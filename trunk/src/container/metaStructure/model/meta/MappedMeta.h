/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAPPEDMETA_H_
#define MAPPEDMETA_H_

#include "AbstractMeta.h"
#include "../elem/MapElem.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Odzwierciedla takie struktury jak bean, mapa.
 * Ta klasa nie zawiera zbyt wiele, poniewaz wiekszosc jej
 * dzialan jest wyrzucona do visitorów.
 * \ingroup Container
 */
class TILIAE_API MappedMeta : public AbstractMeta {
public:

        virtual ~MappedMeta () {}

        const MapElemList &getFieldsAsList () const { return fields; }
        void setFields (const MapElemList &fields) { this->fields = fields; }

        // TODO To jest tymczasowy interfejs, trzeba zorbić porządek z tymi metodami.
        void addField (Ptr <MapElem> field);
        void addFields (const MapElemList &fields);
        void addFieldFront (Ptr <MapElem> field);
        void addFieldsFront (const MapElemList &fields);
        void clearFields () { fields.clear (); }

        /// O(N)
        Ptr <MapElem> getField (const std::string &key);

        /// O(N)
        void removeField (const std::string &key);

/*--------------------------------------------------------------------------*/

        void accept (IMetaVisitor *visitor) { visitor->visit (this); }

private:

        MapElemList fields;

};

} // nam

#endif /* MAPPEDMETA_H_ */
