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
#include <Pointer.h>

namespace Container {

class ValueData;
class NullData;
class RefData;

struct MetaObject;
struct MetaObject;

struct MetaContainer;

struct MetaObject;
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

        virtual bool onMetaBegin (MetaObject *data) = 0;
        virtual bool onMetaEnd (MetaObject *data) = 0;
        virtual bool onMappedMetaBegin (MetaObject *data) = 0;
        virtual bool onMappedMetaEnd (MetaObject *data) = 0;
        virtual bool onIndexedMetaBegin (MetaObject *data) = 0;
        virtual bool onIndexedMetaEnd (MetaObject *data) = 0;

        virtual void onConstructorArgsBegin (MetaObject *data) = 0;
        virtual void onConstructorArgsEnd (MetaObject *data) = 0;

        virtual void onValueData (std::string const &key, ValueData *data) = 0;
        virtual void onNullData (std::string const &key, NullData *data) = 0;
        virtual void onRefData (std::string const &key, RefData *data) = 0;

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
