/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VALUEDATA_H_
#define VALUEDATA_H_

#include "IData.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Warości skalarne.
 * \ingroup Container
 */
class TILIAE_API ValueData : public IData {
public:

        virtual ~ValueData () {}

        const char *getData () const { return data; }
        void setData (const char *data) { this->data = data; }

        const char *getType () const { return type; }
        void setType (const char *type) { this->type = type; }

/*--------------------------------------------------------------------------*/

        void accept (std::string const &key, IDataVisitor *visitor) { visitor->visit (key, this); }

private:

        ValueData () : data (NULL), type (NULL) {}
        ValueData (const char *d) : data (d) {}
        ValueData (const char *d, const char *t) : data (d), type (t) {}
        friend class MetaFactory;

private:

        const char *data;
        const char *type;

};

}

#endif /* VALUEDATA_H_ */
