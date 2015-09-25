/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef REFLECTION_ENABLED
#ifndef TILIAE_ANNOTATIONMANAGER_H_
#define TILIAE_ANNOTATIONMANAGER_H_

#include <iostream>
#include "IAnnotation.h"
#include "core/ApiMacro.h"

namespace Reflection {
struct ICallableWrapper;
struct IFieldWrapper;
}

namespace Annotations {

/**
 * Kontener adnotacji. Instancje pobieramy za pomocą statycznej metody instance.
 * Bardzo ważne założenie : adnotacje są w kontenerze przechowywane w tej kolejności,
 * w której występują w klasie.
 */
class TILIAE_API AnnotationManager : public Core::IToStringEnabled {
public:

        virtual ~AnnotationManager ();
        static AnnotationManager &instance ();

        /**
         * Dodaje adnotacje do managera.
         */
        bool addAnnotation (IAnnotation *a);

        static void addMethodAnnotation (std::string const &clsName, std::string const &methName, Reflection::ICallableWrapper *wrapper);
        static void addFieldAnnotation (std::string const &clsName, std::string const &fieldName, Reflection::IFieldWrapper *wrapper);

        /**
         *
         */
        virtual std::string toString () const;

        const AnnotationList &getAnnotationList () const { return  annotationList; }

private:

        AnnotationManager () {}

private:

        AnnotationList annotationList;

};

}

#endif /* ANNOTATIONMANAGER_H_ */
#endif
