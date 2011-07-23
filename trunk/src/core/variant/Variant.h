/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VARIANT_H_
#define VARIANT_H_

#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/make_shared.hpp>
#include <string> // toString

#include "Object.h"
#include "ApiMacro.h"

namespace Core {
class String;

/**
 * \page Variant Variant : implementacja bezpiecznej unii.
 * \section VariantMotyw Motywacja
 * Motywacją do napisania warianta od nowa był szereg problemów ze starym wariantem. Problemy:
 * - Ogromny rozmiar binarek spowodowany wielką ilością specjalizacji (kokretyzacji) szablonów
 * klas i funkcji, które implementowały stary wariant. To z kolei prowadziło do generowania
 * dużej ilości kodu i dużej ilości symboli w binarce.
 * - Bardzo długi czas kompilacji spowodowany tym co wyżej.
 * - Poprzednia implementacja zamiatała błędy pod dywan : niemożliwe do wykonania kasty nie powodowały
 * błędów podczas kompilacji, a wyjątki podczas działania programu. To powodowało trudne do zdebugowania
 * (kilka straconych wieczorów) błędy.
 *
 * Z tego powodu zdecydowałem się napisać wariant po raz chyba 5 lub 6-sty od nowa. Tym razem oparłem
 * się na QVariant i maksymalnie uprościłem wariant (obcinając też dużo jego funkcjonalności).
 *
 * \section VariantIntro Wstęp
 * Wariant jest to klasa wzorowana na QVariant z qt. Jest to implementacja bezpiecznej unii, z kilkoma
 * dodatkowymi ficzerami ułatwiającymi implementację refleksji. Jego głównym ficzerem prócz "bzpiecznej
 * unii" jest możliwość automatycznego wyłuskania lub pobrania adresu. Czyli inicjujemy wariant wskaźnikiem
 * a wyciągamy z niego referencję i na odwrót.
 *
 * Wariant ma dwie semantyki, które zależą od typu z jakim utworzono wariant. Wariant ma semantykę \b wartości
 * (zachowuje się jak wartość, to znaczy podczas kopiowania wariantu obiekt w środku także jest kopiowany)
 * jeśli wariant zainicjowano skalarem lub wskaźnikiem do typu skalarnego:
 *
 * - bool
 * - char
 * - unsigned char
 * - double
 * - long double
 * - float
 * - int
 * - unsigned int
 * - long int
 * - unsigned long int
 * - short int
 * - unsigned short int
 *
 * We wszystkich innych przypadkach (także std::string i Core::String) wariant ma semantykę \b uchwytu i to nie
 * zależnie czy zainicjowano go typem T, T&, czy T*. Uchwytów jest kilka rodzajów : do stałej i do nie-stałej,
 * jako smart_ptr i jako zwykły wskaźnik.
 *
 * \subsection VariantCreate Tworzenie warianta
 * Aby utworzyć wariant, należy użyć jednego z jego konstruktorów a są to:
 *
 * Core::Variant::Variant (T)
 * Gdzie T może być jednym z typów skalarnych wymienionych wyżej lub wskaźnikiem do jednego z typów skalarnych.
 * Te konstruktory tworzą wariant - o semantyce wartości.
 *
 * Variant::Variant (T *)
 * Variant::Variant (T const *)
 * Variant::Variant (shared_ptr <T>)
 * Variant::Variant (shared_ptr <T const>)
 * Te konstruktory tworzą warianty o semantyce uchwytu. T jest dowolne z wyłączeniem skalarów, które łapią się
 * do pierwszego konstruktora. Jeżeli T* daje się skonwertować do Core:;Object*, to jest to specjalny przypadek.
 * Taki wariant daje się kastowac za pomocą polimorficznego kastu ocast, który jest odpowiednikiem dynamic_cast.
 *
 * \subsection VariantCast Kastowanie z warianta na typ.
 * Służą do tego dwie globalne funkcje : vcast i ocast. Pierwsza jest odpowiednikiem static_cast, a druga
 * dynamic_cast (jednak działa trochę inaczej).
 *
 * <TABLE>
 * 	<TR>
 * 	        <TD></TD>
 * 		<TD>vcast&lt;T&gt;</TD>
 * 		<TD>
 * 			vcast&lt;T&amp;&gt;
 * 		</TD>
 * 		<TD>
 * 			vcast&lt;T const&amp;&gt;
 * 		</TD>
 * 		<TD>
 * 			vcast&lt;T*&gt;
 * 		</TD>
 * 		<TD>
 * 			vcast&lt;T const *&gt;
 * 		</TD>
 * 		<TD>
 * 			vcast&lt;shared_ptr&lt;T&gt; &gt;
 * 		</TD>
 * 		<TD>
 * 			vcast&lt;shared_ptr&lt;T const&gt; &gt;
 * 		</TD>
 * 	</TR>
 * 	<TR>
 * 		<TD>
 * 			Variant (T const &amp;)
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 	</TR>
 * 	<TR>
 * 		<TD>
 * 			Variant (T *)
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 	</TR>
 * 	<TR>
 * 		<TD>
 * 			Variant (T const *)
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 	</TR>
 * 	<TR>
 * 		<TD>
 * 			Variant (shared_ptr &lt;T&gt;)
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 	</TR>
 * 	<TR>
 * 		<TD>
 * 			Variant (shared_ptr &lt;T const&gt;)
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 		<TD>
 * 		</TD>
 * 		<TD>
 * 			v
 * 		</TD>
 * 	</TR>
 * </TABLE>
 *
 * gdy v.getType () ma jedną z poniższych warości:
 *
 * \subsection VariantConst Wariant i const-correctness
 * [Patrz test 07Variant.cc] Wariant w tym przypadku zachowuje się jak wskaźnik. Jeśli wariant jest stały, to nie można
 * mu przypisać nowej wartości, czy wyczyścić go, żeby nic nie zawierał, ale można modyfikować
 * obiekt który jest w jego środku (jeśli ma semantykę uchwytu).
 *
 * Drugą sprawą są wskaźńiki wewnątrz wariantu, które mogą być do stałej, lub do zmiennej.
 * To są dwie różne rzeczy - tak jak w przypadku wskaźników. Przykład:
 *
 * <pre>
 * struct A {
 *     void c () const {}
 *     void n () {}
 * };
 *
 * A a;
 * A const c;
 *
 * Variant va (&a);             // Odpowiednik A*
 * Variant const vac (&a);      // Odpowiednik A * const
 * Variant vc (&c);             // Odpowiednik A const *
 * Variant const vcc (&c);      // Odpowiednik A const * const
 * </pre>
 *
 * va można modyfikować, tak samo jak obiekt wewnątrz va. vac nie można zmodyfikować, ale można modyfikować obiekt w jego
 * wnętrzu (można na przykład uruchomoć dla niego metodę nie const). W przypadku vcc nie można zmodyfikowac nic. Taka
 * implementacja warianta jest też zgodna z tym jak jest zaimplementowane boost::any.
 *
 * \subsection VariantAPI APi
 * Api warianta składa się jedynie z klasy Variant i 4 funkcji globalnych:
 *
 * - Core::vcast
 * - ocast
 * - ccast
 * - occast
 *
 * Więcej w \ref CoreAPI
 *
 * \subsection VariantTODO Do zrobienia.
 * - # Test I
 * - # ocast
 * - # test ocastu
 * - # ccast (can)
 * - # test ccastu
 * - # inne testy ze starego core.
 * - dokumentacja do końca
 * - # wartości zwracane z funkcji
 * - # unia w wariant
 * - valgrind
 * - # ustalić co z shared_ptr w wariancie i poprawić lub udokumentować. Z dokumentacji wynika, że OK : This constructor has been changed to a template in order to remember the actual pointer type passed. The destructor will call delete with the same pointer, complete with its original type, even when T does not have a virtual destructor, or is void]
 *
 * Dopisać do dokumentacji że :
 * - Nie można kastować na char * - taki kast w ogóle nie istnieje (bo to jest wariant value).
 * - Nie można tworzyć waraintów typu : Core::Variant ((char *)NULL) (bo to jest wariant value i robi wyłuskanie z NULL).
 * - Variant::getTypeInfo () zwraca type_info w postaci znormalizowanej, czyli zawsze do T.
 * - variant(const char *) robi string
 *
 * Kiedyś
 * - Na prawdziwym kodzie zrobić optymalizzację warianta pod kątem rozmiaru binarek.
 *
 * Q&A
 * - Dlaczego Variant::Type nie uwzględnia kolekcji i innych bardziej złożonych typów?
 *  - Dla prostoty.
 */

/**
 * Implementacja bezpiecznej unii. Szerzej opisane w \ref Variant.
 * \ingroup CoreAPI
 */
class TILIAE_API Variant {
public:

