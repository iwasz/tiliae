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

        REFLECTION_CONSTRUCTOR_ (void)

        Foo ()
        {
                Ptr <Address> tmp (new Address ());
                tmp->setStreet ("test02-66");
                addr2 = tmp;
        }

        virtual ~Foo () {}

        REFLECTION_METHOD (getField0) Core::String getField0 () const { return field0; }
        REFLECTION_METHOD (setField0) void setField0 (const Core::String &field0) { this->field0 = field0; }

        REFLECTION_METHOD (getField1) Core::String getField1 () const { return field1; }
        REFLECTION_METHOD (setField1) void setField1 (const Core::String &field1) { this->field1 = field1; }

        REFLECTION_METHOD (getField2) int getField2 () const { return field2; }
        REFLECTION_METHOD (setField2) void setField2 (int field2) { this->field2 = field2; }

        REFLECTION_METHOD (getField3) double getField3 () const { return field3; }
        REFLECTION_METHOD (setField3) void setField3 (double field3) { this->field3 = field3; }

        REFLECTION_METHOD (getField4) char getField4 () const { return field4; }
        REFLECTION_METHOD (setField4) void setField4 (char field4) { this->field4 = field4; }

        REFLECTION_METHOD (getField5) bool getField5 () const { return field5; }
        REFLECTION_METHOD (setField5) void setField5 (bool field5) { this->field5 = field5; }

        REFLECTION_METHOD (getField6) char *getField6 () const { return field6; }
        REFLECTION_METHOD (setField6) void setField6 (char *field6) { this->field6 = field6; }

        REFLECTION_METHOD (getCity)   Ptr <City> getCity () const { return city; }
        REFLECTION_SETTER (setCity)   void setCity (Ptr <City> city) { this->city = city; }

        /*
         * To jest narazie nie obsługiwane przez kontener, ponieważ
         * kontener tworzy obiekt City jako City *, a nie Ptr <City>
         * i kastowanie nie udaje się. To ulegnie zmianie po dorobieniu
         * odpowiedniej opcji do Variant.
         */
        REFLECTION_METHOD (getCity2); Ptr <City> getCity2 () const { return city2; }
        REFLECTION_METHOD (setCity2); void setCity2 (Ptr <City> city) { this->city2 = city; }

        REFLECTION_METHOD (getPlace) Place *getPlace () { return &addr; }
        Address addr;

        REFLECTION_METHOD (getPlace2) Ptr <Place> getPlace2 () { return addr2; }
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

        REFLECTION_END (Foo);
};

#endif /* FOO_H_ */