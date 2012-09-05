/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TLE_STATEMACHINE_H_
#define TLE_STATEMACHINE_H_

/**
 * \page StateMachine Maszyna stanów skończonych
 * \section FSMIntro Wstęp
 * Tu są wytłumaczone pojęcia stosowane w mojej maszynie - niektóre mają swoje odpowiedniki w obiektach / klasach,
 * inne nie.
 *
 * - <b>Maszyna</b> : główny obiekt/API. Do niej dodajemy stany, przejścia, do niej kierujemy wejścia i eventy.
 * - <b>Event</b> : coś co wyzwala maszynę. Powoduje jeden "tick" maszyny, podczas którego maszyna może (ale nie musi)
 * zmienić stan (raz lub wiele razy). W Tiliae.StateMachine eventem jest wywołanie metody Machine::run.
 * - <b>Wejście</b> : inaczej Input. Dowolny obiekt pochodzący ze świata zewnętrznego. Typ wejść akceptowalny przez maszynę
 * zależy wyłacznie od kontekstu. Jest kontekst, którego domeną są warianty, ale jest także uproszczony, którego
 * domeną są zwykłe napisy (odpada konieczność kastowania).
 * - <b>Akcja</b> : inaczej Output. Uruchamia jakąś czynność. Akcje dziedziczą z IAction i mogą być przeróżne. Akcja K202Action
 * uruchamia metody obiektów znajdujących się w kontekście, ale mogą być też inne akcje, które robią coś zupełnie innego.
 * - <b>Condition</b> : warunek pracujący na Obiektach wejściowych. Do tej pory było zwykłe matchowanie stringów, teraz dodatkowo
 * mam k202.
 * - <b>Stan</b> : stan. Zawiera InputActions, EntryActions, ExitActions i Transitions.
 * - <b>Transition</b> : przejście pomiędzy stanami wykonywane po spełnieniu warunku.
 * - <b>IObject,input</b> : to są takie jakby konwertery, które zamieniały pojedyncze obiekty rzeczywiste na stringi
 * rozumiane przez maszynę. Jeden taki IObject podpina się pod konkretny obiekt domenowy, na przykład pod int, float
 * etc i generuje string. Jesli teraz zmiaerzm używać k202, to takie IObjecty nie są juz potrzebne. Zostawiłbym to
 * jednak, na wszelki wypadek, zeby nie uzależniać FSM od k202.
 * - <b>IOutput,output</b> : analogicznie dla inputów. Ponieważ maszyna wewnętrznie posługiwała się tylko stringami,
 * zachodziła potrzeba utrzymywania takiego mapowania string-maszyny -> funkcja/metoda C++. I to właśnie to robiło.
 * Teraz, kiedy już jest k202, nie jest to potrzebne, zostawiłbym to na wszelki wypadek, zeby nie uzależniać FSM od k202.
 *
 * \section FSMCreate Tworzymy maszynę
 * Utworzenie obiektu maszyny an 2 sposoby:
 *
 * <pre>
 * Machine machine;
 *
 * // Albo:
 * Ptr <Machine> machine = Machine::create ();
 * </pre>
 *
 * \section FSMContext Tworzymy kontekst
 * Maszyna dostaje wejście ze świata zewnętrznego za pomocą wejść (virtual inputs/variables,
 * jak zwał tak zwał) i eventów. W mojej implementacji eventy nie są rozróżniane. Eventem dla
 * maszyny jest uruchomienie jej metody run.
 *
 * Zmienne wejściowe można dodac do jednego z 3 zakresów, które różnią się między sobą długością życia zmiennych.
 *
 * - <b>MACHINE</b> : zmienne w tym zakresie widoczne przez cały czas istnienia maszyny.
 * - <b>RUN</b> : zmienne w tym zakresie widoczne podczas trwania wyołania metody run (może być wiele przejść (transitions)).
 * - <b>TRANSITION</b> : zmienne znikają po pierwszym przejściu (po pierwszej zmianie stanu).
 *
 * \subsection AAA Kontekst utworzony automatycznie w maszynie
 * Najprościej kazać maszynie, żeby sama sobie utworzyła kontekst. Poniżej przykład jak to zrobić i
 * jak dodać zmienne do zakresu MACHINE:
 *
 * <pre>
 * HelperAT helper; // Jakiś obiekt, który będzie dostępny przez czały czas istnienia obiektu maszyny
 * VariantMap mach; // Mapa "zakres" maszyny.
 * mach.set ("helper", Core::Variant (&helper));
 *
 * Machine machine (mach); // Maszyna
 * </pre>
 *
 * \subsection Kontekst2 Kontekst utworzony przez usera
 * Inny sposób jest taki, ze sami tworzymy kontekst i potem podajemy go do run (nie ma teraz możliwości ustawienia go maszynie) :
 *
 * <pre>
 * MachineContext ctx;
 *
 * VariantMap mach;
 * VariantMap run;
 * VariantMap transition;
 *
 * ctx.setMap (MachineContext::MACHINE, &mach);
 * ctx.setMap (MachineContext::RUN, &run);
 * ctx.setMap (MachineContext::TRANSITION, &transition);
 *
 * // Maszyna
 * Machine machine;
 *
 * // ...
 * machine.run (&ctx);
 * </pre>
 *
 * \section FSMSTany Dodajemy do niej stany
 * Utworzona maszyna jest w meta-stanie \@reset, czyli jakby bez stanu. Użytkownik musi ustawić nazwę initState. Kiedy maszyna
 * dostaje pierwszy event (pierwsze uruchomienie metody Machine::run), to wchodzi w init-state (wykonując oczywiście entry
 * actions), a następnie sprawdza, czy nie zaistniały warunki do przejścia w następny stan i tak w kółko. To jest reguła przy
 * każdym evencie : maszyna może po jednym evencie zmienić stan kilka razy i wykonać w tym czasie wiele akcji. Przykład:
 *
 * <pre>
 * Machine machine;
 * Ptr <State> state1 = State::create ("init");
 * machine.addState (state1);
 * machine.setInitialStateName ("init");
 *
 * // 1. Maszyna nie ma stanu, lub inaczej mówiąc ma meta-stan @reset.
 * machine.run ();
 *
 * // 2. Teraz maszyna jest w stanie init
 * </pre>
 *
 * \section FSMAkcje Do stanu dodajemy akcje (wyjścia)
 *
 * Do stanów można dodać akcje (czyli wyjścia maszyny). Do samego stanu można dodać następujące rodzaje akcji:
 *
 * - <b>entryAction</b> Odpala się przy wejściu w stan.
 * - <b>exitAction</b> Odpala się przy opuszczaniu stanu.
 * - <b>inputAction</b> Odpala się gdy spełniony jest warunek.
 *
 * Przykłady:
 *
 * <pre>
 * Ptr <State> state1 = State::create ("init");
 * state1->addEntryAction (K202Action::create ("$helper.inc ()"));
 *
 * state1->addInputAction (InputActions::create (
 *         K202Condition::create ("$!clicked == true"),
 *         K202Action::create ("$helper.set (667)")));
 * </pre>
 *
 * \section FSMTransition Przejścia między stanami.
 * Można je dodawać do konkretnego stanu. Przejście może (i zazwyczaj ma) warunek rpzejścia. Przejście zostanie
 * wykonane, kedy prze evencie warunek jest spełniony. Warunki mają swoją klasę bazową ICondition i są różne. Na
 * przykład K202Condition wykonuje kawałek skrypu na kontekście maszyny i może na przykłąd sprawdzić wartość
 * jakichś zmiennych etc. Przykład przejścia:
 *
 * <pre>
 * state->addTransition (Transition::create ("idle", "bean",   // Przejście ze stanu idle do stanu bean.
 *     machine->createCondition ("$!name == 'bean'"),          // Jeśli zmienna "name" w kontekście ma wartość 'bean'.
 *     K202Action::create ("$service.pushNewMappedMeta ()"))); // Przy przejściu uruchom akcję K202Action.
 * </pre>
 *
 * \section FSMTransitionAct TransitionAction-s
 * Dodatkowym ficzerem są akcje TransitionAction's dodawane bezpośrednio do maszyny, zamiast do samych przejść. Przykład
 * użycia wygląda tak:
 *
 * <pre>
 * machine->addTransitionAction (TransitionAction::create ("ref", "list", K202Action::create ("$service.popCurrentIndexedElem ()")));
 * </pre>
 *
 * \section FSMLinki Linki
 * - http://en.wikipedia.org/wiki/UML_state_machine - zwłaszcza paragrafy Extended States i Guard Conditions są ciekawe tak ogólnie odnośnie maszyn.
 *

 *
 * \section Workflow
 * Nie wiem co miało być w tej sekcji...
 * - Maszyny
 * - Kolejność wykonywania tranzycji i transition actions nie jest ustalona jeśli warunki
 * wskazują na to, że odpali się kilka przejść, czy akcji.
 * - Placeholdery : \@shutDown, \@reset, \@back (tylko z extensionem).
 */

#include "action/Action.h"
#include "condition/Condition.h"
#include "context/Context.h"
#include "structure/Structure.h"
#include "transition/TransitionAction.h"

#	endif /* STATEMACHINE_H_ */
