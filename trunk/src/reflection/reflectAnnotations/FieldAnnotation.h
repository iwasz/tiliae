/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FIELD_ANNOTATION_H_
#define FIELD_ANNOTATION_H_

#include "reflection/visitor/IReflectionVisitor.h"
#include "core/ApiMacro.h"
#include "reflection/wrapper/FieldWrapper.h"
#include "IReflectionAnnotation.h"

namespace Reflection {

/**
 *
 */
class TILIAE_API FieldAnnotation : public IReflectionAnnotation {
public:

        FieldAnnotation (const std::string &c,
                         const std::string &m,
                         IFieldWrapper *cal) : wrapper (cal), className (c), fieldName (m) {}

        virtual ~FieldAnnotation () {}

        std::string const &getFielddName () const { return fieldName; }
        std::string const &getClassName () const { return className; }
        IFieldWrapper *getWrapper () const { return this->wrapper; }

        virtual Core::Variant accept (IReflectionVisitor *vis, Class *cls = NULL) { return vis->visit (this, cls);}

        virtual std::string toString () const { return ""; }

        std::string getHash () const { return className + fieldName + "-F"; }
        void deleteDuplicate () { delete wrapper; }

private:

        IFieldWrapper *wrapper;
        std::string className;
        std::string fieldName;
};

}

/*
 * Makro ogólnego przeznaczenia.
 */
#define REFLECTION_FIELD_VALUE_ANNOTATION(CLS_NAME, CLS_TYPE, field)        \
                Annotations::AnnotationManager::addFieldAnnotation (CLS_NAME, #field, Reflection::createFieldWrapper (&CLS_TYPE::field));

#define REFLECTION_FIELD_REFERENCE_ANNOTATION(CLS_NAME, CLS_TYPE, field)        \
                Annotations::AnnotationManager::addFieldAnnotation (CLS_NAME, #field, Reflection::createFieldWrapperRetByPtr (&CLS_TYPE::field));

#define REFLECTION_FIELD_ENUM_ANNOTATION(CLS_NAME, CLS_TYPE, field)        \
                Annotations::AnnotationManager::addFieldAnnotation (CLS_NAME, #field, Reflection::createFieldWrapperEnum (&CLS_TYPE::field));



/*
 *
 */
#define REFLECTION_FIELD_VALUE_ANNOTATION_BODY_PRIV(field)                                    \
                REFLECTION_FIELD_VALUE_ANNOTATION(REFLECT_CLASS_NAME, CLASS, field)           \
}

#define REFLECTION_FIELD_REFERENCE_ANNOTATION_BODY_PRIV(field)                                    \
                REFLECTION_FIELD_REFERENCE_ANNOTATION(REFLECT_CLASS_NAME, CLASS, field)           \
}

#define REFLECTION_FIELD_ENUM_ANNOTATION_BODY_PRIV(field)                                    \
                REFLECTION_FIELD_ENUM_ANNOTATION(REFLECT_CLASS_NAME, CLASS, field)           \
}



/**
 * Definicja makra adnotacji dla MethodAnnotation - każde
 * adnotowanie metody za pomocą REFLECTION_METHOD dodaje taki kawał kodu,
 * (zamknięty w statyczną metodę) więc trzeba pamiętać, że
 * jest pewien narzut.
 */
#ifdef REFLECTION_ENABLED
#define REFLECTION_FIELD_VALUE(field)                                                    \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_FIELD_VALUE_ANNOTATION_BODY_PRIV(field)
#else
#define REFLECTION_FIELD_VALUE(field)
#endif

#ifdef REFLECTION_ENABLED
#define REFLECTION_FIELD_REFERENCE(field)                                                \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_FIELD_REFERENCE_ANNOTATION_BODY_PRIV(field)
#else
#define REFLECTION_FIELD_REFERENCE(field)
#endif

#ifdef REFLECTION_ENABLED
#define REFLECTION_FIELD_ENUM(field)                                                \
                ANNOTATION_METHOD_HEADER_RECURENCE                                       \
                REFLECTION_FIELD_ENUM_ANNOTATION_BODY_PRIV(field)
#else
#define REFLECTION_FIELD_ENUM(field)
#endif



/**
 * Do stosowania na przykład tak:
 * int REFLECTION_FIELD_VALUE_INPLACE (i);
 */
#ifdef REFLECTION_ENABLED
#define REFLECTION_FIELD_VALUE_INPLACE(field) field; REFLECTION_FIELD_VALUE(field)
#else
#define REFLECTION_FIELD_VALUE_INPLACE(field) field;
#endif

#ifdef REFLECTION_ENABLED
#define REFLECTION_FIELD_REFERENCE_INPLACE(field) field; REFLECTION_FIELD_REFERENCE(field)
#else
#define REFLECTION_FIELD_REFERENCE_INPLACE(field) field;
#endif

#ifdef REFLECTION_ENABLED
#define REFLECTION_FIELD_ENUM_INPLACE(field) field; REFLECTION_FIELD_ENUM(field)
#else
#define REFLECTION_FIELD_ENUM_INPLACE(field) field;
#endif

#endif /* METHODANNOTATION_H_ */
