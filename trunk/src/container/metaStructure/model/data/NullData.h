/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NULLDATA_H_
#define NULLDATA_H_

#include "IData.h"
#include "../../../../core/string/String.h"
#include "../../../../core/ApiMacro.h"
#include "../../../../core/Pointer.h"

namespace Container {

/**
 * Nulle.
 * \ingroup Container
 */
struct TILIAE_API NullData : public IData {

        virtual ~NullData () {}

        static Ptr <NullData> create () {
                return Ptr <NullData> (new NullData ());
        }

        std::string const &getData () const { static std::string s ("<NULL>"); return s; }
        void accept (IDataVisitor *visitor) { visitor->visit (this); }
};

}

#endif /* NULLDATA_H_ */
