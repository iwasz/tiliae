/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_ANNOTATIONMANAGER_H_
#define TILIAE_ANNOTATIONMANAGER_H_

#include <iostream>
#include "IAnnotation.h"
#include "../../core/ApiMacro.h"

namespace Annotations {

/**
 * Kontener adnotacji. Instancje pobieramy za pomocą statycznej metody instance.
 * Bardzo ważne założenie : adnotacje są w kontenerze przechowywane w tej kolejności,
 * w której występują w klasie.
 */
class TILIAE_API AnnotationManager : public Core::IToStringEnabled {
public:

        static AnnotationManager &instance ();

        /**
         * Dodaje adnotacje do managera. Uwaga : nie ma zabezpieczenia przed wielokrotnym
         * dodaniem tej samej adnotacji.
         */
        bool addAnnotation (IAnnotation *a)
        {
                annotationList.insert (a);
                return true;
        }

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
