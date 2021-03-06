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
#include "core/ApiMacro.h"

namespace Container {

/**
 * Implementuje ref-y.
 * \ingroup Container
 */
class TILIAE_API RefData : public IData {
public:

        virtual ~RefData () {}

        const char *getData () const { return data; }
        void setData (const char *data) { this->data = data; }

        void accept (DataKey const *dk, IDataVisitor *visitor) { visitor->visit (dk, this); }

private:

        RefData () : IData (), data (NULL) {}
        RefData (const char *d) : data (d) {}
        friend class MetaFactory;

private:

        const char *data;

};

}

#endif /* REFDATA_H_ */
