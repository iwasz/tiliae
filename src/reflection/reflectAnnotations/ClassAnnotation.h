/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLASS_ANNOTATION_H_
#define CLASS_ANNOTATION_H_

#include "../visitor/IReflectionVisitor.h"
#include "IReflectionAnnotation.h"
#include "../../core/string/String.h"
#include "../../core/ApiMacro.h"
#include "../../core/Typedefs.h"

namespace Reflection {

/**
 * Every class should have this anotation and it should be
 * added first.
 */
class TILIAE_API ClassAnnotation : public IReflectionAnnotation {
public:

        ClassAnnotation (const std::string &c, std::type_info const &t) :
                className (c), type (t)
        {}

        /**
         * Nazwa klasy.
         */
        std::string getClassName () const { return className; }

        /**
         * Typ klasy do której należy ta adnotacja.
         */
        std::type_info const &getType () const { return type; }

        virtual Core::Variant accept (IReflectionVisitor *vis, const Core::Variant &arg = Core::Variant ()) { return vis->visit (this, arg);}

        virtual std::string toString () const;

        std::string getHash () const { return className; }

private:

        std::string className;
        std::type_info const &type;
};

}

/**
 * Makro ogólnego przeznaczenia.
 */
#define REFLECTION_CLASS_ANNOTATION(CLS_NAME, CLS_TYPE)                       \
                                                                               \
Annotations::AnnotationManager::instance ().addAnnotation                      \
  (new Reflection::ClassAnnotation (CLS_NAME, typeid (CLS_TYPE&)));

/**
 * Makro do implementacji REFLECTION_CONSTRUCTOR, nie używać.
 */
#define REFLECTION_CLASS_ANNOTATION_BODY_PRIV                                 \
REFLECTION_CLASS_ANNOTATION(REFLECT_CLASS_NAME, REFLECT_CLAZZ_TYPE)


#define REFLECTION_CLASS                                                   \
                                                                           \
                ANNOTATION_METHOD_HEADER                                   \
                REFLECTION_CLASS_ANNOTATION_BODY_PRIV }

#endif /* METHODANNOTATION_H_ */
