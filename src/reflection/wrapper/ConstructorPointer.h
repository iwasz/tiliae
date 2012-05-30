/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_REFLECT_CONSTRUCTOR_SHARED_H_POINTER
#define TILIAE_REFLECT_CONSTRUCTOR_SHARED_H_POINTER

#include <list>
#include <map>

#include "../Tools.h"
#include "../../core/variant/Variant.h"
#include "../../core/Typedefs.h"
#include "../../core/variant/Cast.h"
#include "WrapperCommons.h"

namespace Reflection {

/**
 * Jest to, jak widać po interfejsie interfejs klas (szablonow klas), które
 * wrapują konstrukotr dowolnej klasy. Taki wraper udostępnia metode
 * invoke, jak poniżej i argumenty można podać w postaci VariantVector-y.
 * Elementy tej listy idą następnie jako parametry do wrapowanego konstruktora,
 * a sam konstruktor jest uruchamiany za pomocą operatora *new*.
 */
class IConstructorPointer {
public:

        virtual ~IConstructorPointer () {}

        /**
         * Interfejst tej metody wskazuje na to, że argumenty są przekazywane
         * przez referencjęi mogą zostać zmienione przez uruchamianą funkcję,
         * czy tam konstruktor w tym przypadku.
         */
        virtual Core::Variant invoke (Core::VariantVector *args) = 0;
        virtual std::type_info const &getType () const = 0;
        virtual unsigned int getArity () const = 0;

};

/*##########################################################################*/

template <class K> class ConstructorPointer00 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list)
        {
                Tools::checkArgList (list, 0);
                return Core::Variant (new K);
        }

        std::type_info const &getType () const { return typeid (void *); }
        unsigned int getArity () const { return 0; }
};

/*##########################################################################*/

template <class K, class T1>
class ConstructorPointer01 : public IConstructorPointer {
public:
        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 1; }
};

template <class K, class T1>
Core::Variant ConstructorPointer01<K, T1>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 1);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i);
        return Core::Variant (new K (t1));
}

/*##########################################################################*/

template <class K, class T1, class T2>
class ConstructorPointer02 : public IConstructorPointer {
public:
        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 2; }
};

template <class K, class T1, class T2>
Core::Variant ConstructorPointer02<K, T1, T2>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 2);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i);
        return Core::Variant (new K (t1, t2));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3>
class ConstructorPointer03 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 3; }
};

template <class K, class T1, class T2, class T3>
Core::Variant ConstructorPointer03<K, T1, T2, T3>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 3);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i);
        return Core::Variant (new K (t1, t2, t3));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4>
class ConstructorPointer04 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 4; }
};

template <class K, class T1, class T2, class T3, class T4>
Core::Variant ConstructorPointer04<K, T1, T2, T3, T4>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 4);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i++);
        T4 t4 = vcast <T4> (*i);
        return Core::Variant (new K (t1, t2, t3, t4));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4, class T5>
class ConstructorPointer05 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 5; }
};

template <class K, class T1, class T2, class T3, class T4, class T5>
Core::Variant ConstructorPointer05<K, T1, T2, T3, T4, T5>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 5);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i++);
        T4 t4 = vcast <T4> (*i++);
        T5 t5 = vcast <T5> (*i);
        return Core::Variant (new K (t1, t2, t3, t4, t5));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4, class T5, class T6>
class ConstructorPointer06 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 6; }
};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6>
Core::Variant ConstructorPointer06<K, T1, T2, T3, T4, T5, T6>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 6);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i++);
        T4 t4 = vcast <T4> (*i++);
        T5 t5 = vcast <T5> (*i++);
        T6 t6 = vcast <T6> (*i);
        return Core::Variant (new K (t1, t2, t3, t4, t5, t6));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
class ConstructorPointer07 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 7; }
};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
Core::Variant ConstructorPointer07<K, T1, T2, T3, T4, T5, T6, T7>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 7);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i++);
        T4 t4 = vcast <T4> (*i++);
        T5 t5 = vcast <T5> (*i++);
        T6 t6 = vcast <T6> (*i++);
        T7 t7 = vcast <T7> (*i);
        return Core::Variant (new K (t1, t2, t3, t4, t5, t6, t7));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
class ConstructorPointer08 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 8; }
};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
Core::Variant ConstructorPointer08<K, T1, T2, T3, T4, T5, T6, T7, T8>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 8);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i++);
        T4 t4 = vcast <T4> (*i++);
        T5 t5 = vcast <T5> (*i++);
        T6 t6 = vcast <T6> (*i++);
        T7 t7 = vcast <T7> (*i++);
        T8 t8 = vcast <T8> (*i);
        return Core::Variant (new K (t1, t2, t3, t4, t5, t6, t7, t8));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
