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

        const char *key;
        IData *data;
        MetaObject *associatedWith;
        DataKey *next;

private:

        DataKey () : key (NULL), data (NULL), associatedWith (NULL), next (NULL) {}
        DataKey (IData *d) : key (NULL), data (d), associatedWith (NULL), next (NULL) {}
        DataKey (const char *k, IData *d) : key (k), data (d), associatedWith (NULL), next (NULL) {}
        friend class MetaFactory;

};

/**
 * Używane przy parsdowaniu z XML.
 */
typedef std::vector <DataKey *> DataKeyStack;
typedef std::vector <DataKey *> DataKeyVector;

}//nms

#endif /* IDATA_H_ */
