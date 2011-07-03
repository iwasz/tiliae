/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef METHODANNOTATION_H_
#define METHODANNOTATION_H_

#include "../visitor/IReflectionVisitor.h"
#include "IReflectionAnnotation.h"
#include "../../core/string/String.h"
#include "../../core/ApiMacro.h"
#include "../wrapper/ICallableWrapper.h"
#include "../wrapper/MethodWrapper.h"
#include "../wrapper/SetterWrapper.h"
#include "../../core/Pointer.h"

namespace Reflection {

/**
 * Adnotacja metody.
 * TODO Dodać std::string prettyName.
 */
class TILIAE_API MethodAnnotation : public IReflectionAnnotation {
public:

        MethodAnnotation (const std::string &c,
                          const std::string &m,
                          Ptr <ICallableWrapper> cal) : callableWrapper (cal), className (c), methodName (m) {}

        virtual ~MethodAnnotation () {}

        std::string getMethodName () const { return methodName; }
        std::string getClassName () const { return className; }
        Ptr<ICallableWrapper> getCallableWrapper () const { return this->callableWrapper; }

        virtual Core::Variant accept (IReflectionVisitor *vis, const Core::Variant &arg = Core::Variant ()) { return vis->visit (this, arg);}

        virtual std::string toString () const;

        std::string getHash () const { return className + methodName; }

private:

        Ptr <ICallableWrapper> callableWrapper;
        std::string className;
        std::string methodName;
};

}

/**
 * Makro ogólnego przeznaczenia.
 */
#define REFLECTION_METHOD_ANNOTATION(CLS_NAME, CLS_TYPE, method)        \
                                                                         \
Annotations::AnnotationManager::instance ().addAnnotation                \
  (new Reflection::MethodAnnotation (CLS_NAME,                           \
        #method,                                                         \
		Reflection::createMethodWrapper (&CLS_TYPE::method)));

/**
 * Impl.settera.
 */
#define REFLECTION_SETTER_ANNOTATION(CLS_NAME, CLS_TYPE, method)        \
                                                                         \
Annotations::AnnotationManager::instance ().addAnnotation                \
  (new Reflection::MethodAnnotation (CLS_NAME,                           \
        #method,                                                         \
		Reflection::createSetterWrapper (&CLS_TYPE::method)));


/**
 * Makro jak REFLECTION_METHOD_ANNOTATION, ale umożliwia dodawanie
 * metod przeciążonych (nie const).
 */
#define REFLECTION_METHOD_ANNOTATION_OVERLOAD(CLS_NAME, CLS_TYPE, RET, method, ...)        \
                                                                                            \
Annotations::AnnotationManager::instance ().addAnnotation                                   \
  (new Reflection::MethodAnnotation (CLS_NAME,                                              \
        #method,                                                                            \
        Reflection::createMethodWrapper ( \
             static_cast <RET (CLS_TYPE::*)(__VA_ARGS__)> (&CLS_TYPE::method))));

/**
 * Makro jak REFLECTION_METHOD_ANNOTATION, ale umożliwia dodawanie
 * metod przeciążonych (const).
 */
#define REFLECTION_METHOD_ANNOTATION_OVERLOAD_CONST(CLS_NAME, CLS_TYPE, RET, method, ...)        \
                                                                                            \
Annotations::AnnotationManager::instance ().addAnnotation                                   \
  (new Reflection::MethodAnnotation (CLS_NAME,                                              \
        #method,                                                                            \
        Reflection::createMethodWrapper ( \
             static_cast <RET (CLS_TYPE::*)(__VA_ARGS__) const> (&CLS_TYPE::method))));

/**
 * Implementacyjne, nie używać.
 */
#define REFLECTION_METHOD_ANNOTATION_BODY_PRIV(method)                                  \
REFLECTION_METHOD_ANNOTATION(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE, method)           \
}

/**
 * Impl settera./
 */
#define REFLECTION_SETTER_ANNOTATION_BODY_PRIV(method)                                  \
REFLECTION_SETTER_ANNOTATION(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE, method)           \
}

/**
 * Definicja makra adnotacji dla MethodAnnotation - każde
 * adnotowanie metody za pomocą _m dodaje taki kawał kodu,
 * (zamknięty w statyczną metodę) więc trzeba pamiętać, że
 * jest pewien narzut.
 */
#define _m(method)                                                                      \
                                                                                         \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_METHOD_ANNOTATION_BODY_PRIV(method)

#define __m(method)                                                                     \
                                                                                         \
                ANNOTATION_METHOD_HEADER                                                 \
                REFLECTION_METHOD_ANNOTATION_BODY_PRIV(method)

/**
 * Setter.
 */
#define _s(method)                                                                      \
                                                                                         \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_SETTER_ANNOTATION_BODY_PRIV(method)

#define __s(method)                                                                     \
                                                                                         \
                ANNOTATION_METHOD_HEADER                                                 \
                REFLECTION_SETTER_ANNOTATION_BODY_PRIV(method)

#define _M(ret,method,...)                                                              \
        ANNOTATION_METHOD_HEADER_RECURENCE                                              \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE, ret, method, __VA_ARGS__) \
}

#define __M(ret,method,...)                                                              \
        ANNOTATION_METHOD_HEADER                                              \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE, ret, method, __VA_ARGS__) \
}

#define _Mc(ret,method,...)                                                              \
        ANNOTATION_METHOD_HEADER_RECURENCE                                              \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD_CONST(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE, ret, method, __VA_ARGS__) \
}

#define __Mc(ret,method,...)                                                              \
        ANNOTATION_METHOD_HEADER                                              \
        REFLECTION_METHOD_ANNOTATION_OVERLOAD_CONST(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE, ret, method, __VA_ARGS__) \
}

#endif /* METHODANNOTATION_H_ */
