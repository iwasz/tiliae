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
        static Ptr <PrintMetaService> create () { return Ptr <PrintMetaService> (new PrintMetaService); }

        void onContainer (MetaContainer *data);
        bool onMetaBegin (IMeta *data) { return true; }
        bool onMetaEnd (IMeta *data) { return true; }
        bool onMappedMetaBegin (MappedMeta *data);
        bool onMappedMetaEnd (MappedMeta *data) { return true; }
        bool onIndexedMetaBegin (IndexedMeta *data);
        bool onIndexedMetaEnd (IndexedMeta *data) { return true; }
        void onConstructorArgsBegin (IMeta *data) {}
        void onConstructorArgsEnd (IMeta *data) {}
        void onValueData (std::string const &key, ValueData *data);
        void onNullData (std::string const &key, NullData *data);
        void onRefData (std::string const &key, RefData *data);

    /*--------------------------------------------------------------------------*/

        Core::String *getBuffer () const { return buffer; }
        void setBuffer (Core::String *buffer) { this->buffer = buffer; }

private:

        Core::String *buffer;
};

}

#	endif /* PRINTSERVICE_H_ */
