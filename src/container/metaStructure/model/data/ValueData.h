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

        ValueData () {}
        ValueData (const std::string &d, const std::string &t) : data (d), type (t) {}
        virtual ~ValueData () {}

        static Ptr <ValueData> create (const std::string &d = std::string (), const std::string &t = std::string ()) {
                return Ptr <ValueData> (new ValueData (d, t));
        }

        std::string const &getData () const { return data; }
        void setData (const std::string &data) { this->data = data; }

        std::string const &getType () const { return type; }
        void setType (const std::string &type) { this->type = type; }

/*--------------------------------------------------------------------------*/

        void accept (IDataVisitor *visitor) { visitor->visit (this); }

private:

        std::string data;
        std::string type;

};

}

#endif /* VALUEDATA_H_ */
