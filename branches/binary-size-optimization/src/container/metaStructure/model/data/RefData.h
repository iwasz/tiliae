/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REFDATA_H_
#define REFDATA_H_

#include "IData.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Implementuje ref-y.
 * \ingroup Container
 */
struct TILIAE_API RefData : public IData {

        RefData () : IData () {}
        RefData (const std::string &d) : data (d) {}
        virtual ~RefData () {}

        std::string const &getData () const { return data; }
        void setData (const std::string &data) { this->data = data; }

        void accept (std::string const &key, IDataVisitor *visitor) { visitor->visit (key, this); }

private:

        std::string data;

};

}

#endif /* REFDATA_H_ */
