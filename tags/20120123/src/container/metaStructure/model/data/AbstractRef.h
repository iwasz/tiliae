/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTREF_H_
#define ABSTRACTREF_H_

#include "IData.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Referencje - kod wspólny.
 * \ingroup Container
 */
class TILIAE_API AbstractRef : public IData {
public:

        virtual ~AbstractRef () {}

        enum Target { NONE, BEAN, LOCAL };

        std::string const &getData () const { return data; }
        void setData (const std::string &data) { this->data = data; }

        Target getTarget () const { return target; }
        void setTarget (Target target) { this->target = target; }

protected:

        AbstractRef () : target (NONE) {}
        AbstractRef (const AbstractRef &) {}
        AbstractRef (const std::string &d, Target t) : data (d), target (t) {}

private:

        std::string data;
        Target target;

};

}

#endif /* ABSTRACTREF_H_ */
