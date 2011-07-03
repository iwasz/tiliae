/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMETASERVICE2_H_
#define IMETASERVICE2_H_

#include <list>
#include <Pointer.h>

namespace Container {

class ValueData;
class NullData;
class RefData;
class IdRefData;

struct ListElem;
struct MapElem;

struct MappedMeta;
struct IndexedMeta;

struct MetaContainer;

struct IMeta;
struct AbstractMeta;

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

        virtual void onContainer (MetaContainer *data) = 0;

        virtual bool onMetaBegin (IMeta *data) = 0;
        virtual bool onMetaEnd (IMeta *data) = 0;
        virtual bool onMappedMetaBegin (MappedMeta *data) = 0;
        virtual bool onMappedMetaEnd (MappedMeta *data) = 0;
        virtual bool onIndexedMetaBegin (IndexedMeta *data) = 0;
        virtual bool onIndexedMetaEnd (IndexedMeta *data) = 0;

        virtual void onConstructorArgsBegin (IMeta *data) = 0;
        virtual void onConstructorArgsEnd (IMeta *data) = 0;

        virtual void onListElem (ListElem *data) = 0;
        virtual void onMapElem (MapElem *data) = 0;
        virtual void onValueData (ValueData *data) = 0;
        virtual void onNullData (NullData *data) = 0;
        virtual void onRefData (RefData *data) = 0;
        virtual void onIdRefData (IdRefData *data) = 0;

        /*virtual void reset () = 0;*/
        virtual void setContext (VisitorContext *) = 0;
        virtual VisitorContext *getContext () const = 0;
};

/**
 * Lista serwisów.
 * \ingroup Container
 */
typedef std::list <Ptr <IMetaService> > MetaServiceList;

}

#	endif /* IMETASERVICE2_H_ */
