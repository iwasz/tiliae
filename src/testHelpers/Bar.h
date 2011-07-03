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

        __c (const Core::String &, const std::string &, int, double, char, bool, char *)
        Bar (const Core::String &f0, const std::string &f1, int f2, double f3, char f4, bool f5, char *f6) :
    	    field0 (f0), field1 (f1), field2 (f2), field3 (f3), field4 (f4), field5 (f5), field6 (f6)
    	    {
    	    }

        _c (const Core::String &, const std::string &, Ptr <City>)
        Bar (const Core::String &f0, const std::string &f1, Ptr <City> c) :
            field0 (f0), field1 (f1), city (c)
        {
                field6 = NULL;
        }

        _c (const Core::Variant &)
        Bar (const Core::Variant &b) : butter (b)
        {
                city = Ptr <City> (new City ());
                field6 = NULL;
        }

        virtual ~Bar () {}

        _m (getField0) Core::String getField0 () const { return field0; }
        _m (setField0) void setField0 (const Core::String &field0) { this->field0 = field0; }

        _m (getField1) std::string getField1 () const { return field1; }
        _m (setField1) void setField1 (const std::string &field1) { this->field1 = field1; }

        _m (getField2) int getField2 () const { return field2; }
        _m (setField2) void setField2 (int field2) { this->field2 = field2; }

        _m (getField3) double getField3 () const { return field3; }
        _m (setField3) void setField3 (double field3) { this->field3 = field3; }

        _m (getField4) char getField4 () const { return field4; }
        _m (setField4) void setField4 (char field4) { this->field4 = field4; }

        _m (getField5) bool getField5 () const { return field5; }
        _m (setField5) void setField5 (bool field5) { this->field5 = field5; }

        _m (getField6) char *getField6 () const { return field6; }

        _m (getCity) Ptr <City> getCity () const { return city; }
        _m (setCity) void setCity (Ptr <City> city) { this->city = city; }

        /*
         * To jest narazie nie obsługiwane przez kontener, ponieważ
         * kontener tworzy obiekt City jako City *, a nie Ptr <City>
         * i kastowanie nie udaje się. To ulegnie zmianie po dorobieniu
         * odpowiedniej opcji do Variant.
         */
        _m (getCity2); Ptr <City> getCity2 () const { return city2; }
        _m (setCity2); void setCity2 (Ptr <City> city) { this->city2 = city; }

        _m (getCity3) Ptr <City> getCity3 () const { return city3; }
        _m (setCity3) void setCity3 (Ptr <City> city) { MARK(setCity3); this->city3 = city; }

        _m (setAaaby) void setAaaby (Ptr <City> city) { MARK(aaaby); if (!city3) { throw Core::Exception (); } }

        _m (getButter); Core::Variant getButter() const { return butter; }
        _m (setButter); void setButter (const Core::Variant &butter) { this->butter = butter; }

        _m (getButter2); Core::Variant getButter2() const { return butter2; }
        _m (setButter2); void setButter2 (const Core::Variant &butter) { this->butter2 = butter; }

        _m (funcA); void funcA (int i) { field0 = Core::String ("funcA ") + i; }
        _m (funcB); void funcB (int i, const Core::String &s) { field0 = Core::String ("funcB ") + i + ", " + s; }
//        _m (funcC); void funcC (int i, double d, bool b) { field0 = Core::String ("funcC ") + i + ", " + d + ", " + b; }
        _m (funcD); bool funcD () { field0 = Core::String ("funcD "); return false; }

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

        _e (Bar)
};

typedef std::vector <Ptr <Bar> > BarVector;
_g (BarVector)

typedef std::list <Ptr <Bar> > BarList;
_g (BarList)

typedef std::map <std::string, Ptr <Bar> > BarMap;
_g (BarMap)

#endif /* FOO_H_ */
