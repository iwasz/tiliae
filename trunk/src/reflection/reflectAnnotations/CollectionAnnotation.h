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

#include "../../core/variant/Variant.h"
#include "../../core/Typedefs.h"
#include "../wrapper/ICallableWrapper.h"
#include "../model/Class.h"
#include "../Manager.h"
#include "../model/Method.h"
#include "../model/Constructor.h"
#include "../wrapper/AddWrapper.h"
#include "../wrapper/GetWrapper.h"
#include "../wrapper/SetWrapper.h"
#include "../wrapper/IteratorWrapper.h"
#include "../annotations/Macros.h"

/*##########################################################################*/

/**
 * Adnotacja kolekcji. Ta adnotacja służy do dodawania jednego z dozwolonych typó kolekcji do
 * refleksji. Użycie jest na przykład takie (w pliku .h lub .cc):
 *
 * <pre>
 * g_ (std::list<std::string>)
 * </pre>
 *
 * A ładnie wygląda jak się zrobi typedef :
 *
 * <pre>
 * typedef std::list<std::string> StringList;
 * g_ (StringList)
 * </pre>
 *
 * Dozwolone kolekcji, to wszystkie typy, dla których stworzyłem częściową specjalizację
 * szablonu ClassAnotation (w tym pliku poniżej).
 */
#define REFLECTION_COLLECTION(type) \
        ANNOTATION_RUN_ONCE_AT_STARTUP(::Reflection::CollectionAnnotation <type >::run (#type);)

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
#define _gn(type,name) \
        ANNOTATION_RUN_ONCE_AT_STARTUP(::Reflection::CollectionAnnotation <type >::run (name);)

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
        Ptr<Class> clazz = boost::make_shared <Class> (className, typeid (std::vector <T>&));
        Manager::add (clazz);

        // Konstruktor
        Ptr <IConstructorPointer> cp = Reflection::ConstructorPointerWrapper2 <std::vector <T>, void>::Level1Wrapper::newConstructorPointer ();
        Ptr <Constructor> constructor = boost::make_shared <Constructor> (cp);
        clazz->addConstructor (constructor);

        // Metody
        Ptr <ICallableWrapper> w = boost::make_shared <AddWrapper <std::vector <T> > > ();
        Ptr <Method> method = boost::make_shared <Method> ("add", w);
        clazz->addMethod (method);

        w = boost::make_shared <GetWrapper <std::vector <T> > > ();
        method = boost::make_shared <Method> ("get", w);
        clazz->addMethod (method);

        w = boost::make_shared <SetWrapper <std::vector <T> > > ();
        method = boost::make_shared <Method> ("set", w);
        clazz->addMethod (method);

        w = boost::make_shared <IteratorWrapper <std::vector <T> > > ();
        method = boost::make_shared <Method> ("iterator", w);
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
        Ptr<Class> clazz = boost::make_shared <Class> (className, typeid (std::list <T> &));
        Manager::add (clazz);

        // Konstruktor
        Ptr <IConstructorPointer> cp = Reflection::ConstructorPointerWrapper2 <std::list <T>, void>::Level1Wrapper::newConstructorPointer ();
        Ptr <Constructor> constructor = boost::make_shared <Constructor> (cp);
        clazz->addConstructor (constructor);

        // Metody
        Ptr <ICallableWrapper> w = boost::make_shared <AddWrapper <std::list <T> > > ();
        Ptr <Method> method = boost::make_shared <Method> ("add", w);
        clazz->addMethod (method);

        w = boost::make_shared <GetWrapper <std::list <T> > > ();
        method = boost::make_shared <Method> ("get", w);
        clazz->addMethod (method);

        w = boost::make_shared <SetWrapper <std::list <T> > > ();
        method = boost::make_shared <Method> ("set", w);
        clazz->addMethod (method);

        w = boost::make_shared <IteratorWrapper <std::list <T> > > ();
        method = boost::make_shared <Method> ("iterator", w);
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
        Ptr<Class> clazz = boost::make_shared <Class> (className, typeid (std::set <T>&));
        Manager::add (clazz);

        // Konstruktor
        Ptr <IConstructorPointer> cp = Reflection::ConstructorPointerWrapper2 <std::set <T>, void>::Level1Wrapper::newConstructorPointer ();
        Ptr <Constructor> constructor = boost::make_shared <Constructor> (cp);
        clazz->addConstructor (constructor);

        // Metody
        Ptr <ICallableWrapper> w = boost::make_shared <AddWrapper <std::set <T> > > ();
        Ptr <Method> method = boost::make_shared <Method> ("add", w);
        clazz->addMethod (method);

        w = boost::make_shared <GetWrapper <std::set <T> > > ();
        method = boost::make_shared <Method> ("get", w);
        clazz->addMethod (method);

        w = boost::make_shared <IteratorWrapper <std::set <T> > > ();
        method = boost::make_shared <Method> ("iterator", w);
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
        Ptr<Class> clazz = boost::make_shared <Class> (className, typeid (std::map <K,V>&));
        Manager::add (clazz);

        // Konstruktor
        Ptr <IConstructorPointer> cp = Reflection::ConstructorPointerWrapper2 <std::map <K, V>, void>::Level1Wrapper::newConstructorPointer ();
        Ptr <Constructor> constructor = boost::make_shared <Constructor> (cp);
        clazz->addConstructor (constructor);

        // Metody
        Ptr <ICallableWrapper> w = boost::make_shared <SetWrapper <std::map <K, V> > > ();
        Ptr <Method> method = boost::make_shared <Method> ("set", w);
        clazz->addMethod (method);

        w = boost::make_shared <GetWrapper <std::map <K, V> > > ();
        method = boost::make_shared <Method> ("get", w);
        clazz->addMethod (method);

        w = boost::make_shared <IteratorWrapper <std::map <K, V> > > ();
        method = boost::make_shared <Method> ("iterator", w);
        clazz->addMethod (method);}

} // notebook

#endif /* COLLECTIONANNOTATION_H_ */
