/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Core.h>
#include <vector>
#include <string>

#include "Manager.h"
#include "ClassContainer.h"
#include "Exceptions.h"
#include "annotations/AnnotationManager.h"
#include "reflectAnnotations/BaseClassAnnotation.h"
#include "reflectAnnotations/MethodAnnotation.h"
#include "reflectAnnotations/ConstructorAnnotation.h"
#include "reflectAnnotations/ClassAnnotation.h"
#include "reflectAnnotations/CollectionAnnotation.h"
#include "model/Class.h"
#include "model/Constructor.h"
#include "model/Method.h"

#include "visitor/ClassVisitor.h"
#include "visitor/MethodVisitor.h"
#include "visitor/BaseClassVisitor.h"
#include "visitor/ConstructorVisitor.h"
#include "../core/variant/Cast.h"
#include "../core/variant/Variant.h"
#include "../core/Pointer.h"
#include "../core/Typedefs.h"

namespace Reflection {
using namespace Annotations;
using namespace Core;

Manager::Manager () : initialized (false), classContainer (new ClassContainer ())
{
//        std::cerr << "Manager::Manager" << std::endl;
}

/****************************************************************************/

std::string Manager::toString () const
{
        return std::string ("Manager (ClassContainer:") + classContainer->toString() + ")";
}

/*
 * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.12
 * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.13
 * http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.14
 */
Manager &Manager::instance ()
{
        static Manager *neverDelete = new Manager ();
        return *neverDelete;
}

/****************************************************************************/

void Manager::init ()
{
        Manager &manager = Manager::instance ();

        // 0. Jeśli zainicjowane, spadamy stąd.
        if (manager.initialized) {
                return;
        }

        addStandardTypes ();

        Ptr <ClassVisitor> classVisitor (new ClassVisitor);
        Ptr <ConstructorVisitor> constructorVisitor (new ConstructorVisitor);
        Ptr <MethodVisitor> methodVisitor (new MethodVisitor);
        Ptr <BaseClassVisitor> baseClassVisitor (new BaseClassVisitor);

        // 1. Przeiterować po AnnotationManagerze
        const AnnotationList &annotationList = AnnotationManager::instance ().getAnnotationList ();

        typedef AnnotationList::nth_index<1>::type::iterator Iterator1;

        for (Iterator1 i = annotationList.get<1> ().begin (); i != annotationList.get<1> ().end (); ++i) {

                IReflectionAnnotation *annotation = dynamic_cast <IReflectionAnnotation *> (*i);

                /*
                 * No niestety, ale mogą być też i inne adnotacje,
                 * które nie są IReflectionAnnotation (w przyszłości).
                 */
                if (!annotation) {
                        continue;
                }

#if 0
                std::cerr << annotation->toString () << std::endl;
#endif

                /*
                 * Stworzy klasę, albo poprostu ją znajdzie w managerze,
                 * jeśli już jest stworzona. ClassVisitor ma cache, więc
                 * nie odpytuje Managera za każdym razem.
                 */
                Variant v = annotation->accept (classVisitor.get ());

                // Jakaś adnotacja bez klasy (w przyszłości).
                if (v.isNone ()) {
                        //continue;
                        /*
                         * TODO może kiedyś się to zmieni, albo już zostanie. Genralnie
                         * chodzi o to, że beż __c na początku nie utworzy się w ogóle obiekt
                         * Class, z którego mogą korzystać pozostałe adnotacje. Każda adnotacja
                         * zawiera jaiieś tam informacj i każda ziwera inne. Adnotacja _m, czy _b
                         * nie zawiera wszystkich potrzebnych informacji do stworzenia nowego
                         * obiektu typu Class. Może uda się to zmienić? A jeśli nie to wyjebać
                         * adnotacje __m i __b.
                         */
                        throw AnnotationException ("No ClassAnnotation (1). You shoud use macro with double '__' as the first macro in annotated class. " + annotation->toString ());

//                        // Zwrócenie pustego warianta oznacza, że dana klasa już znajduje się w managerze.
//                        continue;
                }

                Ptr <Class> clazz = vcast <Ptr <Class> > (v);

                // Jakaś adnotacja bez klasy (w przyszłości).
                if (!clazz) {
                        //continue;
                        throw AnnotationException ("No ClassAnnotation (2). You shoud use macro with double '__' as the first macro in annotated class. " + annotation->toString ());
                }

                // Mając obiekt Class jeśli:
                // Adnotacja dotyczy konstruktora, stworzyć obiekt Constructor, dodać do Class.
                v = annotation->accept (constructorVisitor.get ());

                if (!v.isNone ()) {
                        clazz->addConstructor (vcast <Ptr <Constructor> > (v));
                }

                // Adnotacja dotyczy metody, stworzyć obiekt Method, dodać do Class.
                v = annotation->accept (methodVisitor.get ());

                if (!v.isNone ()) {
                        clazz->addMethod (vcast <Ptr <Method> > (v));
                }

                // Adnotacja dotyczy baseClass;
                v = annotation->accept (baseClassVisitor.get ());

                if (!v.isNone ()) {
                        clazz->addBaseClassNames (vcast <StringList> (v));
                }
        }

        manager.initialized = true;
}

/****************************************************************************/

void Manager::addStandardTypes ()
{
//        // Simple types - scalars
        REFLECTION_CLASS_ANNOTATION ("int", int);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("int", int, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("int", int, int);

        REFLECTION_CLASS_ANNOTATION ("bool", bool);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("bool", bool, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("bool", bool, bool);

        REFLECTION_CLASS_ANNOTATION ("char", char);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("char", char, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("char", char, char);

        REFLECTION_CLASS_ANNOTATION ("signed char", signed char);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("signed char", signed char, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("signed char", signed char, signed char);

        REFLECTION_CLASS_ANNOTATION ("unsigned char", unsigned char);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned char", unsigned char, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned char", unsigned char, unsigned char);

        REFLECTION_CLASS_ANNOTATION ("double", double);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("double", double, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("double", double, double);

        REFLECTION_CLASS_ANNOTATION ("long double", long double);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("long double", long double, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("long double", long double, long double);

        REFLECTION_CLASS_ANNOTATION ("float", float);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("float", float, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("float", float, float);

        REFLECTION_CLASS_ANNOTATION ("unsigned int", unsigned int);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned int", unsigned int, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned int", unsigned int, unsigned int);

        REFLECTION_CLASS_ANNOTATION ("long int", long int);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("long int", long int, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("long int", long int, long int);

        REFLECTION_CLASS_ANNOTATION ("unsigned long int", unsigned long int);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned long int", unsigned long int, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned long int", unsigned long int, unsigned long int);

        REFLECTION_CLASS_ANNOTATION ("short int", short int);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("short int", short int, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("short int", short int, short int);

        REFLECTION_CLASS_ANNOTATION ("unsigned short int", unsigned short int);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned short int", unsigned short int, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("unsigned short int", unsigned short int, unsigned short int);

        // Variant
        REFLECTION_CLASS_ANNOTATION ("Variant", Core::Variant);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("Variant", Core::Variant, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("Variant", Core::Variant, const Core::Variant &);

        REFLECTION_CLASS_ANNOTATION ("String", Core::String);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("String", Core::String, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("String", Core::String, const Core::String &);

        REFLECTION_CLASS_ANNOTATION ("string", std::string);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("string", std::string, void);
        REFLECTION_CONSTRUCTOR_ANNOTATION ("string", std::string, std::string);

        // Collection
        CollectionAnnotation <VariantList>::run ("VariantList");
        CollectionAnnotation <VariantVector>::run ("VariantVector");
        CollectionAnnotation <VariantMap>::run ("VariantMap");

        CollectionAnnotation <UStringList>::run ("UStringList");
        CollectionAnnotation <UStringVector>::run ("UStringVector");
        CollectionAnnotation <UStringSet>::run ("UStringSet");
        CollectionAnnotation <UStringMap>::run ("UStringMap");

        CollectionAnnotation <StringVector>::run ("StringVector");
        CollectionAnnotation <StringList>::run ("StringList");
        CollectionAnnotation <StringSet>::run ("StringSet");
        CollectionAnnotation <StringMap>::run ("StringMap");

}

/****************************************************************************/

Ptr<Class> Manager::classForName (const std::string &className)
{
        Manager::init (); // Run only once.
        return classForNameImpl (className);
}

/****************************************************************************/

Ptr<Class> Manager::classForNameImpl (const std::string &className)
{
        return Manager::instance ().classContainer->get (className);
}

/****************************************************************************/

Ptr<Class> Manager::classForType (std::type_info const &t)
{
        Manager::init (); // Run only once.
        return Manager::instance ().classContainer->get (t);
}

/****************************************************************************/

void Manager::add (Ptr <Class> c)
{
        Manager::instance ().classContainer->add (c);
}

}