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
#include <string>
#include "City.h"
#include "reflection/Reflection.h"
#include "core/Pointer.h"
#include "core/variant/Variant.h"
#include "core/Exception.h"
#include <vector>
#include "core/ApiMacro.h"
#include <boost/lexical_cast.hpp>

// TODO Czemu parser generuje z _Bool, dowiedzieć się, usunąć.
#define _Bool bool

/****************************************************************************/

//#define MARK(a) std::cerr << #a << std::endl;
#define MARK(a)

/****************************************************************************/

class TILIAE_API __tiliae_reflect__ Bar {
public:

        REFLECTION_CONSTRUCTOR_ (const std::string &, const std::string &, int, double, char, bool, char *)
        Bar (const std::string &f0, const std::string &f1, int f2, double f3, char f4, bool f5, char *f6) :
            field0 (f0), field1 (f1), field2 (f2), field3 (f3), field4 (f4), field5 (f5), field6 (f6)
            {
            }

        REFLECTION_CONSTRUCTOR (const std::string &, const std::string &, Ptr <City>)
        Bar (const std::string &f0, const std::string &f1, Ptr <City> c) :
            field0 (f0), field1 (f1), city (c)
        {
                field6 = NULL;
        }

        REFLECTION_CONSTRUCTOR (const Core::Variant &)
        Bar (const Core::Variant &b) : butter (b)
        {
                city = Ptr <City> (new City ());
                field6 = NULL;
        }

        virtual ~Bar () {}

        REFLECTION_METHOD (getField0) std::string getField0 () const { return field0; }
        REFLECTION_METHOD (setField0) void setField0 (const std::string &field0) { this->field0 = field0; }

        REFLECTION_METHOD (getField1) std::string getField1 () const { return field1; }
        REFLECTION_METHOD (setField1) void setField1 (const std::string &field1) { this->field1 = field1; }

        REFLECTION_METHOD (getField2) int getField2 () const { return field2; }
        REFLECTION_METHOD (setField2) void setField2 (int field2) { this->field2 = field2; }

        REFLECTION_METHOD (getField3) double getField3 () const { return field3; }
        REFLECTION_METHOD (setField3) void setField3 (double field3) { this->field3 = field3; }

        REFLECTION_METHOD (getField4) char getField4 () const { return field4; }
        REFLECTION_METHOD (setField4) void setField4 (char field4) { this->field4 = field4; }

        REFLECTION_METHOD (getField5) bool getField5 () const { return field5; }
        REFLECTION_METHOD (setField5) void setField5 (bool field5) { this->field5 = field5; }

        REFLECTION_METHOD (getField6) char *getField6 () const { return field6; }

        REFLECTION_METHOD (getCity) Ptr <City> getCity () const { return city; }
        REFLECTION_METHOD (setCity) void setCity (Ptr <City> city) { this->city = city; }

        /*
         * To jest narazie nie obsługiwane przez kontener, ponieważ
         * kontener tworzy obiekt City jako City *, a nie Ptr <City>
         * i kastowanie nie udaje się. To ulegnie zmianie po dorobieniu
         * odpowiedniej opcji do Variant.
         */
        REFLECTION_METHOD (getCity2); Ptr <City> getCity2 () const { return city2; }
        REFLECTION_METHOD (setCity2); void setCity2 (Ptr <City> city) { this->city2 = city; }

        REFLECTION_METHOD (getCity3) Ptr <City> getCity3 () const { return city3; }
        REFLECTION_METHOD (setCity3) void setCity3 (Ptr <City> city) { MARK(setCity3); this->city3 = city; }

        City *getCity4 () { return city4; }
        City *getCity5 () { return city5; }

        REFLECTION_METHOD (setAaaby) void setAaaby (Ptr <City> city) { MARK(aaaby); if (!city3) { throw Core::Exception (); } }

        REFLECTION_METHOD (getButter); Core::Variant getButter() const { return butter; }
        REFLECTION_METHOD (setButter); void setButter (const Core::Variant &butter) { this->butter = butter; }

        REFLECTION_METHOD (getButter2); Core::Variant getButter2() const { return butter2; }
        REFLECTION_METHOD (setButter2); void setButter2 (const Core::Variant &butter) { this->butter2 = butter; }

        REFLECTION_METHOD (funcA); void funcA (int i) { field0 = std::string ("funcA ") + boost::lexical_cast <std::string> (i); }
        REFLECTION_METHOD (funcB); void funcB (int i, const std::string &s) { field0 = std::string ("funcB ") + boost::lexical_cast <std::string> (i) + ", " + s; }
        REFLECTION_METHOD (funcD); bool funcD () { field0 = std::string ("funcD "); return false; }

private:

        std::string field0;
        std::string field1;
        int field2;
        double field3;
        char field4;
        bool field5;
        char *field6;
        Ptr <City> city;
        Ptr <City> city2;
        Ptr <City> city3;
        City *REFLECTION_FIELD_VALUE_INPLACE (city4);
        City *REFLECTION_FIELD_VALUE_INPLACE (city5);
        Core::Variant butter;
        Core::Variant butter2;

        REFLECTION_END (Bar)
};

typedef std::vector <Ptr <Bar> > BarVector;
REFLECTION_COLLECTION (BarVector)

typedef std::list <Ptr <Bar> > BarList;
REFLECTION_COLLECTION (BarList)

typedef std::list <Bar *> BarListPtr;
REFLECTION_COLLECTION (BarListPtr)

typedef std::map <std::string, Ptr <Bar> > BarMap;
REFLECTION_COLLECTION (BarMap)

#endif /* FOO_H_ */
