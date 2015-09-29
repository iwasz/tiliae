/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TESTHELPERS_H_
#define TESTHELPERS_H_
#endif /* TESTHELPERS_H_ */

#include "ReflectionParserAnnotation.h"
#include "Address.h"
#include "Bar.h"
#include "City.h"
#include "Contractor.h"
#include "Country.h"
#include "Foo.h"
#include "Gender.h"
#include "Note.h"
#include "Place.h"
#include "Telephone.h"
#include "User.h"
#include "Helper.h"
#include "signal/Listener.h"
#include "XClass.h"
#include "TestFactories.h"
#include "DummyIEditor.h"
#include "container/beanFactory/BeanFactoryContainer.h"

// Those are only tests, so I can do this:
using namespace Container;
using namespace Signal;

namespace A {

        struct __tiliae_reflect__ Testowa {
                REFLECTION_END_ (Testowa)
        };

}

namespace B {

        struct __tiliae_reflect_token__ (B::Testowa) Testowa {
//                __ne (B::Testowa, BTestowa)
                REFLECTION_END_TOKEN_ (B::Testowa, B_Testowa)
        };
}

namespace C {

        struct __tiliae_reflect_token__ (C::Testowa) Testowa {
                REFLECTION_END_TOKEN_ (C::Testowa, C_Testowa)
        };

}

namespace D {

        struct __tiliae_reflect_token__ (D::Testowa) Testowa {
                REFLECTION_CONSTRUCTOR_ (void)
                REFLECTION_METHOD (f) void f () {}
                REFLECTION_END_TOKEN (D::Testowa, D_Testowa)
        };

}

namespace E {

        struct __tiliae_reflect__ Testowa01 {
                REFLECTION_CLASS
                REFLECTION_END (Testowa01)
        };

        struct __tiliae_reflect__ Testowa02 : public Core::Object {
                REFLECTION_CLASS
                virtual ~Testowa02 () {}

                REFLECTION_METHOD (f) virtual void f () = 0;

                REFLECTION_END (Testowa02)
        };

        struct __tiliae_reflect__ Testowa03 : public Testowa02 {
                REFLECTION_CONSTRUCTOR_ (void)
                REFLECTION_BASE_CLASS ("Testowa02")

                virtual ~Testowa03 () {}

                virtual void f () {}
                REFLECTION_METHOD (g) virtual void g () {}

                REFLECTION_END (Testowa03)
        };

        struct __tiliae_reflect__ Testowa04 : public Testowa03 {
                REFLECTION_CONSTRUCTOR_ (void)
                REFLECTION_BASE_CLASS ("Testowa03")

                virtual ~Testowa04 () {}

                REFLECTION_METHOD (h) virtual void h () {}

                REFLECTION_END (Testowa04)
        };

}

namespace F {

        template <typename T>
        struct Template {

                REFLECTION_CONSTRUCTOR_ (void)

                virtual ~Template () {}

                REFLECTION_METHOD (f) virtual void f () {}

        private:

                T t;

                REFLECTION_END_TOKEN (Template<int>, Template_int)
        };

/*--------------------------------------------------------------------------*/

        template <typename T>
        struct Template01 {

                REFLECTION_CONSTRUCTOR_ (void)

                virtual ~Template01 () {}

                REFLECTION_METHOD (setT) void setT (const T &t) { this->t = t; }
                REFLECTION_METHOD (getT) const T &getT () const { return t; }

                T t;

                REFLECTION_END_TOKEN (Template01<int>, Template01_int)
        };

/*--------------------------------------------------------------------------*/

#if 0
        template <typename T>
        struct Template02 {

                REFLECTION_CONSTRUCTOR_ (void)

                virtual ~Template02 () {}

                REFLECTION_METHOD (setT) void setT (const T &t) { this->t = t; }
                REFLECTION_METHOD (getT) const T &getT () const { return t; }

                T t;

                REFLECTION_TEMPLATE_BEGIN
                REFLECTION_TEMPLATE (Template02<int>)
                REFLECTION_TEMPLATE (Template02<double>)
                REFLECTION_TEMPLATE_END
        };
#endif
}



#define FV(x) REFLECTION_FIELD_VALUE_INPLACE(x)
#define FR(x) REFLECTION_FIELD_REFERENCE_INPLACE(x)

struct IY : public Core::Object {
        virtual ~IY () {}
};

struct Y2 : public IY {
        virtual ~Y2 () {}
};

/**
 *
 */
struct __tiliae_reflect__ Y : public IY {

        REFLECTION_CONSTRUCTOR_ (void);
        virtual ~Y () {}

        IY *getY () { return y; }

//private:

        double FV (d);
        std::string FV (s);
        int FV (i);
        IY *FV (y);

        REFLECTION_END(Y)
};

/**
 * Odbiera sygnał od buttona.
 */
struct __tiliae_reflect__ Handler {

        REFLECTION_CONSTRUCTOR_(void);

        Handler () :
                onClickedListener (this, "$onClicked ()", "clicked2"),
                onClickedListener2 (this, "$onClicked3 ()", "clicked3"),
                iValue (0) {}

        REFLECTION_METHOD (onClicked) void onClicked ()
        {
                iValue = 778890;
        }

        REFLECTION_METHOD (onClicked3) void onClicked3 ()
        {
                ++iValue;
        }

        Signal::Listener onClickedListener, onClickedListener2;
        int iValue;

        REFLECTION_END (Handler);
};

/**
 * Używana w następnym tescie.
 */
class __tiliae_reflect__ TestFactory : public Factory::IFactory {
public:

