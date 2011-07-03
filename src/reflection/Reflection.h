/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_REFLECTION1_H
#define TILIAE_REFLECTION1_H

/**
 * \page Reflection Reflection : prosty system refleksji.
 * \section ReflectMakro Makra adnotacyjne.
 * - \b _c Konstruktor. Jako argumenty podajemy typy argumentów tego konstruktora. Na przykład
 * _c (void), _c (int, float) etc.
 * - \b __c Konstruktor jako pierwsza adnotacja w pliku. Jako argumenty podajemy typy argumentów
 * tego konstruktora. Na przykład __c (void), __c (int, float) etc.
 * - \b __d Początek klasy (abstrakcyjnej/nie dającej się konstruować, czyli nie mozliwej do
 * zaadnotowania za pomocą _c). To makro jest niezbędne jeśli chcemy adnotować metody w abstrakcyjnej
 * klasie. Musi występowac jako pierwsza adnotacja w klasie.
 * - \b _b Lista klas bazowych. To makro służy do informowania systemu refleksji o nadklasach danej
 * klasy. Dzięki temu makru refleksja wie, że wszystkie metody nadklas są dostępne także w tej klasie.
 * Dzięki temu nie trzeba powtarzać tych samych adnotacji metod w klasach konkretnych, a jedynie
 * zaadnotować je w klasie bazowej / interfejsie. Przykład : _b ("IWidget", "ICallable").
 * - \b __b  Lista klas bazowych - pierwsza adnotacja w klasie. Działa tak samo jak _b, ale może
 * występowac jako pierwsze makro w klasie.
 * - \b _m Adnotacja metody. Za pomocą tego makra adnotujemy metody. Jako parametr makra podajemy tylko
 * nazwę metody. Przykład : _m (setName).
 * - \b __m Adnotacja metody - pierwsza adnotacja w klasie. Działa jak _m, ale może występowac jako
 * pierwsza adnotacja w klasie (dla tego podwójne podkreślenie ___). Przykład użycia : __m (setName).
 * - \b _s, \b __s Adnotacja settera. Jest to bardzo podobna adnotacja do _m, ale można ją stosowac tylko
 * do setterów (a konkretnie tylko do metod z jednym argumentem). Dodatkową różnicą w stosunku do _m
 * jest polimorficzny cast ocast przy rzutowaniu argumentu z Variant na konkretny typ. To pozwala
 * ustawiać typy polimorficzne.
 * - \b _M, \b __M Adnotacja metody przeciążonej (nie const). Działa identycznie jak _m, tylko różni się sposobem
 * adnotowania. Jako argumenty tego makra podajemy typ zwracany z funkcji, jej nazwe, a następnie
 * typy jej argumentów. Dzięki temu, jeśli w klasie jest kilka metod o tej samej nazwie (przeciążonych),
 * to można je także adnotować. Z makrami _m i __m jest to niemożliwe. Przykład stosowania : _M (void, metoda, double, int).
 * - \b _Mc, \b __Mc - Adnotacja metody przeciążonej (const). Identyczne jak _M i __M, ale dla metod
 * stałych (czyli z const na końcu).
 *
 * - \b _g Adnotacja kolekcji. Za pomocą tego makra można adnotować kolekcje. W tym momencie obsługiwane
 * są cztery kolekcje STL : std::vector, std::list, std::set i std::map. Można rozszerzać funkcjonalność
 * makgra _g. Przykład użycia : _g (StringList), gdzie StringList to jakiś typedef. W refleksji ten typ
 * będzie figurował jako "StringList".
 * - \b _gn Adnotacja kolekcji z dodatkową nazwą. Działa jak _g, tylko jako dodatkowy argument podajemy
 * nazwę klasy pod ktorą ten typ będzie figurował w refleksji.
 * - \b _f Adnotacja typu z metodą fabryki. Ta adnotacja uruchamia po prostu statyczną metodę o nazwie
 * \b addAnnotations. Ta metoda powinna dodać właściwe obiekty do systemu refleksji.
 * - \b _fn Adnotacja typu z metodą fabryki z dodatkową nazwą.
 *
 * - \b _e Koniec zwykłej klasy (nie szablonu). Jako argument podajemy tą klasę. Na przykłąd _e (Klasa).
 * Bez tego makra nic się nie doda do refleksji.
 * _ \b __e Koniec zwykłej klasy (nie szablonu) jako jedyna adnotacja w klasie. Dodaje jeden bezargumentowy
 * konstruktor do reflakcji dla tej klasy.
 * - \b _tb, \b _t, \b _te - Koniec szablonu klas. Przykłady poniżej.
 *
 * Teraz przykłady. Na pocżatek zwykła klasa - bez żadnych szablonów.
 *
 * <pre>
 * class City {
 * public:
 *         __c (void)
 *
 *         _m (init)       void init ();
 *         _m (setName)    void setName (const Core::String &name);
 *
 *         _e (City)
 * };
 * </pre>
 *
 * Mamy tu 3 rodzaje adnotacji. Pierwsza z nich oznacza początek klasy (stąd podwójny underscore) i jednocześnie
 * oznacza konstruktor bez-argumentowy. Dwa następne makra mówią same za siebie - są to adnotacje metod.
 * Ostatnia adnotacja oznacza koniec klasy - każda klasa musi mieć na końcu jedno z makr kończących. Przykład 2:
 *
 * <pre>
 * struct Interface {
 *      __d
 *      _s (setName)    virtual void setObj (ISomeObj *obj) = 0;
 *      _e (Interface)
 * };
 *
 * struct Concrete : public Interface {
 *      __b ("Interface")
 *      _c (void)
 *      _e (Concrete)
 * };
 * </pre>
 *
 * W powyższym przykładzie zadeklarowałem w klasie Concrete odwołanie do jej klasy bazowej, czyli
 * Interface za pomocą __b (od base-class). Dodatkowo w klasie Interface użyłem __d, co pozwala
 * dodawać klasy abstrakcyjne do refleksji. Metodę setObj zaadnotowałem za pomocą _s, co pozwoli
 * podawać różne typy dziedziczące z ISomeObj jako argument tego settera. Dodajmy jakieś kolekcje:
 *
 * <pre>
 * typedef std::list <Ptr <Address> > AddressList;
 * _g (AddressList)
 *
 * typedef std::map <Core::String, Ptr <Bar> > BarMap;
 * _g (BarMap)
 * </pre>
 *
 * Na koniec dodam do refleksji 2 konkretyzacje (specjalizacje) szablonu klas:
 *
 * <pre>
 * template <typename T&gt;
 * struct Template02 {
 *
 *         __c (void)
 *
 *         _m (setT) void setT (const T &t) { this->t = t; }
 *         _m (getT) const T &getT () const { return t; }
 *
 *         T t;
 *
 *         _tb
 *         _t (Template02<int>)
 *         _t (Template02<double>)
 *         _te
 * };
 * </pre>
 *
 * Jeśli konkretyzacja była by tylko jedna, to użyli byśmy zwykłego _e. Na przykład _e (Template02<double>).
 *
 * \section ReflectKoszt Koszt używania refleksji.
 * Nie zmieżyłęm tego dobrze, ale wygląda na to, że przy wyłączonej optymalizacji (-O0) i na 32 bitowej
 * maszynie rozmiar binarki zwiększa się od 600B do 800B po dodaniu jednej adnotacji _m dla settera (dla
 * jednoargumentowej metody). Na razie sprawdziłem tylko tyle.
 *
 * \section ReflectIncomplete Refleksja i typy niekompletne
 * Często zdarza się tak, że w zaadnotowanej klasie są settery i gettery lub konstruktory, które przyjmują
 * wskaźniki lub referencje do typów niekompletnych jako argumenty. Można je adnotowac, ale potrzebna jest
 * też definicja takiej klasy gdzieś w jednostce translacji (kiedyś tak nie było). Na przykład :
 *
 *
 * <pre>
 * class Incompl; // forward declaration
 *
 * struct A {
 *      __c (void)
 *
 *      _m (getI)
 *      Incompl *getI () const { return i; }
 *
 *      Incompl *i;
 *      _e (A)
 * };
 * </pre>
 *
 * Makra adnotacyjne tworzą niejawne wrappery, które wrapują te settery/konstruktory tak, że wszystkie
 * ich argumenty można podać jako warianty. Jednak każdy wariant przy inicjowaniu próbuje pobrać type_info
 * w ten sposób : typeid (T&). Z tego właśnie powodu potrzebna jest definicja klasy, bo jeśli jej nie ma
 * w jednostce translacji, to wyskakuje coś w stylu:
 *
 * <pre>
 * error: forward declaration of ‘struct Country’
 * </pre>
 *
 * \section Jak to działa?
 * Adnotacja _e dodaje na końcu specjalną strukturę, a zaraz potem definicję statyczne zmiennej globalnej o typie tej
 * struktury, która jest umieszczona jeszcze w anonymous namespace. Całość wygląda mniej więcej tak:
 *
 * <pre>
 *         template <typename REFLECT_CLAZZ_TYPE> static void __init_method__ (const char *__clazz_reflect_name__)
 *         {
 *                 __annotation_method__19 <REFLECT_CLAZZ_TYPE> (__clazz_reflect_name__);
 *         }
 *
 * }; // Końcówka klasy Address
 *
 * // Specjalna struktura inicjująca.
 * struct ServiceClass2061 {
 *
 *         ServiceClass2061 (int)
 *         {
 *                 static ServiceClass2061 dummy;
 *         }
 *
 *         ServiceClass2061 ()
 *         {
 *                 Address::__init_method__ <Address> ("Address");
 *                 std::cerr << "Address" << std::endl;
 *         }
 * };
 *
 * namespace {
 *         static ServiceClass2061 ServiceClass206161 (0);
 * };
 * </pre>
 *
 * Zmienna globalna ServiceClass206161 jest tworzona przed uruchomieniem się funkcji main tyle razy ile
 * razy powtarza się jej definicja (czyli tyle razy w ilu jednostkach translacji inkludowano plik Address.h).
 * W przypadku reflection_test jest to chyba 6 razy. Następnie jest użyty trick z "initialization fiasco" z
 * C++ FAQ i przy pierwszym uruchomieniu się konstruktora  ServiceClass2061 (int) jest tworzona instancja
 * ServiceClass2061 o nazwie dummy. Uzywany jest w tym celu konstruktor bezargumentowy, który odpala łańcuch
 * metod (nazwijmy je) serwisowych.
 *
 * Niestety ale, zdarza się, że nazwa tej ostatniej zmiennej (w przykłądzie pozyżej jest to ServiceClass206161),
 * jest różna w różnych jednostkach translacji. Jest to zrozumiałe, ponieważ jej nazwa jest generowana za pomocą
 * __COUNTER__ i __LINE__, które mogą być rózne w różnych jednostkach translacji. Wówczas powstanie więcej niż
 * jedna instancja zmiennej dummy i łańcuch metod uruchomi się więcej niż raz.
 *
 * Aby zapobiec wielokrotnemu dodawaniu się adnotacji do AnnotationManagera, prócz wstępnego tricku z dummy
 * AnnotationManager odrzuca adnotacje, o których wie, że już są na liście.
 *
 * \section FAQ
 * o Leci wyjątek, że klasa jest już zaadnotowana. Mniej więcej taki :
 *
 * <pre>
 * unknown location(0): fatal error in "testClassProperClass": std::exception: 1. ClassAllreadyManagedException (City). There is another class with this name with different type_info. Type info of stored class : [4City, 139927121869552], type_info of new class : [4City, 5139376].
 * </pre>
 *
 * To oznacza, że w Manager-rze jest już klasa o tej samej nazwie, ale innym type_info. Jeśli type_info by
 * było takie samo, to nic się złego nie stanie.
 *
 * Należy upewnić się, że klasa ma wyeksportowane symbole (makro TILIAE_API).
 *
 * o Nie ma klasy w managerze (no class found), mimo, że adnotacje są i wszystko inne wydaje się być OK.
 * Należy (z tego co pamiętam) spróbować przenieść makro _e jedną linię do dołu.
 */

#include "model/Method.h"
#include "model/Class.h"
#include "model/Constructor.h"

#include "annotations/Annotations.h"

#include "reflectAnnotations/MethodAnnotation.h"
#include "reflectAnnotations/ConstructorAnnotation.h"
#include "reflectAnnotations/BaseClassAnnotation.h"
#include "reflectAnnotations/FactoryMethodAnnotation.h"
#include "reflectAnnotations/ClassAnnotation.h"
#include "reflectAnnotations/CollectionAnnotation.h"

#include "Manager.h"
#include "Exceptions.h"

namespace Reflection {

        /**
         *  Inicjuje biblioteke.
         *  TODO Czy to jest potrzebne?! Chyba się sama inicjuje.
         */
        extern void init ();

};

#endif

