/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDATA_H_
#define IDATA_H_

#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include "metaStructure/interface/IDataVisitor.h"
#include "../../../../core/string/String.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Jest to najbardziej elementarna (atomowa) część meta-struktur.
 * Za jej pomocą implementowane są takie pojęcia jak <ref>, <idref>,
 * <value>, i <null>. Ustawiamy je meta-elementom.
 * \ingroup Container
 */
struct TILIAE_API IData {
        virtual ~IData () {}
        virtual const char *getData () const = 0;
        virtual void accept (std::string const &key, IDataVisitor *visitor) = 0;
};

/**
 * Typ danych dla IndexedMeta.
 */
typedef std::vector <IData *> DataVector;

struct DataKey {

        DataKey () : data (NULL) {}
        DataKey (std::string const &k, IData *d) : key (k), data (d), associatedWith (NULL) {}

        std::string key;
        IData *data;
        MetaObject *associatedWith;
};

/**
 * Używane przy parsdowaniu z XML.
 */
typedef std::vector <DataKey> DataKeyStack;

/**
 * Typ danych dla MappedMeta - działa jak mapa, ale zachowuje kolejność
 * wstawiania elementów, czyli działa jak LinkedHashMap w Javie.
 */
typedef boost::multi_index::multi_index_container<
        DataKey,
        boost::multi_index::indexed_by<
                // Jak mapa
                boost::multi_index::ordered_unique<
                        boost::multi_index::member <DataKey, std::string, &DataKey::key>
                >,
                // Jak lista
                boost::multi_index::sequenced<>
        >
> DataMap;

typedef DataMap::nth_index <0>::type::const_iterator DataKeyIterator0;
typedef DataMap::nth_index <1>::type::const_iterator DataKeyIterator1;

}//nms

#endif /* IDATA_H_ */
