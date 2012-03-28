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
#include "../data/IData.h"

namespace Container {

/**
 * Odzwierciedla takie struktury jak bean, mapa.
 * Ta klasa nie zawiera zbyt wiele, poniewaz wiekszosc jej
 * dzialan jest wyrzucona do visitorów.
 * \ingroup Container
 */
class TILIAE_API MappedMeta : public AbstractMeta {
public:

        virtual ~MappedMeta ();

        Type getType () const { return MAPPED; }

        DataMap getFields () const;
        void addField (DataKey const &dataKey);
        IData *getField (const std::string &key);

/*--------------------------------------------------------------------------*/

        void accept (IMetaVisitor *visitor) { visitor->visit (this); }

private:

        DataMap fields;
};

} // nam

#endif /* MAPPEDMETA_H_ */
