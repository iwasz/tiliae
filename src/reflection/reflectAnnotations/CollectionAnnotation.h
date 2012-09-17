/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COLLECTIONANNOTATION_H_
#define COLLECTIONANNOTATION_H_

#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <set>
#include <boost/make_shared.hpp>

#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "reflection/wrapper/ICallableWrapper.h"
#include "reflection/model/Class.h"
#include "reflection/Manager.h"
#include "reflection/model/Method.h"
#include "reflection/model/Constructor.h"
#include "reflection/wrapper/AddWrapper.h"
#include "reflection/wrapper/GetWrapper.h"
#include "reflection/wrapper/SetWrapper.h"
#include "reflection/wrapper/IteratorWrapper.h"
#include "reflection/annotations/Macros.h"

/*##########################################################################*/

/**
 * Adnotacja kolekcji. Ta adnotacja służy do dodawania jednego z dozwolonych typó kolekcji do
 * refleksji. Użycie jest na przykład takie (w pliku .h lub .cc):
 *
 * <pre>
 * REFLECTION_COLLECTION (std::list<std::string>)
 * </pre>
 *
 * A ładnie wygląda jak się zrobi typedef :
 *
 * <pre>
 * typedef std::list<std::string> StringList;
 * REFLECTION_COLLECTION (StringList)
 * </pre>
 *
 * Dozwolone kolekcji, to wszystkie typy, dla których stworzyłem częściową specjalizację
 * szablonu ClassAnotation (w tym pliku poniżej).
 */
#ifdef REFLECTION_ENABLED
#define REFLECTION_COLLECTION(type) \
        ANNOTATION_RUN_ONCE_AT_STARTUP(::Reflection::CollectionAnnotation <type >::run (#type);)
#else
#define REFLECTION_COLLECTION(type)
#endif

/**
 * Adnotacja kolekcji. Ta adnotacja służy do dodawania jednego z dozwolonych typó kolekcji do
 * refleksji. Użycie jest na przykład takie (w pliku .h lub .cc):
 *
 * <pre>
 * _gn (std::list<std::string>, "StringList")
 * </pre>
 *
 * A ładnie wygląda jak się zrobi typedef :
 *
 * <pre>
 * typedef std::list<std::string> StringList;
 * _gn (StringList, "my_list")
 * </pre>
 *
 * Dozwolone kolekcji, to wszystkie typy, dla których stworzyłem częściową specjalizację
 * szablonu ClassAnotation (w tym pliku poniżej).
 */
#ifdef REFLECTION_ENABLED
#define REFLECTION_COLLECTION_NAME(type,name) \
        ANNOTATION_RUN_ONCE_AT_STARTUP(::Reflection::CollectionAnnotation <type >::run (name);)
#else
#define REFLECTION_COLLECTION_NAME(type,name)
#endif

namespace Reflection {

template <typename>
struct CollectionAnnotation {};

/*##########################################################################*/

template <typename T>
struct CollectionAnnotation <std::vector <T> > {
	static void run (std::string const &className);
};

template <typename T>
void CollectionAnnotation <std::vector <T> >::run (std::string const &className)
{
        // Sama klasa
        Class *clazz = new Class (className, typeid (std::vector <T>&), new PtrDeleter <std::vector <T> >);

        if (!Manager::add (clazz)) {
                delete clazz;
                return;
        }

        // Konstruktor
        IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <std::vector <T>, void>::Level1Wrapper::newConstructorPointer ();
        Constructor *constructor = new Constructor (cp);
        clazz->addConstructor (constructor);

        // Metody
        ICallableWrapper *w = new AddWrapper <std::vector <T> > ();
        Method *method = new Method ("add", w);
        clazz->addMethod (method);

        w = new GetWrapper <std::vector <T> > ();
        method = new Method ("get", w);
        clazz->addMethod (method);

        w = new SetWrapper <std::vector <T> > ();
        method = new Method ("set", w);
        clazz->addMethod (method);

        w = new IteratorWrapper <std::vector <T> > ();
        method = new Method ("iterator", w);
        clazz->addMethod (method);
}

/*##########################################################################*/

template <typename T>
struct CollectionAnnotation <std::list <T> > {
	static void run (std::string const &className);
};

template <typename T>
void CollectionAnnotation <std::list <T> >::run (std::string const &className)
{
        // Sama klasa
        Class *clazz = new Class (className, typeid (std::list <T> &), new PtrDeleter <std::list <T> >);
        if (!Manager::add (clazz)) {
                delete clazz;
                return;
        }

        // Konstruktor
        IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <std::list <T>, void>::Level1Wrapper::newConstructorPointer ();
        Constructor *constructor = new Constructor (cp);
        clazz->addConstructor (constructor);

        // Metody
        ICallableWrapper *w = new AddWrapper <std::list <T> > ();
        Method *method = new Method ("add", w);
        clazz->addMethod (method);

        w = new GetWrapper <std::list <T> > ();
        method = new Method ("get", w);
        clazz->addMethod (method);

        w = new SetWrapper <std::list <T> > ();
        method = new Method ("set", w);
        clazz->addMethod (method);

        w = new IteratorWrapper <std::list <T> > ();
        method = new Method ("iterator", w);
        clazz->addMethod (method);
}

/*##########################################################################*/

template <typename T>
struct CollectionAnnotation <std::set <T> > {
	static void run (std::string const &className);
};

template <typename T>
void CollectionAnnotation <std::set <T> >::run (std::string const &className)
{
        // Sama klasa
        Class *clazz = new Class (className, typeid (std::set <T>&), new PtrDeleter <std::set <T> >);
        if (!Manager::add (clazz)) {
                delete clazz;
                return;
        }

        // Konstruktor
        IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <std::set <T>, void>::Level1Wrapper::newConstructorPointer ();
        Constructor *constructor = new Constructor (cp);
        clazz->addConstructor (constructor);

        // Metody
        ICallableWrapper *w = new AddWrapper <std::set <T> > ();
        Method *method = new Method ("add", w);
        clazz->addMethod (method);

        w = new GetWrapper <std::set <T> > ();
        method = new Method ("get", w);
        clazz->addMethod (method);

        w = new IteratorWrapper <std::set <T> > ();
        method = new Method ("iterator", w);
        clazz->addMethod (method);
}

/*##########################################################################*/

template <typename K, typename V>
struct CollectionAnnotation <std::map <K, V> > {
	static void run (std::string const &className);
};

template <typename K, typename V>
void CollectionAnnotation <std::map <K, V> >::run (std::string const &className)
{
        // Sama klasa
        Class *clazz = new Class (className, typeid (std::map <K,V>&), new PtrDeleter <std::map <K,V> >);
        if (!Manager::add (clazz)) {
                delete clazz;
                return;
        }

        // Konstruktor
        IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <std::map <K, V>, void>::Level1Wrapper::newConstructorPointer ();
        Constructor *constructor = new Constructor (cp);
        clazz->addConstructor (constructor);

        // Metody
        ICallableWrapper *w = new SetWrapper <std::map <K, V> > ();
        Method *method = new Method ("set", w);
        clazz->addMethod (method);

        w = new GetWrapper <std::map <K, V> > ();
        method = new Method ("get", w);
        clazz->addMethod (method);

        w = new IteratorWrapper <std::map <K, V> > ();
        method = new Method ("iterator", w);
        clazz->addMethod (method);}

} // notebook

#endif /* COLLECTIONANNOTATION_H_ */