        /**
         * Typy elementów w wariancie.
         */
        enum Type {

                /**
                 *  Variant uninitialised (this value is set when creating
                 *  empty Variant ie. Variant v;).
                 */
                NONE,

                /**
                 * Specjalny znacznik warianta NULL, który można skastowac na dowolny
                 * typ wskaźnikowy. Aby stworzyć taki wariant, należy użyć metody setNull ();
                 */
                NIL,

                /**
                 *  Taki typ maja warianty stworzone ze wskaznikow, ale
                 *  jesli te wskaniki nie maja nic wspolnego z Core::Object.
                 */
                POINTER,

                /**
                 *  Taki typ maja warianty stworzone ze wskaznikow, ale
                 *  jesli te wskaniki nie maja nic wspolnego z Core::Object.
                 */
                POINTER_CONST,

                /**
                 * Warianty stworzone z shared_ptr zwracają ten typ.
                 */
                SMART,

                /**
                 * Warianty stworzone z shared_ptr <T const> zwracają ten typ.
                 */
                SMART_CONST,

                /**
                 * Zainicjowane wskaźnikiem do Object*
                 */
                OBJECT,

                /**
                 * Zainicjowane wskaźnikiem do Object const*
                 */
                OBJECT_CONST,

                ///
                SMART_OBJECT,

