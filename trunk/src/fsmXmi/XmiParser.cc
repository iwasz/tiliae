/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <stack>
#include "XmiParser.h"
#include "core/Pointer.h"
#include "stateMachine2/structure/Model.h"
#include "stateMachine2/structure/Region.h"
#include "stateMachine2/structure/State.h"
#include "stateMachine2/structure/StateMachine.h"
#include "xml/XmlTextReader.h"

namespace FsmXmi {
using namespace StateMachine;
using namespace Xml;

typedef std::stack <Ptr <Region> > RegionStack;
typedef std::stack <Ptr <State> > StateStack;

struct XmiParserPrivate {

        /// Current machine.
        Ptr < ::StateMachine::StateMachine> machine;
        RegionStack regionStack;
        StateStack stateStack;

};

/*##########################################################################*/

XmiParser::XmiParser () : impl (new XmiParserPrivate) {}

/****************************************************************************/

Ptr <StateMachine::Model> XmiParser::parse (std::string const &path)
{
        Ptr <StateMachine::Model> model;

        XmlTextReader reader;
        reader.readerForFilename (path);

        while (reader.read ()) {

                int nodeType = reader.nodeType ();

                if (nodeType != XML_READER_TYPE_ELEMENT &&
                    nodeType != XML_READER_TYPE_ATTRIBUTE &&
                    nodeType != XML_READER_TYPE_TEXT &&
                    nodeType != XML_READER_TYPE_END_ELEMENT) {
                        continue;
                }

#if 0
                std::cout << std::string ("E: Depth=") + boost::lexical_cast <std::string> (reader.depth ()) +
                                ", nodeType=" + boost::lexical_cast <std::string> (reader.nodeType ()) +
                                ", nodeName=" + reader.name () + ", isEmptyElem=" + boost::lexical_cast <std::string> (reader.isEmptyElement ()) +
                                "\nvalue=[" + reader.value () + "]\n\n";
#endif

                if (reader.nodeType () == XML_READER_TYPE_ELEMENT) {

                        processStartElement (reader.name ());

                        while (reader.moveToNextAttribute ()) {

                                processAttribute (reader.name (), reader.value ());
#if 0
                                std::cout << std::string ("  A: Depth=") + boost::lexical_cast <std::string> (reader.depth ()) +
                                                ", nodeType=" + boost::lexical_cast <std::string> (reader.nodeType ()) +
                                                ", attribCount=" + boost::lexical_cast <std::string> (reader.attributeCount ()) +
                                                ", hasAttrib=" + boost::lexical_cast <std::string> (reader.hasAttributes ()) +
                                                ", name=" + reader.name () + "\nvalue=[" + reader.value () + "]\n";
#endif
                        }
                }
                else if (reader.nodeType () == XML_READER_TYPE_END_ELEMENT) {
                        processEndElement (reader.name ());
                }
                else if (reader.nodeType () == XML_READER_TYPE_TEXT) {
                        processText (reader.value ());
                }

        }


        return model;
}

/****************************************************************************/

void XmiParser::processStartElement (std::string const &nodeName)
{
#if 1
        std::cout << "XmiParser::processStartElement : " << nodeName << std::endl;
#endif

        // We consider only one model which comes forst in the XMI file.
        if (nodeName == "uml:Model") {
                return;
        }

}

/****************************************************************************/

void XmiParser::processEndElement (std::string const &nodeName)
{
#if 1
        std::cout << "XmiParser::processEndElement : " << nodeName << std::endl;
#endif
}

/****************************************************************************/

void XmiParser::processText (std::string const &text)
{
#if 1
        std::cout << "XmiParser::processText : " << text << std::endl;
#endif
}

/****************************************************************************/

void XmiParser::processAttribute (std::string const &name, std::string const &value)
{
#if 1
        std::cout << "XmiParser::processAttribute name : " << name << ", value : " << value << std::endl;
#endif
}

} /* namespace FsmXmi */
