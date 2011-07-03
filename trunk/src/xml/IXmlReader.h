/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLREADER_H_
#define XMLREADER_H_

#include <libxml/xmlreader.h>
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

namespace Xml {

/**
 * Wzorowane na :
 * http://dotgnu.org/pnetlib-doc/System/Xml/XmlReader.html
 * http://xmlsoft.org/html/libxml-xmlreader.html
 */
struct TILIAE_API IXmlReader {

        virtual ~IXmlReader () {}

        virtual void readerForFilename (const std::string &uri) = 0;

        /**
         *
         */
        virtual void readerForFilename (const std::string &uri,
                                        const std::string &encoding,
                                        int options) = 0;

        /**
         *
         */
        virtual void readerForDoc (const std::string &buffer) = 0;

        /**
         *
         */
        virtual void readerForDoc (const std::string &buffer,
                                   const std::string &url,
                                   const std::string &encoding,
                                   int options) = 0;


/*--------------------------------------------------------------------------*/

        virtual void close () = 0;
        virtual std::string lookupNamespace (const std::string &prefix) const = 0;

        virtual std::string getAttribute (const std::string &name) const = 0;
        virtual std::string getAttribute (const std::string &localName, const std::string &namespaceURI) const = 0; //X
        virtual std::string getAttribute (int no) const = 0; //X

        virtual bool moveToAttribute (const std::string &name) = 0; //X
        virtual bool moveToAttribute (int no) = 0; //X
        virtual bool moveToAttribute (const std::string &localName, const std::string &namespaceURI) = 0; //X

        virtual bool moveToElement() = 0; //X
        virtual bool moveToFirstAttribute() = 0; //X
        virtual bool moveToNextAttribute() = 0; //X

        virtual bool read () const = 0; //X

        /**
         * To działa tak, ze pozwala sie zaglebic do wartosci atrybutu.
         * Test tej metody nazywa sie  XmlTest::testGetAttributeValue i
         * tlumaczy jak ona dziala. Powiedzmy ze mamy tag:
         *
         * <bean id="mojBean"/>
         *
         * read () - spowoduje ustawienie readera na depth () == 0, czyli
         * na elemencie glownym bean.
         *
         * moveToFirstAttribute () - spowoduje przejscie o krok dalej,
         * czyli ustawienie readera na atrybucie id (jego name to "id",
         * a value to "mojBean").
         *
         * readAttributeValue () - wreszcie, spowoduje ustawienie sie
         * readera na wartości atrybutu i bedziemy miec depth () == 2,
         * name () == "#text", value () == "mojBean".
         */
        virtual bool readAttributeValue () const = 0; // X

        /**
         * Kiedy mam przykladowy XML powiedzmy taki :
         *
         * <tag>
         *      <tagWew/>
         * </tag>
         *
         * read () - spowoduje ustawienie readera na depth () == 0, czyli
         * na elemencie glownym tag.
         *
         * readInnerXml () - zwróci to co jest w śrdoku tego taga, czyli
         * coś w stylu <tagWew/> i to ze wszystkimi spacjami, LFami etc.
         */
        virtual std::string readInnerXml () const = 0; //X

        /**
         * Kiedy mam przykladowy XML powiedzmy taki :
         *
         * <tag>
         *      <tagWew/>
         * </tag>
         *
         * read () - spowoduje ustawienie readera na depth () == 0, czyli
         * na elemencie glownym tag.
         *
         * readOuterXml () - zwróci mój tag z tym co ma w środku, czyli w
         * przypadku powyższego przykladu zwróci cały XML. Oczywiście ze
         * wszystkimi białymi znakami.
         */
        virtual std::string readOuterXml () const = 0; //X
        virtual int attributeCount () const = 0; //X

        /**
         * Nie wiem co to robi.
         */
        virtual std::string baseUri () const = 0;
        virtual int depth () const = 0; //X
        virtual std::string encoding () const = 0; //X

        /**
         * A to dziala tak, ze jesli mamy np. text bezposrednio w
         * tagu, to zwroci true, jesli jednak mamy jakis ,,podtag'',
         * to zwraca false, no nie traktuje dalszego XML jako wartosci.
         */
        virtual bool hasValue () const = 0; //X
        virtual bool isDefault () const = 0;
        virtual bool isEmptyElement () const = 0; //X
        virtual int getParserColumnNumber () const = 0; //X
        virtual int getParserLineNumber () const = 0; //X

        virtual int getParserProp (int prop) const = 0;
        virtual int setParserProp (int prop, int value) = 0;

        virtual std::string localName () const = 0; //X
        virtual std::string namespaceUri () const = 0; //X
        virtual std::string name () const = 0; //X
        virtual int nodeType () const = 0; //X
        virtual bool normalization () const = 0;
        virtual std::string prefix () const = 0;
        virtual int quoteChar () const = 0;
        virtual int readState () const = 0;
        virtual std::string value () const = 0; //X
        virtual std::string xmlLang () const = 0;

        virtual long byteConsumed () const = 0; //X
        virtual std::string xmlVersion () const = 0; //X
        virtual bool next () const = 0; //X
        virtual bool hasAttributes () const = 0; //X
        virtual bool isNamespaceDecl () const = 0;
        virtual bool isValid () const = 0;
        virtual bool nextSibling () const = 0;
        virtual int relaxNGValidate (const std::string &rng) const = 0;
        virtual int schemaValidate (const std::string &xsd) const = 0;
        virtual bool standalone () const = 0;

};

}

#endif /* XMLREADER_H_ */