                ///
                SMART_OBJECT_CONST,

                /**
                 *  Boolean value (not pointer). When copying Varinats, each will have
                 *  its own copy of this value.
                 */
                BOOL,
                CHAR,
                UNSIGNED_CHAR,
                DOUBLE,
                LONG_DOUBLE,
                FLOAT,
                INT,
                UNSIGNED_INT,
                LONG_INT,
                UNSIGNED_LONG_INT,
                SHORT_INT,
                UNSIGNED_SHORT_INT,
                STRING,                      /// std::string - przez wartość.
                STRING_POINTER,              /// std::string - wskaźnik.
                STRING_POINTER_CONST,        /// std::string - wskaźnik do stałej.
                USTRING,                     /// Core::String - przez wartość.
                USTRING_POINTER,             /// Core::String - wskaźnik.
                USTRING_POINTER_CONST        /// Core::String - wskaźnik do stałej.
        };

        template <typename T> friend struct VCast;
        template <typename T> friend struct OCast;
        template <typename T> friend struct LCast;

/*--------------------------------------------------------------------------*/

        // NONE
        Variant ();

        // VALUE
        explicit Variant (bool const &d);
        explicit Variant (char const &d);
        explicit Variant (unsigned char const &d);
        explicit Variant (double const &d);
        explicit Variant (long double const &d);
        explicit Variant (float const &d);
        explicit Variant (int const &d);
        explicit Variant (unsigned int const &d);
        explicit Variant (long int const &d);
        explicit Variant (unsigned long int const &d);
        explicit Variant (short int const &d);
        explicit Variant (unsigned short int const &d);

        // Handler
        explicit Variant (std::string const &d);
        explicit Variant (std::string *d);
        explicit Variant (std::string const *d);
        explicit Variant (Core::String const &d);
        explicit Variant (Core::String *d);
        explicit Variant (Core::String const *d);
        /**
         * Uwaga - konstruktor Variant (const char *s) nie tworzy warianta o typie CHAR,
         * a twoarzy wariant o typie STD_STRING. Tak jest prościej, bo można podać stałą
         * napisową.
         */
        explicit Variant (const char *s);

        /**
         * Przy używaniu tego konstruktora trzeba bezwzględnie pamiętać, żeby nie podawać
         * tu wartości tymczasowych, ponieważ ten konstruktor pobiera wskaźnik do swojego
         * argumentu. Dlatego należy mieć włączone -Wall, żeby kompilator miał szansę wykryć
         * taki błąd.
         */
        template<typename S>
        explicit Variant (S const &);
        template<typename S>
        explicit Variant (S *);
        template<typename S>
        explicit Variant (S const *);
        template<typename S>
        explicit Variant (boost::shared_ptr<S> const &);
        template<typename S>
        explicit Variant (boost::shared_ptr<S const> const &);

/*--------------------------------------------------------------------------*/

