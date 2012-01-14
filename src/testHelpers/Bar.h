/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAR_H_
#define BAR_H_

#include <list>
#include <map>
#include "City.h"
#include "Reflection.h"
#include "../core/string/String.h"
#include "../core/Pointer.h"
#include "../core/variant/Variant.h"
#include "../core/Exception.h"
#include <vector>
#include "../core/ApiMacro.h"

/****************************************************************************/

//#define MARK(a) std::cerr << #a << std::endl;
#define MARK(a)

/****************************************************************************/

/*

848B  - getter
4508B - setter!!!


 */

class TILIAE_API Bar {
public:

        c__ (const Core::String &, const std::string &, int, double, char, bool, char *)
        Bar (const Core::String &f0, const std::string &f1, int f2, double f3, char f4, bool f5, char *f6) :
    	    field0 (f0), field1 (f1), field2 (f2), field3 (f3), field4 (f4), field5 (f5), field6 (f6)
    	    {
    	    }

        c_ (const Core::String &, const std::string &, Ptr <City>)
        Bar (const Core::String &f0, const std::string &f1, Ptr <City> c) :
            field0 (f0), field1 (f1), city (c)
        {
                field6 = NULL;
        }

        c_ (const Core::Variant &)
        Bar (const Core::Variant &b) : butter (b)
        {
                city = Ptr <City> (new City ());
                field6 = NULL;
        }

        virtual ~Bar () {}

        m_ (getField0) Core::String getField0 () const { return field0; }
        m_ (setField0) void setField0 (const Core::String &field0) { this->field0 = field0; }

        m_ (getField1) std::string getField1 () const { return field1; }
        m_ (setField1) void setField1 (const std::string &field1) { this->field1 = field1; }

        m_ (getField2) int getField2 () const { return field2; }
        m_ (setField2) void setField2 (int field2) { this->field2 = field2; }

        m_ (getField3) double getField3 () const { return field3; }
        m_ (setField3) void setField3 (double field3) { this->field3 = field3; }

        m_ (getField4) char getField4 () const { return field4; }
        m_ (setField4) void setField4 (char field4) { this->field4 = field4; }

        m_ (getField5) bool getField5 () const { return field5; }
        m_ (setField5) void setField5 (bool field5) { this->field5 = field5; }

        m_ (getField6) char *getField6 () const { return field6; }

        m_ (getCity) Ptr <City> getCity () const { return city; }
        m_ (setCity) void setCity (Ptr <City> city) { this->city = city; }

        /*
         * To jest narazie nie obsługiwane przez kontener, ponieważ
         * kontener tworzy obiekt City jako City *, a nie Ptr <City>
         * i kastowanie nie udaje się. To ulegnie zmianie po dorobieniu
         * odpowiedniej opcji do Variant.
         */
        m_ (getCity2); Ptr <City> getCity2 () const { return city2; }
        m_ (setCity2); void setCity2 (Ptr <City> city) { this->city2 = city; }

        m_ (getCity3) Ptr <City> getCity3 () const { return city3; }
        m_ (setCity3) void setCity3 (Ptr <City> city) { MARK(setCity3); this->city3 = city; }

        m_ (setAaaby) void setAaaby (Ptr <City> city) { MARK(aaaby); if (!city3) { throw Core::Exception (); } }

        m_ (getButter); Core::Variant getButter() const { return butter; }
        m_ (setButter); void setButter (const Core::Variant &butter) { this->butter = butter; }

        m_ (getButter2); Core::Variant getButter2() const { return butter2; }
        m_ (setButter2); void setButter2 (const Core::Variant &butter) { this->butter2 = butter; }

        m_ (funcA); void funcA (int i) { field0 = Core::String ("funcA ") + i; }
        m_ (funcB); void funcB (int i, const Core::String &s) { field0 = Core::String ("funcB ") + i + ", " + s; }
//        m_ (funcC); void funcC (int i, double d, bool b) { field0 = Core::String ("funcC ") + i + ", " + d + ", " + b; }
        m_ (funcD); bool funcD () { field0 = Core::String ("funcD "); return false; }

private:

        Core::String field0;
        std::string field1;
        int field2;
        double field3;
        char field4;
        bool field5;
        char *field6;
        Ptr <City> city;
        Ptr <City> city3;
        Ptr <City> city2;
        Core::Variant butter;
        Core::Variant butter2;

        e_ (Bar)
};

typedef std::vector <Ptr <Bar> > BarVector;
g_ (BarVector)

typedef std::list <Ptr <Bar> > BarList;
g_ (BarList)

typedef std::map <std::string, Ptr <Bar> > BarMap;
g_ (BarMap)

#endif /* FOO_H_ */
