/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMETASERVICE2_H_
#define IMETASERVICE2_H_

#include <vector>
#include "core/Pointer.h"

namespace Container {

class ValueData;
class NullData;
class RefData;
class DataKey;
struct MetaObject;
struct MetaContainer;
class VisitorContext;

/**
 * Interfejs serwisów, które w pracują na meta-strukturze. Jak widać po
 * metodach, ma troszkę podobną zasadę działania do parsera SAX. Istnieje
 * jeszcze specjalna klasa MetaVisitor, której obiekt wykonuje iterowanie
 * po całej metasukturze i uruchamia własnie odpowiednie metody swoich
 * serwisów (IMetaService).
 * \ingroup Container
 */
struct IMetaService {
        virtual ~IMetaService () {}

        virtual void onContainer (MetaContainer const *data) = 0;

        virtual bool onMetaBegin (MetaObject const *data) = 0;
        virtual bool onMetaEnd (MetaObject const *data) = 0;
        virtual bool onMappedMetaBegin (MetaObject const *data) = 0;
        virtual bool onMappedMetaEnd (MetaObject const *data) = 0;
        virtual bool onIndexedMetaBegin (MetaObject const *data) = 0;
        virtual bool onIndexedMetaEnd (MetaObject const *data) = 0;

        virtual void onConstructorArgsBegin (MetaObject const *data) = 0;
        virtual void onConstructorArgsEnd (MetaObject const *data) = 0;

        virtual void onValueData (DataKey const *dk, ValueData const *data) = 0;
        virtual void onNullData (DataKey const *dk, NullData const *data) = 0;
        virtual void onRefData  (DataKey const *dk, RefData const *data) = 0;

        virtual void setContext (VisitorContext *) = 0;
        virtual VisitorContext *getContext () const = 0;
};

/**
 * Lista serwisów.
 * \ingroup Container
 */
typedef std::vector <IMetaService *> MetaServiceVector;

}

#	endif /* IMETASERVICE2_H_ */
