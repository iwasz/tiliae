/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONSTRUCTOR_ANNOTATION_H_
#define CONSTRUCTOR_ANNOTATION_H_

#include "../wrapper/ConstructorPointer.h"
#include "../visitor/IReflectionVisitor.h"
#include "../annotations/AnnotationManager.h"
#include "IReflectionAnnotation.h"
#include "ClassAnnotation.h"
#include "../../core/string/String.h"
#include "../../core/variant/Variant.h"
#include "../../core/ApiMacro.h"

namespace Reflection {

/**
 * Adnotacja dla konstruktorów.
 */
class TILIAE_API ConstructorAnnotation : public IReflectionAnnotation {
public:

        ConstructorAnnotation (const std::string &c,
                          Ptr <IConstructorPointer> poi) :
                                  constructorPointer (poi), className (c) {}

        /**
         * Nazwa klasy.
         */
        std::string getClassName () const { return className; }

        /**
         * Obiekt wywołujący fizycnie konstruktor danej klasy za pomocą
         * operatora new.
         */
        Ptr<IConstructorPointer> getConstructorPointer () const { return this->constructorPointer; }

        virtual Core::Variant accept (IReflectionVisitor *vis, const Core::Variant &arg = Core::Variant ()) { return vis->visit (this, arg);}

        virtual std::string toString () const;

        std::string getHash () const;

private:

        Ptr <IConstructorPointer> constructorPointer;
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
 * Makro do implementacji _c, nie używać.
 */
#define REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PRIV(...)                                        \
REFLECTION_CONSTRUCTOR_ANNOTATION(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE, __VA_ARGS__)

/**
 * Definicja makra adnotacji dla ConstructorAnnotation. Zadziała jednakowoż
 * tylko z kompilatorami C++, które obsługują *variadic macros*, a niestety
 * to nie jest w standardzie :( Gcc działa bez problemu, ale nie wiem od
 * której wersji :(
 */
#define REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PUBLIC(...)                               \
                                                                                         \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PRIV(__VA_ARGS__) }

#define REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PUBLIC_COMBO(...)                         \
                                                                                         \
                ANNOTATION_METHOD_HEADER                                                 \
                REFLECTION_CLASS_ANNOTATION_BODY_PRIV                                   \
                REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PRIV(__VA_ARGS__) }

#endif /* METHODANNOTATION_H_ */
