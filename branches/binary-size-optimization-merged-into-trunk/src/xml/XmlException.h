/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLEXCEPTION_H_
#define XMLEXCEPTION_H_

#include "../core/Exception.h"
#include "../core/ApiMacro.h"

namespace Xml {

class TILIAE_API XmlException : public Core::Exception {
public:

        XmlException (std::string const &m = "") : Core::Exception (m) {}
        virtual ~XmlException () throw () {}

//private:
//
//        // TODO http://dotgnu.org/pnetlib-doc/System/Xml/XmlException.html
//        int lineNumber;
//        int linePosition;

};

}

#endif /* XMLEXCEPTION_H_ */
