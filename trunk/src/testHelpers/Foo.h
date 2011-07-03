/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FOO_H_
#define FOO_H_

#include "City.h"
#include "Reflection.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API Foo {
public:

        __c (void)

        Foo ()
        {
                Ptr <Address> tmp (new Address ());
                tmp->setStreet ("test02-66");
                addr2 = tmp;
        }

        virtual ~Foo () {}

        _m (getField0) Core::String getField0 () const { return field0; }
        _m (setField0) void setField0 (const Core::String &field0) { this->field0 = field0; }

        _m (getField1) Core::String getField1 () const { return field1; }
        _m (setField1) void setField1 (const Core::String &field1) { this->field1 = field1; }

        _m (getField2) int getField2 () const { return field2; }
        _m (setField2) void setField2 (int field2) { this->field2 = field2; }

        _m (getField3) double getField3 () const { return field3; }
        _m (setField3) void setField3 (double field3) { this->field3 = field3; }

        _m (getField4) char getField4 () const { return field4; }
        _m (setField4) void setField4 (char field4) { this->field4 = field4; }

        _m (getField5) bool getField5 () const { return field5; }
        _m (setField5) void setField5 (bool field5) { this->field5 = field5; }

        _m (getField6) char *getField6 () const { return field6; }
        _m (setField6) void setField6 (char *field6) { this->field6 = field6; }

        _m (getCity)   Ptr <City> getCity () const { return city; }
        _s (setCity)   void setCity (Ptr <City> city) { this->city = city; }

        /*
         * To jest narazie nie obsługiwane przez kontener, ponieważ
         * kontener tworzy obiekt City jako City *, a nie Ptr <City>
         * i kastowanie nie udaje się. To ulegnie zmianie po dorobieniu
         * odpowiedniej opcji do Variant.
         */
        _m (getCity2); Ptr <City> getCity2 () const { return city2; }
        _m (setCity2); void setCity2 (Ptr <City> city) { this->city2 = city; }

        _m (getPlace) Place *getPlace () { return &addr; }
        Address addr;

        _m (getPlace2) Ptr <Place> getPlace2 () { return addr2; }
        Ptr <Place> addr2;

private:

        Core::String field0;
        Core::String field1;
        int field2;
        double field3;
        char field4;
        bool field5;
        char *field6;
        Ptr <City> city;
        Ptr <City> city2;

        _e (Foo);
};

#endif /* FOO_H_ */