        virtual ~TestFactory () {}
        Core::Variant create (const Core::VariantMap &parameters, Core::DebugContext *context = NULL) const { return Core::Variant (new Core::StringMap); }
        REFLECTION_END_(TestFactory)
};

struct A02;

struct __tiliae_reflect__ A01 {
        REFLECTION_CONSTRUCTOR_ (void)
        A02 *a02;
        REFLECTION_METHOD (setA02) void setA02 (A02 *a) { a02 = a; }
        REFLECTION_END (A01)
};

struct __tiliae_reflect__ A02 {
        REFLECTION_CONSTRUCTOR_ (void)
        A01 *a01;
        REFLECTION_METHOD (setA01) void setA01 (A01 *a) { a01 = a; }
        REFLECTION_END (A02)
};

struct __tiliae_reflect__ A03 {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (BeanFactoryContainer *c) { cont = c; }

        BeanFactoryContainer *cont;

        REFLECTION_END (A03)
};

struct __tiliae_reflect__ A04 {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (BeanFactoryContainer *c) { cont = c; }

        BeanFactoryContainer *cont;

        REFLECTION_END (A04)
};

struct __tiliae_reflect__ Source {
        REFLECTION_CONSTRUCTOR_ (void)

        REFLECTION_METHOD (setCont)
        void setCont (BeanFactoryContainer *c) { cont = c; }

        BeanFactoryContainer *cont;

        REFLECTION_METHOD (init)
        void init ()
        {
                cont->addSingleton ("external1", Core::Variant ("Benek pies"));
                cont->addSingleton ("external2", Core::Variant ("Borys pies"));
        }

        REFLECTION_END (Source)
};

struct Dummy1;

typedef std::vector <Dummy1 *> DummyVector;
REFLECTION_COLLECTION (DummyVector)

struct __tiliae_reflect__ Dummy1 {

        REFLECTION_CONSTRUCTOR_ (void)
        Dummy1 () {}

        DummyVector REFLECTION_FIELD_REFERENCE_INPLACE (vector);

        REFLECTION_END (Dummy1)
};

struct A02c;

struct __tiliae_reflect__ A01c {
        REFLECTION_CONSTRUCTOR_ (void)
        A02c *a02;
        REFLECTION_METHOD (setA02) void setA02 (A02c *a) { a02 = a; }
        REFLECTION_END (A01c)
};

struct __tiliae_reflect__ A02c {
        REFLECTION_CONSTRUCTOR_ (void)
        A01c *a01;
        REFLECTION_METHOD (setA01) void setA01 (A01c *a) { a01 = a; }
        REFLECTION_END (A02c)
};

struct __tiliae_reflect__ Dummy {

        REFLECTION_CONSTRUCTOR_ (void)
        Dummy () {}

        REFLECTION_CONSTRUCTOR (Dummy *)
        Dummy (Dummy *d) : field1 (d) {}

        Dummy *REFLECTION_FIELD_VALUE_INPLACE (field1);
        Dummy *REFLECTION_FIELD_VALUE_INPLACE (field2);
        Dummy *REFLECTION_FIELD_VALUE_INPLACE (field3);

        REFLECTION_END (Dummy)
};

enum Type { TYPE1, TYPE2, TYPE3 };

struct __tiliae_reflect__ Dummy3 {

        REFLECTION_CONSTRUCTOR_ (void)
        Dummy3 () {}

        Type REFLECTION_FIELD_ENUM_INPLACE (field1);
        Type REFLECTION_FIELD_ENUM_INPLACE (field2);
        Type REFLECTION_FIELD_ENUM_INPLACE (field3);

        REFLECTION_END (Dummy3)
};

/**
 * Odbiera. W konstruktorze, lub gdzieś indziej należy włączyć
 * nasłuch, czyli inaczej "podłączyć" sygnał.
 */
struct __tiliae_reflect__ Receiver {

        REFLECTION_CONSTRUCTOR_(void);

        Receiver () : onClicked (this, "$onClicked1 ()", "clicked"),
                        onSig0 (this, "$handler2 (668)", "sig0"),
                        onSig1 (this, "$handler2 (%0)", "sig1"),
                        onSig2 (this, "$handler3 (%0, %1)", "sig2"),
                        iValue (0)
                        {}

        REFLECTION_METHOD (onClicked1) void onClicked1 () { iValue = 667; }
        REFLECTION_METHOD (handler2) void handler2 (int i) { iValue = i; }

        REFLECTION_METHOD (handler3) int handler3 (int i, const std::string &nam)
        {
                iValue = i;
                sValue = nam;
                return 666;
        }

        Listener onClicked, onSig0, onSig1, onSig2;
        int iValue;
        std::string sValue;

        REFLECTION_END (Receiver);
};

struct __tiliae_reflect__ Receiver2 {

        REFLECTION_CONSTRUCTOR_(void);

        Receiver2 () : onSig3 (this, "$handler2 (3)", "/scope/sig3"),
                        onSig4 (this, "$handler2 (4)", "/sig4"),
                        iValue (0)
                        {}

        REFLECTION_METHOD (handler2) void handler2 (int i)
        {
                iValue = i;
        }

        Listener onSig3, onSig4;
        int iValue;

        REFLECTION_END (Receiver2);
};

struct __tiliae_reflect__ Receiver3 {

        Receiver3 () : clck1 (this, "1"),
                        clck2 (this, "2", "/scpe/clck2") {}

        Listener clck1, clck2;
        REFLECTION_END_ (Receiver3);
};

