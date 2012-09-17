/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONSTRUCTOR_ANNOTATION_H_
#define CONSTRUCTOR_ANNOTATION_H_

#include "reflection/wrapper/ConstructorPointer.h"
#include "reflection/visitor/IReflectionVisitor.h"
#include "reflection/annotations/AnnotationManager.h"
#include "IReflectionAnnotation.h"
#include "ClassAnnotation.h"
#include "core/string/String.h"
#include "core/variant/Variant.h"
#include "core/ApiMacro.h"

namespace Reflection {

/**
 * Adnotacja dla konstruktorów.
 */
class TILIAE_API ConstructorAnnotation : public IReflectionAnnotation {
public:

        ConstructorAnnotation (const std::string &c,
                                  IConstructorPointer *poi) :
                                  constructorPointer (poi), className (c) {}
        virtual ~ConstructorAnnotation () {}

        /**
         * Nazwa klasy.
         */
        std::string getClassName () const { return className; }

        /**
         * Obiekt wywołujący fizycnie konstruktor danej klasy za pomocą
         * operatora new.
         */
        IConstructorPointer *getConstructorPointer () const { return this->constructorPointer; }

        virtual Core::Variant accept (IReflectionVisitor *vis, Class *cls = NULL) { return vis->visit (this, cls);}

        virtual std::string toString () const;

        std::string getHash () const;
        virtual void deleteDuplicate () { delete constructorPointer; }

private:

        IConstructorPointer *constructorPointer;
        std::string className;
};

}

/**
 * Makro ogólnego przeznaczenia.
 */
#define REFLECTION_CONSTRUCTOR_ANNOTATION(CLS_NAME, CLS_TYPE, ...)           \
                                                                              \
Annotations::AnnotationManager::instance ().addAnnotation                     \
  (new Reflection::ConstructorAnnotation (CLS_NAME,                           \
     Reflection::ConstructorPointerWrapper2 <CLS_TYPE,                        \
     __VA_ARGS__>::Level1Wrapper::newConstructorPointer ()));

/**
 * Makro do implementacji REFLECTION_CONSTRUCTOR, nie używać.
 */
#define REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PRIV(...)                                        \
REFLECTION_CONSTRUCTOR_ANNOTATION(REFLECT_CLASS_NAME, CLASS, __VA_ARGS__)

/**
 * Definicja makra adnotacji dla ConstructorAnnotation. Zadziała jednakowoż
 * tylko z kompilatorami C++, które obsługują *variadic macros*, a niestety
 * to nie jest w standardzie :( Gcc działa bez problemu, ale nie wiem od
 * której wersji :(
 */
#ifdef REFLECTION_ENABLED
#define REFLECTION_CONSTRUCTOR(...)                                                      \
                                                                                         \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PRIV(__VA_ARGS__) }
#else
#define REFLECTION_CONSTRUCTOR(...)
#endif

#ifdef REFLECTION_ENABLED
#define REFLECTION_CONSTRUCTOR_(...)                                                     \
                                                                                         \
                ANNOTATION_METHOD_HEADER                                                 \
                REFLECTION_CLASS_ANNOTATION_BODY_PRIV                                    \
                REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PRIV(__VA_ARGS__) }
#else
#define REFLECTION_CONSTRUCTOR_(...)
#endif

#endif /* METHODANNOTATION_H_ */
