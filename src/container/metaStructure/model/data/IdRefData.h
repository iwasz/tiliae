/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDREFDATA_H_
#define IDREFDATA_H_

#include "AbstractRef.h"
#include "../../../../core/Pointer.h"
#include "../../../../core/string/String.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Data typu IdRef.
 * \ingroup Container
 * TODO Wypierdolić to w chuj.
 */
struct TILIAE_API IdRefData : public AbstractRef {

        IdRefData () : AbstractRef () {}
        IdRefData (const std::string &d, Target t) : AbstractRef (d, t) {}
        virtual ~IdRefData () {}

        static Ptr <IdRefData> create (const std::string &d = std::string (), Target t = AbstractRef::BEAN) {
                return Ptr <IdRefData> (new IdRefData (d, t));
        }

        void accept (IDataVisitor *visitor) { visitor->visit (this); }
};

}

#endif /* IDREFDATA_H_ */
