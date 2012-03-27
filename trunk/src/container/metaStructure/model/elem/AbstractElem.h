/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTELEM_H_
#define ABSTRACTELEM_H_

#include "IElem.h"
#include "../../../../core/Typedefs.h"
#include "../../../../core/string/String.h"
#include "../../../../core/Pointer.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * Wspólny kod elementów.
 * Klasa tylko w celach implementacyjnych tj. wspolny
 * kod w nadklasie.
 * \ingroup Container
 */
class TILIAE_API AbstractElem : public IElem {
public:

        virtual ~AbstractElem () {}

        Ptr<IData> getData () const { return data; }
        void setData (Ptr<IData> data) { this->data = data; }

//        Core::StringMap const &getAttributes () const { return attributes; }
//        void setAttributes (const Core::StringMap &attributes) { this->attributes = attributes; }
//        void addAttribute (const std::string &key, const std::string &attribute) { this->attributes[key] = attribute; }
//        std::string const &getAttribute (const std::string &key) const;

protected:

        AbstractElem () {}
        AbstractElem (const AbstractElem &) {}
        AbstractElem (Ptr <IData> d, const Core::StringMap &a) : data (d)/*, attributes (a)*/ {}

private:

        Ptr <IData> data;
//        Core::StringMap attributes;

};

}

#endif /* ABSTRACTELEM_H_ */