        /**
         * Zwraca typ warianta - czyli jedną z wartości z Variant::Type.
         */
        Type getType () const { return type; }

        /**
         * Zawsze zwraca typeid (T *). Bez względu na sposób zawierania obiektu. Jest to
         * tak zwana (moja nazwa) postać znormalizowana type_info. Chodzi o to, żeby nie
         * martwić się o szczegóły typu czy to jest wskaźnik, czy referencja, czy wskaźnik
         * do stałej, tylko mieć informację o "czystym" typie T.
         */
        std::type_info const &getTypeInfo () const
        {
                if (ti) {
                        return *ti;
                }
                else {
                        return typeid (void *);
                }
        }

        /**
         * Można ustawić type_info, ale to tylko na własną odpowiedzialność :)
         */
        void setTypeInfo (std::type_info const &t) { ti = &t; }

        /**
         * Pomocnicza metoda zwracająca reprezentację napisową.
         */
        std::string toString () const;

        /**
         * Czy wariant zawiera elementy typu Core:;Object i czy można użyć kastowania
         * polimorficznego ocast.
         */
        bool isObject () const;

        /**
         * Zwraca informację czy wariant ma semantykę uchwytu.
         */
        bool isHandle () const;

        /**
         * Zwraca informację czy wariant ma semantykę wartości.
         */
        bool isValue () const;

        /**
         * Mówi czy wariant jest zainicjowany jakąś wartością.
         */
        bool isNone () const;

        /**
         * Jeśli wariant jest uchwytem (isHandle *( == true) to ta metoda zwraca
         * czy ten uchwyt jest pusty. W pozostałych przypadkach zwróci false.
         */
        bool isNull () const;

        /**
         * Służy do stworzenia specjalnego warianta nullowego, który można potem skastować na
         * dowlony wskaźnik. Wcześniej do tego służył wariant typu INT o wartości 0, ale niestety
         * powodowało to problemy tam gdzie wymagany był INT.
         */
        void setNull ();

private:

        Type type;
        std::type_info const *ti;
        boost::shared_ptr<void> sptr;

        union {
                bool b;
                char c;
                unsigned char uc;
                double d;
                long double ld;
                float f;
                int i;
                unsigned int ui;
                long int li;
                unsigned long int uli;
                short int si;
                unsigned short int usi;
                wchar_t w;
                void *ptr;
                void const *cptr;
        };
};

/****************************************************************************/

//template<typename S>
//Variant::Variant (S const &p) :
//        type ((boost::is_convertible <S *, Core::Object *>::value) ? (OBJECT_CONST) : (POINTER_CONST)),
//        ti (&typeid (S&)),
//        cptr (&p)
//{
//}

template<typename S>
Variant::Variant (S const &p) :
        type ((boost::is_convertible <S *, Core::Object *>::value) ? (SMART_OBJECT) : (SMART)),
        ti (&typeid (S&)),
        sptr (boost::make_shared <S> (p))
{
}

/****************************************************************************/

template<typename S>
Variant::Variant (S *p) :
        type ((boost::is_convertible <S *, Core::Object *>::value) ? (OBJECT) : (POINTER)),
        ti (&typeid (S)),
        ptr (p)
{
}

/****************************************************************************/

template<typename S>
Variant::Variant (S const *p) :
        type ((boost::is_convertible <S *, Core::Object *>::value) ? (OBJECT_CONST) : (POINTER_CONST)),
        ti (&typeid (S)),
        cptr (p)
{
}

/****************************************************************************/

template<typename S>
Variant::Variant (boost::shared_ptr<S> const &p) :
        type ((boost::is_convertible <S *, Core::Object *>::value) ? (SMART_OBJECT) : (SMART)),
        ti (&typeid (S)),
        sptr (p)
{
}

/****************************************************************************/

template<typename S>
Variant::Variant (boost::shared_ptr<S const> const &p) :
        type ((boost::is_convertible <S *, Core::Object *>::value) ? (SMART_OBJECT_CONST) : (SMART_CONST)),
        ti (&typeid (S)),
        sptr (boost::const_pointer_cast <S> (p))
{
}

extern TILIAE_API std::ostream &operator << (std::ostream &s, Core::Variant const &v);

} // namespace

#	endif /* VARIANT_H_ */
