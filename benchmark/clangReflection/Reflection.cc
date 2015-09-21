#include "reflection/Reflection.h"
#include "Reflection.h"

using namespace boost;
using namespace Core;
using namespace Reflection;

void instrumentation01 ()
{
        {
        Class *clazz = new Class ("Address", typeid (Address &), new Reflection::PtrDeleter <Address>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address::unit)));
        }

        {
        Class *clazz = new Class ("Address01", typeid (Address &), new Reflection::PtrDeleter <Address01>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address01, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address01::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address01::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address01::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address01::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address01::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address01::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address01::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address01::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address01::unit)));
        }

        {
        Class *clazz = new Class ("Address02", typeid (Address &), new Reflection::PtrDeleter <Address02>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address02, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address02::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address02::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address02::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address02::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address02::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address02::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address02::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address02::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address02::unit)));
        }

        {
        Class *clazz = new Class ("Address03", typeid (Address &), new Reflection::PtrDeleter <Address03>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address03, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address03::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address03::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address03::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address03::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address03::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address03::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address03::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address03::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address03::unit)));
        }

        {
        Class *clazz = new Class ("Address04", typeid (Address &), new Reflection::PtrDeleter <Address04>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address04, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address04::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address04::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address04::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address04::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address04::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address04::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address04::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address04::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address04::unit)));
        }

        {
        Class *clazz = new Class ("Address05", typeid (Address &), new Reflection::PtrDeleter <Address05>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address05, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address05::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address05::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address05::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address05::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address05::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address05::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address05::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address05::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address05::unit)));
        }

        {
        Class *clazz = new Class ("Address06", typeid (Address &), new Reflection::PtrDeleter <Address06>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address06, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address06::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address06::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address06::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address06::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address06::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address06::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address06::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address06::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address06::unit)));
        }

        {
        Class *clazz = new Class ("Address07", typeid (Address &), new Reflection::PtrDeleter <Address07>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address07, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address07::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address07::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address07::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address07::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address07::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address07::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address07::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address07::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address07::unit)));
        }

        {
        Class *clazz = new Class ("Address08", typeid (Address &), new Reflection::PtrDeleter <Address08>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address08, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address08::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address08::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address08::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address08::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address08::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address08::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address08::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address08::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address08::unit)));
        }

        {
        Class *clazz = new Class ("Address09", typeid (Address &), new Reflection::PtrDeleter <Address09>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address09, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address09::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address09::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address09::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address09::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address09::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address09::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address09::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address09::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address09::unit)));
        }

        {
        Class *clazz = new Class ("Address10", typeid (Address &), new Reflection::PtrDeleter <Address10>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Address10, void>::Level1Wrapper::newConstructorPointer ()));
        clazz->addField (new Field ("id", Reflection::createFieldWrapper (&Address10::id)));
        clazz->addField (new Field ("city", Reflection::createFieldWrapper (&Address10::city)));
        clazz->addField (new Field ("street", Reflection::createFieldWrapper (&Address10::street)));
        clazz->addField (new Field ("province", Reflection::createFieldWrapper (&Address10::province)));
        clazz->addField (new Field ("postalCode", Reflection::createFieldWrapper (&Address10::postalCode)));
        clazz->addField (new Field ("country", Reflection::createFieldWrapper (&Address10::country)));
        clazz->addField (new Field ("streetNumber", Reflection::createFieldWrapper (&Address10::streetNumber)));
        clazz->addField (new Field ("building", Reflection::createFieldWrapper (&Address10::building)));
        clazz->addField (new Field ("unit", Reflection::createFieldWrapper (&Address10::unit)));
        }

}
