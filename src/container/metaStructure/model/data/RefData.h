/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REFDATA_H_
#define REFDATA_H_

#include "AbstractRef.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Implementuje ref-y.
 * \ingroup Container
 */
struct TILIAE_API RefData : public AbstractRef {

        RefData () : AbstractRef () {}
        RefData (const std::string &d, Target t) : AbstractRef (d, t) {}
        virtual ~RefData () {}

        static Ptr <RefData> create (const std::string &d = std::string (), Target t = AbstractRef::BEAN) {
                return Ptr <RefData> (new RefData (d, t));
        }

        void accept (IDataVisitor *visitor) { visitor->visit (this); }
};

}

#endif /* REFDATA_H_ */
