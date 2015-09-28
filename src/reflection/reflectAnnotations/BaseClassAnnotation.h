/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BASE_CLASS_ANNOTATION_H_
#define BASE_CLASS_ANNOTATION_H_

#include "IReflectionAnnotation.h"
#include "reflection/ListHelper.h"
#include "reflection/visitor/IReflectionVisitor.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/variant/Variant.h"
#include "core/ApiMacro.h"

#ifdef WITH_ANNOTATIONS

namespace Reflection {

/**
 * Adnotacja metody.
 */
class TILIAE_API BaseClassAnnotation : public IReflectionAnnotation {
public:

        BaseClassAnnotation (const std::string &c,
                          const Core::StringVector &l = Core::StringVector ()) : className (c), baseClassList (l) {}
        virtual ~BaseClassAnnotation () {}

        std::string const &getClassName () const { return className; }
        Core::StringVector const &getBaseClassList () const { return baseClassList; }

        virtual Core::Variant accept (IReflectionVisitor *vis, Class *cls = NULL) { return vis->visit (this, cls);}

        virtual std::string toString () const;

        std::string getHash () const;

private:

        std::string className;
        Core::StringVector baseClassList;
};

}

#endif

/**
 *
 */
#define REFLECTION_BASE_CLASS_ANNOTATION(CLS_NAME, ...)                         \
                                                                                 \
        Annotations::AnnotationManager::instance ().addAnnotation                \
          (new Reflection::BaseClassAnnotation (CLS_NAME,                        \
                Reflection::ListHelper::createStringList (__VA_ARGS__)));

/**
 *
 */
#define REFLECTION_BASE_CLASS_ANNOTATION_BODY_PRIV(...)                                  \
                REFLECTION_BASE_CLASS_ANNOTATION(REFLECT_CLASS_NAME, __VA_ARGS__);     \
        }

/**
 * Definicja makra adnotacji dla BaseClassAnnotation - każde
 * adnotowanie metody za pomocą REFLECTION_METHOD dodaje taki kawał kodu,
 * (zamknięty w statyczną metodę) więc trzeba pamiętać, że
 * jest pewien narzut.
 *
 * Uwaga! W jednym wywołaniu można dodać do 10 klas bazowych.
 * Jeśli klas bazowych jest więcej, to 1. coś jest nie tak z
 * Twoim designem, 2. należy użyć makra REFLECTION_BASE_CLASS kilka razy.
 *
 * Klasy bazowe podajemy jako stringi.
 */
#ifdef WITH_ANNOTATIONS
#define REFLECTION_BASE_CLASS(...)                                                       \
                                                                                         \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_BASE_CLASS_ANNOTATION_BODY_PRIV(__VA_ARGS__)
#else
#define REFLECTION_BASE_CLASS(...)
#endif

/**
 * Tak samo jak REFLECTION_BASE_CLASS, ale bez wywoływania poprzedniej metody. Można użyć
 * jako pierwszą adnotację w klasie.
 */
#ifdef WITH_ANNOTATIONS
#define REFLECTION_BASE_CLASS_(...)                                                      \
                                                                                         \
                ANNOTATION_METHOD_HEADER                                                 \
                REFLECTION_BASE_CLASS_ANNOTATION_BODY_PRIV(__VA_ARGS__)
#else
#define REFLECTION_BASE_CLASS_(...)
#endif


#endif /* METHODANNOTATION_H_ */
