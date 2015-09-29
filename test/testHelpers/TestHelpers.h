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

namespace A {

        struct Testowa {
                REFLECTION_END_ (Testowa)
        };

}

namespace B {

        struct Testowa {
//                __ne (B::Testowa, BTestowa)
                REFLECTION_END_TOKEN_ (B::Testowa, B_Testowa)
        };

}

namespace C {

        struct Testowa {
//                __ne (C::Testowa, CTestowa)
                REFLECTION_END_TOKEN_ (C::Testowa, C_Testowa)
        };

}

namespace D {

        struct Testowa {
                REFLECTION_CONSTRUCTOR_ (void)
                REFLECTION_METHOD (f) void f () {}
                REFLECTION_END_TOKEN (D::Testowa, D_Testowa)
        };

}

namespace E {
        
        struct Testowa01 {
                REFLECTION_CLASS
                REFLECTION_END (Testowa01)
        };
                
        struct Testowa02 : public Core::Object {
                REFLECTION_CLASS
                virtual ~Testowa02 () {}
                
                REFLECTION_METHOD (f) virtual void f () = 0;
                
                REFLECTION_END (Testowa02)
        };      
                
        struct Testowa03 : public Testowa02 {
                REFLECTION_CONSTRUCTOR_ (void)
                REFLECTION_BASE_CLASS ("Testowa02")
                
                virtual ~Testowa03 () {}
                
                virtual void f () {}
                REFLECTION_METHOD (g) virtual void g () {}
                
                REFLECTION_END (Testowa03)
        };      
                
        struct Testowa04 : public Testowa03 {
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
struct Y : public IY {

        REFLECTION_CONSTRUCTOR_ (void);
        
        virtual ~Y () {}

        IY *getY () { return y; }
        
private:

        double FV (d);
        std::string FV (s);
        int FV (i);
        IY *FV (y);

        REFLECTION_END(Y)
};

/**
 * Odbiera sygnał od buttona.
 */
struct Handler {

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

        Listener onClickedListener, onClickedListener2;
        int iValue;

        REFLECTION_END (Handler);
};

