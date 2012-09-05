/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PRINTSERVICE_H_
#define PRINTSERVICE_H_

#include "AbstractMetaService.h"
#include "../../../core/ApiMacro.h"

namespace Container {

/**
 * Wypisuje cały ten pierdolnik (metastrukturę w sensie) na ekran.
 * \ingroup Container
 */
struct PrintMetaService : public AbstractMetaService {

        TILIAE_API PrintMetaService () : buffer (NULL) {}
        virtual ~PrintMetaService () {}

        void onContainer (MetaContainer const *data);
        bool onMetaBegin (MetaObject const *data) { return true; }
        bool onMetaEnd (MetaObject const *data) { return true; }
        bool onMappedMetaBegin (MetaObject const *data);
        bool onMappedMetaEnd (MetaObject const *data) { return true; }
        bool onIndexedMetaBegin (MetaObject const *data);
        bool onIndexedMetaEnd (MetaObject const *data) { return true; }
        void onConstructorArgsBegin (MetaObject const *data) {}
        void onConstructorArgsEnd (MetaObject const *data) {}
        void onValueData (DataKey const *dk, ValueData const *data);
        void onNullData (DataKey const *dk, NullData const *data);
        void onRefData (DataKey const *dk, RefData const *data);

    /*--------------------------------------------------------------------------*/

        Core::String *getBuffer () const { return buffer; }
        void setBuffer (Core::String *buffer) { this->buffer = buffer; }

private:

        Core::String *buffer;
};

}

#	endif /* PRINTSERVICE_H_ */
