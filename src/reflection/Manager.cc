/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "core/Core.h"
#include <vector>
#include <string>
#include "reflection/Manager.h"
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
#include "visitor/ClassInternalsVisitor.h"
#include "core/variant/Cast.h"
#include "core/variant/Variant.h"
#include "core/Pointer.h"
#include "core/Typedefs.h"

namespace Reflection {
using namespace Annotations;
using namespace Core;

Manager::Manager () : initialized (false), classContainer (new ClassContainer ())
{
//        std::cerr << "Manager::Manager" << std::endl;
}

/****************************************************************************/

Manager::~Manager ()
{
        delete classContainer;
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
//        static Manager *neverDelete = new Manager ();
//        return *neverDelete;

        static Manager reflectionManager;
        return reflectionManager;
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

#ifdef WITH_ANNOTATIONS
        ClassVisitor classVisitor;
        ClassInternalsVisitor methodVisitor;

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
                Variant v = annotation->accept (&classVisitor);

                // Jakaś adnotacja bez klasy (w przyszłości).
                if (v.isNone ()) {
                        //continue;
                        /*
                         * TODO może kiedyś się to zmieni, albo już zostanie. Genralnie
                         * chodzi o to, że beż REFLECTION_CONSTRUCTOR_ na początku nie utworzy się w ogóle obiekt
                         * Class, z którego mogą korzystać pozostałe adnotacje. Każda adnotacja
                         * zawiera jaiieś tam informacj i każda ziwera inne. Adnotacja REFLECTION_METHOD, czy REFLECTION_BASE_CLASS
                         * nie zawiera wszystkich potrzebnych informacji do stworzenia nowego
                         * obiektu typu Class. Może uda się to zmienić? A jeśli nie to wywalić
                         * adnotacje REFLECTION_METHOD_ i REFLECTION_BASE_CLASS_.
                         */
                        throw AnnotationException ("No ClassAnnotation (1). You shoud use macro with double '__' as the first macro in annotated class. " + annotation->toString ());
                }

                Class *clazz = vcast <Class *> (v);

                // Jakaś adnotacja bez klasy (w przyszłości).
                if (!clazz) {
                        throw AnnotationException ("No ClassAnnotation (2). You shoud use macro with double '__' as the first macro in annotated class. " + annotation->toString ());
                }

                annotation->accept (&methodVisitor, clazz);
        }
#endif

        manager.initialized = true;
}

/****************************************************************************/

#define REFLECTION_ADD(type) { Class *clazz = new Class (#type, typeid (type &), new Reflection::PtrDeleter <type>);                        \
Manager::add (clazz);                                                                                                                     \
clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <type, type>::Level1Wrapper::newConstructorPointer ()));   \
clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <type, void>::Level1Wrapper::newConstructorPointer ())); }


void Manager::addStandardTypes ()
{
        // Simple types - scalars
        REFLECTION_ADD (int);
        REFLECTION_ADD (bool);
        REFLECTION_ADD (char);
        REFLECTION_ADD (signed char);
        REFLECTION_ADD (unsigned char);
        REFLECTION_ADD (double);
        REFLECTION_ADD (long double);
        REFLECTION_ADD (float);
        REFLECTION_ADD (unsigned int);
        REFLECTION_ADD (long int);
        REFLECTION_ADD (unsigned long int);
        REFLECTION_ADD (short int);
        REFLECTION_ADD (unsigned short int);

        {
        Class *clazz = new Class ("Variant", typeid (Core::Variant &), new Reflection::PtrDeleter <Core::Variant>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Core::Variant, Core::Variant const &>::Level1Wrapper::newConstructorPointer ()));
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Core::Variant, void>::Level1Wrapper::newConstructorPointer ()));
        }

        {
        Class *clazz = new Class ("string", typeid (std::string &), new Reflection::PtrDeleter <std::string>);
        Manager::add (clazz);
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <std::string, std::string const &>::Level1Wrapper::newConstructorPointer ()));
        clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <std::string, void>::Level1Wrapper::newConstructorPointer ()));
        }

        // Collection
        CollectionAnnotation <VariantList>::run ("VariantList");
        CollectionAnnotation <VariantVector>::run ("VariantVector");
        CollectionAnnotation <VariantMap>::run ("VariantMap");

#ifdef WITH_CORE_STRING
        CollectionAnnotation <UStringList>::run ("UStringList");
        CollectionAnnotation <UStringVector>::run ("UStringVector");
        CollectionAnnotation <UStringSet>::run ("UStringSet");
        CollectionAnnotation <UStringMap>::run ("UStringMap");
#endif

        CollectionAnnotation <StringVector>::run ("StringVector");
        CollectionAnnotation <StringList>::run ("StringList");
        CollectionAnnotation <StringSet>::run ("StringSet");
        CollectionAnnotation <StringMap>::run ("StringMap");

}

/****************************************************************************/

Class *Manager::classForName (const std::string &className)
{
        Manager::init (); // Run only once.
        return classForNameImpl (className);
}

/****************************************************************************/

Class *Manager::classForNameImpl (const std::string &className)
{
        return Manager::instance ().classContainer->get (className);
}

/****************************************************************************/

Class *Manager::classForType (std::type_info const &t)
{
        Manager::init (); // Run only once.
        return Manager::instance ().classContainer->get (t);
}

/****************************************************************************/

bool Manager::add (Class *c)
{
        return Manager::instance ().classContainer->add (c);
}

}
