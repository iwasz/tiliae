/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMIPARSER_H_
#define XMIPARSER_H_

#include <memory>
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace StateMachine {
class Model;
}

namespace FsmXmi {
class XmiParserPrivate;

/**
 *
 */
class TILIAE_API XmiParser {
public:

        XmiParser ();
        Ptr <StateMachine::Model> parse (std::string const &path);

private:

        void processStartElement (std::string const &nodeName);
        void processEndElement (std::string const &nodeName);
        void processText (std::string const &text);
        void processAttribute (std::string const &name, std::string const &value);

private:

        std::auto_ptr <XmiParserPrivate> impl;

};

} /* namespace FsmXmi */

#	endif /* XMIPARSER_H_ */
