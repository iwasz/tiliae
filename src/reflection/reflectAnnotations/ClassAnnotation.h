/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLASS_ANNOTATION_H_
#define CLASS_ANNOTATION_H_

#include "reflection/visitor/IReflectionVisitor.h"
#include "IReflectionAnnotation.h"
#include "core/ApiMacro.h"
#include "core/Typedefs.h"
#include "core/variant/Variant.h"
#include "reflection/wrapper/Deleter.h"

namespace Reflection {

/**
 * Every class should have this anotation and it should be
 * added first.
 */
class TILIAE_API ClassAnnotation : public IReflectionAnnotation {
public:

        ClassAnnotation (const std::string &c, std::type_info const &t, Reflection::IDeleter *d) :
                className (c), type (t), deleter (d)
        {}
        virtual ~ClassAnnotation () {}

        /**
         * Nazwa klasy.
         */
        std::string getClassName () const { return className; }

        /**
         * Typ klasy do której należy ta adnotacja.
         */
        std::type_info const &getType () const { return type; }

        virtual Core::Variant accept (IReflectionVisitor *vis, Class *cls = NULL) { return vis->visit (this, cls);}

        virtual std::string toString () const;

        std::string getHash () const { return className; }

        Reflection::IDeleter* getDeleter () const { return deleter; }

        void deleteDuplicate ();

private:

        std::string className;
        std::type_info const &type;
        Reflection::IDeleter *deleter;
};

}

/**
 * Makro ogólnego przeznaczenia.
 */
#ifdef REFLECTION_ENABLED
#define REFLECTION_CLASS_ANNOTATION(CLS_NAME, CLS_TYPE)                       \
                                                                               \
Annotations::AnnotationManager::instance ().addAnnotation                      \
  (new Reflection::ClassAnnotation (CLS_NAME, typeid (CLS_TYPE&), new Reflection::PtrDeleter<CLS_TYPE>));
#else
#define REFLECTION_CLASS_ANNOTATION(CLS_NAME, CLS_TYPE)
#endif

/**
 * Makro do implementacji REFLECTION_CONSTRUCTOR, nie używać.
 */

#define REFLECTION_CLASS_ANNOTATION_BODY_PRIV                                 \
REFLECTION_CLASS_ANNOTATION(REFLECT_CLASS_NAME, CLASS)

#ifdef REFLECTION_ENABLED
#define REFLECTION_CLASS                                                   \
                                                                           \
                ANNOTATION_METHOD_HEADER                                   \
                REFLECTION_CLASS_ANNOTATION_BODY_PRIV }
#else
#define REFLECTION_CLASS
#endif

#endif /* METHODANNOTATION_H_ */
