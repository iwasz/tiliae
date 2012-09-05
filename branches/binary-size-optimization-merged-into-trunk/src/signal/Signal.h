/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_SIGNAL_H_
#define TILIAE_SIGNAL_H_

/**
 * \page Signal
 * Implementacja sygnał-slot, tylko z dodatkowym obiektem pośredniczącym.
 * \section CoToSaSygnaly Co to są sygnały
 * Tiliae.Signal zostało zaimplementowane z myślą jak największego uniezależnienienia od siebie
 * obiektów. Inspiracją w tym przypadku był mechanizm <b>socketów</b>, gdzie separującą abstrakcją jest
 * warstwa sieciowa i jej adresy IP. Tak samo jest w Tiliae.Signal - aby połączyć obiekt wysyłający
 * i odbierający, programista musi znać jedynie ich wspólny "adres", który w tym przypadku ukrywa
 * się pod pojęciem <b>Scope</b>.
 *
 * Prócz maksymalnego oddzielenia od siebie obiektów ma to jescze jedną zaletę : ułatwia stosowanie
 * Tiliae.Signal z kontenerem. Wyobraźmy sobie sytuację, gdzie obiekt wysyłąjący stosuje zwykłe sygnały,
 * na przykład te z Boost, albo SigC:
 *
 * <pre>
 * struct QuitButton {
 *      REFLECTION_CONSTRUCTOR_ (void)
 *      onClicked () { sig.emit (); }
 *      REFLECTION_METHOD (getSig) signal<void()> const &getSig () const { return sig; }
 *
 * private:
 *      signal<void()> sig;
 *      REFLECTION_END (Button)
 * };
 *
 * /// Odbiorca sygnału z guzika
 * struct Controller {
 *      REFLECTION_CONSTRUCTOR_ (void)
 *      REFLECTION_METHOD (quit) void quit () { exit (0); }
 *      REFLECTION_END (Controller)
 * };
 * </pre>
 *
 * Powyższe klasy tworzymy w kontenerze, z tym nie ma problemu. Jednak w jaki sposób je połączyć?
 * Kontener nie jest językiem skryptowym, a służy do <b>tworzenia</b> obiektów (czyli jest taką dużą fabryką).
 * Problemy się mnożą:
 *
 * - Potrzebna jest klasa (której nie ma, ale można napisać, więc nie jest to duży problem), która by przeprowadzała
 * faktyczny connect. Używało by się jej jakoś tak:
 *
 * <pre>
 * <bean class="Connection">
 *      <property name="signal" ref="quitButton.onClicked" />
 *      <property name="slot" ref="controller" />
 * </bean>
 * </pre>
 *
 * - Z powyższego widać problem drugi, dużo poważniejszy : nie ma mechanizmu, który pozwalałby na wyciągnięcie
 * jakiegoś pola z już stworzonego obiektu (ref="quitButton.onClicked"). To jest oczywiście niepoprawne. Nawet
 * nie ma za bardzo jak zaimplementować takiego wyciągania, bo kontener nie trzyma wskaźników do wszystkich
 * stworzonych przez siebie obiektów, chyba, że są to singletony.
 * - Widać też problem trzeci : Connection będzie działało tylko dla singletonów. Np. jeśli controller nie będzie
 * singletonem, to się w tym przypadku utworzy nowa instancja.
 *
 * \section SignalCechy Cechy Tiliae.Signal
 *
 * Tiliae.Signal wymaga, aby zarówno w obiekcie wysyłającym, jak i nasłuchującym znalazł się specjalny dodatkowy
 * obiekt. To odróżnia Tiliae.Signal od innych tego typu systemów, gdzie receiver nie musi w ogóle być modyfikowany.
 *
 * Sender może być przyporządkowany tylko do jednego scope. Listener do wielu.
 *
 * Ta implementacja nie była optymalizowana pod względem szybkości (która jedakowoż nie została sprawdzona, więc
 * nie wiadomo tak na prawdę, czy są takie wolne). Została pomyślana jako rozwiązanie do programów
 * GUI, gdzie sygnały miałyby być wysyłane w odpowiedzi na akcje usera.
 *
 * \section SygnalyStart Start
 * Plik nagłówkowy:
 *
 * <pre>
 * #include <Signal.h>
 * </pre>
 * lub:
 * <pre>
 * #include <Tiliae.h>
 * </pre>
 *
 * \section SygnalyWysylanie Wysyłanie sygnałów
 * Sposób typowy : za pomocą obiektu klasy Signal::Sender, który należy dodać
 * jako pole do klasy która ma wysyłac sygnał. To jest jak socket, który da się
 * otworzyć tylko do zapisu. Signal::Sender ma tylko jedną metodę : emit, do ktorej
 * trzeba podać nazwę sygnału i opcjonalne argumenty.
 *
 * <pre>
 * struct Button {
 *
 *        Button () :
 *                sender (this) {}
 *
 *        void click () {
 *                sender.emit ("clicked2");
 *        }
 *
 *        Sender sender;
 * };
 * </pre>
 *
 * Drugi sposób to globalna funkcja Signal::emit ("/scope/signal"), której podajemy bezwzględną
 * scieżkę do sygnału. Działa wolno, gdyż przeszukiwane są struktury danych.
 *
 * Treci sposób, to globalna funkcja Signal::emit (scope, "signal"), której podajemy
 * wskaźnik do scope i nazwę sygnału (szybsza wersja tej poprzedniej). W tym scope zostanie wyemitowany sygnał. To jest
 * podobne do wysylania senderem, bo klasa Signal::Sener ma wskaźnik do zbindowanego scope.
 *
 * \section ArgumentySygnalow Argumenty sygnałów
 *
 * Najpierw idą te podane przy tworzeniu listenera, a potem dołaczane są te parametry aktualne, które
 * idą z sendera. Podobniej est z mapą argumentów, z tym, że tam 2 mapy są merdżowane, więc nie ma problemu.
 *
 * \section SygnalyNasluchiwanie Nasłuchiwanie
 *
 * Implementuje się tylko za pomocą obiektów klasy Listener. Listener należy skonfigurować za pomocą jego
 * konstruktora dokłądnie w poniższy sposób:
 *
 * <pre>
 * struct Handler {
 *        REFLECTION_CONSTRUCTOR_(void);
 *
 *        Handler () : onClickedListener (this, "clicked2", "$onClicked ()") {}
 *
 *        REFLECTION_METHOD (onClicked) void onClicked () { ... }
 *
 *        Listener onClickedListener;
 *
 *        REFLECTION_END (Handler);
 * };
 * </pre>
 *
 * Szczególną uwagę należy zwrócić na sygnał na który reaguje dany listener, gdyż można go podać na 2 sposoby:
 *
 * - Sam sygnał bez scope. W takim przypadku listener nie jest aktywny i nie będzie odbierał sygnałów.
 * Trzeba go najpierw umieścić w jakimś scope za pomocą Signal::bind.
 * - Bezwzględna ścieżka do sygnału (zawierająca scope i sygnał). Musi zaczynać się od znaku /. Na przykład :
 * onClickedListener (this, "/window/clicked2", "$onClicked ()") {}. Podanie takiej ścieżki powoduje automatyczne
 * dodanie listenera do wybranego scope.
 *
 * Umieszczenie listenera jako pola klasy powoduje, że zniszczenie tej klasy powoduje także zniszczenie
 * samego listenera. Zaś listener w destruktorze wyrejestrowuje nasz obiekt ze scope, czyli de facto rozłącznie
 * go od podłączonych sygnałów.
 *
 * \section SygnalyBindowanie Bindowanie
 *
 * Bindowanie to proces umieszczania obiektów nasłuchujących i wysyłających sygnały w scopach. Scopey są
 * transparentne i są utrzymywane przez managera. Mają ścieżki podobne to tych z unixowych filesystemów.
 *
 * <pre>
 * Signal::bind ("/scope", &recv);
 * Signal::bind ("/window/panel", &recv, &send);
 * </pre>
 *
 * \section SygnalyElementyAPI Elementy składowe publicznego API
 * - klasa Listener
 * - klasa Sender
 * - Globalne metody dostępowe do Managera : emit, bind, findScope.
 * - klasa Scope jest to wewnętrzna reprezentacja takiej kaby przestrzeni dla obiektów w zakresie której mogą
 * one wysyłać między sobą sygnały. Dzięki zakresom można precyzyjnie wskazać kto ma odebrać sygnał, co
 * przyspiesza wyszukiwanie. Dzięki zakresom można też używac wielokrotnie tej samej nazwy sygnału w różnych miejscach.
 *
 * \section SygnalyPrzyklady Przykłady
 * \section SygnalyXML Jak używać w kontenerze.
 * \section SygnalyImpl Implementacja w skrócie (jak to działa)
 * W aplikacj używającej sygnaów istnieje singleton klasy StateMachine::Machine. Ten obiekt ma mapę obiektów StateMachine::Scope.
 * Obiekty scope z jednej strony zawierająl listę wskaźników do obiektów StateMachine::IListener, a z drugiej strony obiekty
 * typu StateMachine::Sender zawerają po jednym wskaźniku do wybranego scope. Kiedy StateMachine::Sender emituje sygnał (metoda
 * StateMachine::Sender::emit), to deleguje to wywołanie do StateMachine::Scope, który uruchamia wszystkie StateMachine::Listener'y
 * ze swojej listy.
 *
 * Z mniej istotnych rzeczy to:
 * - StateMachine::Listener ma listę StateMachine::Scope'ów do ktorych został dodany, czyli mamy tu round-reference. Jest
 * to zrobione po to, żeby Listenery mogły "wyrejestrowywać" się ze Scopów kiedy są kasowane (i kiedy obiekt je zawierający
 * jest kasowany).
 */

#include "Manager.h"
#include "Helper.h"
#include "Functions.h"
#include "Listener.h"
#include "Sender.h"
#include "Scope.h"

#endif /* SIGNAL_H_ */
