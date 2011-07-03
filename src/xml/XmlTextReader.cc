/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <boost/lexical_cast.hpp>
#include "XmlTextReader.h"
#include "XmlException.h"
#include "XmlString.h"
#include "../core/string/String.h"

namespace Xml {

using namespace Core;

const std::string XmlTextReader::DEFAULT_ENCODING = "UTF-8";
const std::string XmlTextReader::DEFAULT_URL = "";
const int XmlTextReader::DEFAULT_OPTIONS = 0;

/****************************************************************************/

XmlTextReader::XmlTextReader (const std::string &buffer)
{
        readerForDoc (buffer);
}

/**
 *
 */
XmlTextReader::XmlTextReader (const std::string &buffer,
           const std::string &url,
           const std::string &encoding,
           int options)
{
        readerForDoc (buffer, url, encoding, options);
}

/**
 *
 */
XmlTextReader::XmlTextReader (const std::string &uri,
                const std::string &encoding,
                int options)
{
        readerForFilename (uri, encoding, options);
}

/****************************************************************************/

XmlTextReader::~XmlTextReader ()
{
        if (reader) {
                xmlFreeTextReader(reader);
        }
}

/****************************************************************************/

void XmlTextReader::readerForFilename (const std::string &uri)
{
        int ret = 0;

        if (reader) {
                ret = xmlReaderNewFile (reader, uri.c_str (), DEFAULT_ENCODING.c_str (), DEFAULT_OPTIONS);
        }
        else {
                reader = xmlNewTextReaderFilename (uri.c_str ());
        }

        if (ret == -1 || !reader) {
                throw XmlException (std::string ("XmlTextReader::readerForFilename (") + uri + ") failed.");
        }
}

/****************************************************************************/

void XmlTextReader::readerForFilename (const std::string &uri,
                                const std::string &encoding,
                                int options)
{
        int ret = 0;

        if (reader) {
                ret = xmlReaderNewFile (reader, uri.c_str (), encoding.c_str (), options);
        }
        else {
                reader = xmlReaderForFile (uri.c_str (), encoding.c_str (), options);
        }

        if (ret == -1 || !reader) {
                throw XmlException (std::string ("XmlTextReader::readerForFilename (") +
                                uri + ", " + encoding + ", " +
                                boost::lexical_cast <std::string> (options) + ") failed.");
        }
}

/****************************************************************************/

void XmlTextReader::readerForDoc (const std::string &buffer)
{
        readerForDoc (buffer, DEFAULT_URL, DEFAULT_ENCODING, DEFAULT_OPTIONS);
}

/****************************************************************************/

void XmlTextReader::readerForDoc (const std::string &buffer,
                           const std::string &url,
                           const std::string &encoding,
                           int options)
{
        int ret = 0;

        if (reader) {
                ret = xmlReaderNewDoc (reader,
                                xmlCharStrdup (buffer.c_str ()),
                                url.c_str (),
                                encoding.c_str (),
                                options);
        }
        else {
                reader = xmlReaderForDoc (xmlCharStrdup (buffer.c_str ()),
                                url.c_str (),
                                encoding.c_str (),
                                options);
        }

        if (ret == -1 || !reader) {
                throw XmlException (std::string ("XmlTextReader::readerForDoc (buffer, ") +
                                url + ", " + encoding + ", " +
                                boost::lexical_cast <std::string> (options) + ") failed.");
        }
}

/*##########################################################################*/

void XmlTextReader::close ()
{

        if (xmlTextReaderClose (reader) == -1) {
                throw XmlException ();
        }
}

/****************************************************************************/

std::string XmlTextReader::getAttribute (const std::string &name) const
{

        XmlString ret = xmlTextReaderGetAttribute (reader, XmlString::toXmlChar (name));

        if (!ret) {
                throw XmlException (std::string ("XmlTextReader::getAttribute (") + name + ") failed.");
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::getAttribute (const std::string &localName,
                                            const std::string &namespaceURI) const
{

        XmlString ret = xmlTextReaderGetAttributeNs (reader,
                        XmlString::toXmlChar (localName),
                        XmlString::toXmlChar (namespaceURI));

        if (!ret) {
                throw XmlException (std::string ("XmlTextReader::getAttribute (") + localName + ", " +
                                namespaceURI + ") failed.");
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::getAttribute (int no) const
{

        XmlString ret = xmlTextReaderGetAttributeNo (reader, no);

        if (!ret) {
                throw XmlException (std::string ("XmlTextReader::getAttribute (") + boost::lexical_cast <std::string> (no) + ") failed.");
        }

        return ret;
}

//getRemainder - not implemented

/****************************************************************************/

std::string XmlTextReader::lookupNamespace (const std::string &prefix) const
{

        XmlString ret  = xmlTextReaderLookupNamespace (reader, XmlString::toXmlChar (prefix));

        if (!ret) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::moveToAttribute (const std::string &name)
{

        int ret = xmlTextReaderMoveToAttribute (reader, XmlString::toXmlChar (name));

        if (ret == -1) {
                throw XmlException (std::string ("XmlTextReader::moveToAttribute (") + name + ") failed.");
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::moveToAttribute (int no)
{

        int ret = xmlTextReaderMoveToAttributeNo (reader, no);

        if (ret == -1) {
                throw XmlException (std::string ("XmlTextReader::moveToAttribute (") +
                                boost::lexical_cast <std::string> (no) + ") failed.");
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::moveToAttribute (const std::string &localName,
                                       const std::string &namespaceURI)
{


        int ret = xmlTextReaderMoveToAttributeNs (reader, XmlString::toXmlChar (localName), XmlString::toXmlChar (namespaceURI));

        if (ret == -1) {
                throw XmlException (std::string ("XmlTextReader::moveToAttribute (") + localName + ", " +
                                namespaceURI + ") failed.");
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::moveToElement ()
{

        int ret = xmlTextReaderMoveToElement (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::moveToFirstAttribute ()
{

        int ret = xmlTextReaderMoveToFirstAttribute (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::moveToNextAttribute()
{

        int ret = xmlTextReaderMoveToNextAttribute (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::read () const
{

        int ret = xmlTextReaderRead (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::readAttributeValue() const
{

        int ret = xmlTextReaderReadAttributeValue (reader);

        if (ret == -1) {
                throw XmlException ("XmlTextReader::readAttributeValue () failed.");
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::readInnerXml() const
{

        XmlString ret = xmlTextReaderReadInnerXml (reader);

        if (!ret) {
                throw XmlException ("XmlTextReader::readInnerXml () failed.");
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::readOuterXml() const
{

        XmlString ret = xmlTextReaderReadOuterXml (reader);

        if (!ret) {
                throw XmlException ("XmlTextReader::readOuterXml () failed.");
        }

        return ret;
}

/****************************************************************************/
/****************************************************************************/
//Properties
/****************************************************************************/
/****************************************************************************/

int XmlTextReader::attributeCount () const
{

        int ret = xmlTextReaderAttributeCount (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::baseUri () const
{

        xmlChar *ret = xmlTextReaderBaseUri (reader);

        if (!ret) {
                throw XmlException ("XmlTextReader::baseUri () failed.");
        }

        return CHAR_CAST (ret);
}

/****************************************************************************/

int XmlTextReader::depth () const
{

        int ret = xmlTextReaderDepth (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::encoding () const
{
        XmlString ret = xmlTextReaderConstEncoding (reader);

        if (!ret) {
                throw XmlException ();
        }

        return ret;
}


/****************************************************************************/

bool XmlTextReader::hasValue () const
{

        int ret = xmlTextReaderHasValue (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::isDefault () const
{

        int ret = xmlTextReaderIsDefault (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::isEmptyElement () const
{

        int ret = xmlTextReaderIsEmptyElement (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::getParserColumnNumber () const
{

        int ret = xmlTextReaderGetParserColumnNumber (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::getParserLineNumber () const
{

        int ret = xmlTextReaderGetParserLineNumber (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::getParserProp (int prop) const
{

        int ret = xmlTextReaderGetParserProp (reader, prop);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::localName () const
{
        XmlString ret = xmlTextReaderConstLocalName (reader);

        if (!ret) {
                throw XmlException ("XmlTextReader::localName () failed.");
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::name () const
{
        XmlString ret = xmlTextReaderConstName (reader);

        if (!ret) {
                throw XmlException ("XmlTextReader::name () failed.");
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::namespaceUri () const
{
        XmlString ret = xmlTextReaderConstNamespaceUri (reader);

        if (!ret) {
                throw XmlException ("XmlTextReader::namespaceUri () failed.");
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::nodeType () const
{

        int ret = xmlTextReaderNodeType (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::normalization () const
{

        int ret = xmlTextReaderNormalization (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::prefix () const
{

        XmlString ret = xmlTextReaderPrefix (reader);

        if (!ret) {
                return "";
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::quoteChar () const
{

        int ret = xmlTextReaderQuoteChar (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::readState () const
{

        int ret = xmlTextReaderReadState (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::value () const
{

        XmlString ret = xmlTextReaderValue (reader);

        if (!ret) {
                return "";
        }

        return ret;
}


/****************************************************************************/

std::string XmlTextReader::xmlLang () const
{

        XmlString ret = xmlTextReaderConstXmlLang (reader);

        if (!ret) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

// Dodatkowe z libxml

long XmlTextReader::byteConsumed () const
{

        long ret = xmlTextReaderByteConsumed (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}


/****************************************************************************/

//std::string XmlTextReader::string () const
//{
//
//        XmlString ret = xmlTextReaderConstString (reader);
//
//        if (!ret) {
//                throw XmlException ();
//        }
//
//        return ret;
//}

/****************************************************************************/

std::string XmlTextReader::xmlVersion () const
{

        XmlString ret = xmlTextReaderConstXmlVersion (reader);

        if (!ret) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::next () const
{

        int ret = xmlTextReaderNext (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}


/****************************************************************************/

bool XmlTextReader::hasAttributes () const
{

        int ret = xmlTextReaderHasAttributes (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::isNamespaceDecl () const
{

        int ret = xmlTextReaderIsNamespaceDecl (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::isValid () const
{

        int ret = xmlTextReaderIsValid (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::nextSibling () const
{

        int ret = xmlTextReaderNextSibling (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::relaxNGValidate (const std::string &rng) const
{

        int ret = xmlTextReaderRelaxNGValidate (reader, rng.c_str ());

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::schemaValidate (const std::string &xsd) const
{

        int ret = xmlTextReaderSchemaValidate (reader, xsd.c_str ());

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

int XmlTextReader::setParserProp (int prop, int value)
{

        int ret = xmlTextReaderSetParserProp (reader, prop, value);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

bool XmlTextReader::standalone () const
{

        int ret = xmlTextReaderStandalone (reader);

        if (ret == -1) {
                throw XmlException ();
        }

        return ret;
}

/****************************************************************************/

std::string XmlTextReader::strReaderType (int type)
{
        static std::string labels[] = { "XML_READER_TYPE_NONE",
                "XML_READER_TYPE_ELEMENT",
                "XML_READER_TYPE_ATTRIBUTE",
                "XML_READER_TYPE_TEXT",
                "XML_READER_TYPE_CDATA",
                "XML_READER_TYPE_ENTITY_REFERENCE",
                "XML_READER_TYPE_ENTITY",
                "XML_READER_TYPE_PROCESSING_INSTRUCTION",
                "XML_READER_TYPE_COMMENT",
                "XML_READER_TYPE_DOCUMENT",
                "XML_READER_TYPE_DOCUMENT_TYPE",
                "XML_READER_TYPE_DOCUMENT_FRAGMENT",
                "XML_READER_TYPE_NOTATION",
                "XML_READER_TYPE_WHITESPACE",
                "XML_READER_TYPE_SIGNIFICANT_WHITESPACE",
                "XML_READER_TYPE_END_ELEMENT",
                "XML_READER_TYPE_END_ENTITY",
                "XML_READER_TYPE_XML_DECLARATION" };

        static int lastElem = (int)XML_READER_TYPE_XML_DECLARATION;

        if (type < 0 || type > lastElem) {
                return "";
        }

        return labels[type];
}

}