class ConstructorPointer09 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 9; }
};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
Core::Variant ConstructorPointer09<K, T1, T2, T3, T4, T5, T6, T7, T8, T9>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 9);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i++);
        T4 t4 = vcast <T4> (*i++);
        T5 t5 = vcast <T5> (*i++);
        T6 t6 = vcast <T6> (*i++);
        T7 t7 = vcast <T7> (*i++);
        T8 t8 = vcast <T8> (*i++);
        T9 t9 = vcast <T9> (*i);
        return Core::Variant (new K (t1, t2, t3, t4, t5, t6, t7, t8, t9));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
class ConstructorPointer10 : public IConstructorPointer {
public:

        Core::Variant invoke (Core::VariantVector *list);
        std::type_info const &getType () const { return typeid (typename Core::normalize<T1>::type); }
        unsigned int getArity () const { return 10; }
};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
Core::Variant ConstructorPointer10<K, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::invoke (Core::VariantVector *list)
{
        Tools::checkArgList (list, 10);
        Core::VariantVector::iterator i = list->begin ();
        T1 t1 = vcast <T1> (*i++);
        T2 t2 = vcast <T2> (*i++);
        T3 t3 = vcast <T3> (*i++);
        T4 t4 = vcast <T4> (*i++);
        T5 t5 = vcast <T5> (*i++);
        T6 t6 = vcast <T6> (*i++);
        T7 t7 = vcast <T7> (*i++);
        T8 t8 = vcast <T8> (*i++);
        T9 t9 = vcast <T9> (*i++);
        T10 t10 = vcast <T10> (*i);
        return Core::Variant (new K (t1, t2, t3, t4, t5, t6, t7, t8, t9, t10));
}

/*##########################################################################*/

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
struct ConstructorPointerWrapper {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer10 <K, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> ();
        }

};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
struct ConstructorPointerWrapper <K, T1, T2, T3, T4, T5, T6, T7, T8, T9, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer09 <K, T1, T2, T3, T4, T5, T6, T7, T8, T9> ();
        }

};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
struct ConstructorPointerWrapper <K, T1, T2, T3, T4, T5, T6, T7, T8, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer08 <K, T1, T2, T3, T4, T5, T6, T7, T8> ();
        }

};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
struct ConstructorPointerWrapper <K, T1, T2, T3, T4, T5, T6, T7, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer07 <K, T1, T2, T3, T4, T5, T6, T7> ();
        }

};

template <class K, class T1, class T2, class T3, class T4, class T5, class T6>
struct ConstructorPointerWrapper <K, T1, T2, T3, T4, T5, T6, void, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer06 <K, T1, T2, T3, T4, T5, T6> ();
        }

};

template <class K, class T1, class T2, class T3, class T4, class T5>
struct ConstructorPointerWrapper <K, T1, T2, T3, T4, T5, void, void, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer05 <K, T1, T2, T3, T4, T5> ();
        }

};

template <class K, class T1, class T2, class T3, class T4>
struct ConstructorPointerWrapper <K, T1, T2, T3, T4, void, void, void, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer04 <K, T1, T2, T3, T4> ();
        }

};

template <class K, class T1, class T2, class T3>
struct ConstructorPointerWrapper <K, T1, T2, T3, void, void, void, void, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer03 <K, T1, T2, T3> ();
        }

};

template <class K, class T1, class T2>
struct ConstructorPointerWrapper <K, T1, T2, void, void, void, void, void, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer02 <K, T1, T2> ();
        }

};

template <class K, class T1>
struct ConstructorPointerWrapper <K, T1, void, void, void, void, void, void, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer01 <K, T1> ();
        }

};

template <class K>
struct ConstructorPointerWrapper <K, void, void, void, void, void, void, void, void, void, void> {

        static IConstructorPointer *newConstructorPointer () {
                return new ConstructorPointer00 <K> ();
        }

};

/*##########################################################################*/

template <class K,
          class T1 = void,
          class T2 = void,
          class T3 = void,
          class T4 = void,
          class T5 = void,
          class T6 = void,
          class T7 = void,
          class T8 = void,
          class T9 = void,
          class T10 = void>
struct ConstructorPointerWrapper2 {

        typedef ConstructorPointerWrapper <K, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> Level1Wrapper;

};

} // namespace

#endif

