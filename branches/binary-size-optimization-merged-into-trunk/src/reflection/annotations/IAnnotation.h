/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_ANNOTATION_H_
#define TILIAE_ANNOTATION_H_

#include <string>
#include <list>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include "../../core/IToStringEnabled.h"

namespace Annotations {

/**
 * Symbolizuje adnotację dodawaną do klasy poprzez system refleksji.
 * Adnotacje można tworzyć za pomocą makr (raczej tylko, bo stworzone
 * inaczej to już nie będą adnotacje).
 * MARKER.
 */
struct IAnnotation : public Core::IToStringEnabled {

        virtual ~IAnnotation () {}
        virtual std::string getHash () const = 0;

        /**
         * Wywoływane przez AnnotationManager kiedy próbujemy dodać adnotację
         * po raz drugi. Wówczas dodawanie nie powiedzie się, a manager zawoła
         * tą metodę.
         */
        virtual void deleteDuplicate () = 0;

};

/****************************************************************************/

/**
 * Elementy unikalne jak w secie, ale trzyma też kolejność wstawiania elementów,
 * co jest ważne dla Managera.
 */
typedef boost::multi_index::multi_index_container<
        IAnnotation *,
        boost::multi_index::indexed_by<
                // Jak mapa
                boost::multi_index::ordered_unique<
                        boost::multi_index::const_mem_fun <IAnnotation, std::string, &IAnnotation::getHash>
                >,
                // Jak lista
                boost::multi_index::sequenced<>
        >
> AnnotationList;

}

#endif /* ANNOTATION_H_ */
