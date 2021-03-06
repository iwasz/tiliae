/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METHOD_ANNOTATION_H_
#define METHOD_ANNOTATION_H_

#include "reflection/visitor/IReflectionVisitor.h"
#include "IReflectionAnnotation.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"
#include "reflection/wrapper/ICallableWrapper.h"
#include "reflection/wrapper/MethodWrapper.h"
#include "reflection/wrapper/SetterWrapper.h"
#include "core/Pointer.h"

#ifdef WITH_ANNOTATIONS

namespace Reflection {

/**
 * Adnotacja metody.
 */
class TILIAE_API MethodAnnotation : public IReflectionAnnotation {
public:

        MethodAnnotation (const std::string &c,
                          const std::string &m,
                          ICallableWrapper *cal) : callableWrapper (cal), className (c), methodName (m) {}

        virtual ~MethodAnnotation () {}

        std::string const &getMethodName () const { return methodName; }
        std::string const &getClassName () const { return className; }
        ICallableWrapper *getWrapper () const { return this->callableWrapper; }

        virtual Core::Variant accept (IReflectionVisitor *vis, Class *cls = NULL) { return vis->visit (this, cls);}

        virtual std::string toString () const;

        std::string getHash () const { return className + methodName; }
        void deleteDuplicate () { delete callableWrapper; }

private:

        ICallableWrapper *callableWrapper;
        std::string className;
        std::string methodName;
};

}

#endif

/**
 * Makro ogólnego przeznaczenia.
 */
#define REFLECTION_METHOD_ANNOTATION(CLS_NAME, CLS_TYPE, method)        \
                Annotations::AnnotationManager::addMethodAnnotation (CLS_NAME, #method, Reflection::createMethodWrapper (&CLS_TYPE::method));


/**
 * Impl.settera.
 */
#define REFLECTION_SETTER_ANNOTATION(CLS_NAME, CLS_TYPE, method)        \
                Annotations::AnnotationManager::addMethodAnnotation (CLS_NAME, #method, Reflection::createSetterWrapper (&CLS_TYPE::method));

/**
 * Makro jak REFLECTION_METHOD_ANNOTATION, ale umożliwia dodawanie
 * metod przeciążonych (nie const).
 */
#define REFLECTION_METHOD_ANNOTATION_OVERLOAD(CLS_NAME, CLS_TYPE, RET, method, ...)        \
                Annotations::AnnotationManager::addMethodAnnotation (CLS_NAME, #method, Reflection::createMethodWrapper (static_cast <RET (CLS_TYPE::*)(__VA_ARGS__)> (&CLS_TYPE::method)));


/**
 * Makro jak REFLECTION_METHOD_ANNOTATION, ale umożliwia dodawanie
 * metod przeciążonych (const).
 */
#define REFLECTION_METHOD_ANNOTATION_OVERLOAD_CONST(CLS_NAME, CLS_TYPE, RET, method, ...)        \
                Annotations::AnnotationManager::addMethodAnnotation (CLS_NAME, #method, Reflection::createMethodWrapper (static_cast <RET (CLS_TYPE::*)(__VA_ARGS__) const> (&CLS_TYPE::method)));

/**
 * Implementacyjne, nie używać.
 */
#define REFLECTION_METHOD_ANNOTATION_BODY_PRIV(method)                                  \
REFLECTION_METHOD_ANNOTATION(REFLECT_CLASS_NAME, CLASS, method)           \
}

/**
 * Impl settera./
 */
#define REFLECTION_SETTER_ANNOTATION_BODY_PRIV(method)                                  \
REFLECTION_SETTER_ANNOTATION(REFLECT_CLASS_NAME, CLASS, method)           \
}

/**
 * Definicja makra adnotacji dla MethodAnnotation - każde
 * adnotowanie metody za pomocą REFLECTION_METHOD dodaje taki kawał kodu,
 * (zamknięty w statyczną metodę) więc trzeba pamiętać, że
 * jest pewien narzut.
 */
#ifdef WITH_ANNOTATIONS
#define REFLECTION_METHOD(method)                                                        \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_METHOD_ANNOTATION_BODY_PRIV(method)
#else
#define REFLECTION_METHOD(method)
#endif

#ifdef WITH_ANNOTATIONS
#define REFLECTION_METHOD_(method)                                                       \
                ANNOTATION_METHOD_HEADER                                                 \
                REFLECTION_METHOD_ANNOTATION_BODY_PRIV(method)
#else
#define REFLECTION_METHOD_(method)
#endif

/**
 * Setter.
 */
#ifdef WITH_ANNOTATIONS
#define REFLECTION_SETTER(method)                                                        \
                                                                                         \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_SETTER_ANNOTATION_BODY_PRIV(method)
#else
#define REFLECTION_SETTER(method)
#endif

#ifdef WITH_ANNOTATIONS
#define REFLECTION_SETTER_(method)                                                       \
                ANNOTATION_METHOD_HEADER                                                 \
                REFLECTION_SETTER_ANNOTATION_BODY_PRIV(method)
#else
#define REFLECTION_SETTER_(method)
#endif

#ifdef WITH_ANNOTATIONS
#define REFLECTION_OVERLOADED_METHOD(ret,method,...)                                                            \
        ANNOTATION_METHOD_HEADER_RECURENCE                                                                      \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD(REFLECT_CLASS_NAME, CLASS, ret, method, __VA_ARGS__) \
}
#else
#define REFLECTION_OVERLOADED_METHOD(ret,method,...)
#endif

#ifdef WITH_ANNOTATIONS
#define REFLECTION_OVERLOADED_METHOD_(ret,method,...)                                                           \
        ANNOTATION_METHOD_HEADER                                                                                \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD(REFLECT_CLASS_NAME, CLASS, ret, method, __VA_ARGS__) \
}
#else
#define REFLECTION_OVERLOADED_METHOD_(ret,method,...)
#endif

#ifdef WITH_ANNOTATIONS
#define REFLECTION_OVERLOADED_CONST_METHOD(ret,method,...)                                                            \
        ANNOTATION_METHOD_HEADER_RECURENCE                                                                            \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD_CONST(REFLECT_CLASS_NAME, CLASS, ret, method, __VA_ARGS__) \
}
#else
#define REFLECTION_OVERLOADED_CONST_METHOD(ret,method,...)
#endif

#ifdef WITH_ANNOTATIONS
#define REFLECTION_OVERLOADED_CONST_METHOD_(ret,method,...)                                                           \
        ANNOTATION_METHOD_HEADER                                                                                      \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD_CONST(REFLECT_CLASS_NAME, CLASS, ret, method, __VA_ARGS__) \
}
#else
#define REFLECTION_OVERLOADED_CONST_METHOD_(ret,method,...)
#endif

#endif /* METHODANNOTATION_H_ */
