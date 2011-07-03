/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLTEXTREADER_H_
#define XMLTEXTREADER_H_

#include "IXmlReader.h"
#include "../core/ApiMacro.h"

namespace Xml {

/**
 * Niezaimplementowane wiekszosc konstruktorów + funkcji tworzacych, oraz:
 * ReadBase64
 * ReadBinHex
 * ReadChars
 * ReadString
 * ResetState
 * ResolveEntity
 * eof
 * item
 * XmlResolver
 * XmlSpace
 * string
 */
class TILIAE_API XmlTextReader : public IXmlReader {
public:

        /**
         *
         */
        XmlTextReader () : reader (NULL) {}

        /**
         *
         */
        XmlTextReader (const std::string &buffer);

        /**
         *
         */
        XmlTextReader (const std::string &buffer,
                   const std::string &url,
                   const std::string &encoding,
                   int options);

        /**
         *
         */
        XmlTextReader (const std::string &uri,
                        const std::string &encoding,
                        int options);

        /**
         * Destruktor.
         */
        virtual ~XmlTextReader ();

        /**
         *
         */
        virtual void readerForFilename (const std::string &uri);

        /**
         *
         */
        virtual void readerForFilename (const std::string &uri,
                                        const std::string &encoding,
                                        int options);

        /**
         *
         */
        virtual void readerForDoc (const std::string &buffer);

        /**
         *
         */
        virtual void readerForDoc (const std::string &buffer,
                                   const std::string &url,
                                   const std::string &encoding,
                                   int options);


/*--------------------------------------------------------------------------*/

        virtual void close ();
        virtual std::string lookupNamespace (const std::string &prefix) const; //X

        virtual std::string getAttribute (const std::string &name) const; //X
        virtual std::string getAttribute (const std::string &localName, const std::string &namespaceURI) const; //X
        virtual std::string getAttribute (int no) const; //X

        virtual bool moveToAttribute (const std::string &name); //X
        virtual bool moveToAttribute (int no); //X
        virtual bool moveToAttribute (const std::string &localName, const std::string &namespaceURI); //X

        virtual bool moveToElement(); //X
        virtual bool moveToFirstAttribute(); //X
        virtual bool moveToNextAttribute(); //X

        virtual bool read () const; //X

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
        virtual bool readAttributeValue () const; // X

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
        virtual std::string readInnerXml () const; //X

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
        virtual std::string readOuterXml () const; //X
        virtual int attributeCount () const; //X

        /**
         * Nie wiem co to robi.
         */
        virtual std::string baseUri () const;
        virtual int depth () const; //X
        virtual std::string encoding () const; //X

        /**
         * A to dziala tak, ze jesli mamy np. text bezposrednio w
         * tagu, to zwroci true, jesli jednak mamy jakis ,,podtag'',
         * to zwraca false, no nie traktuje dalszego XML jako wartosci.
         */
        virtual bool hasValue () const; //X
        virtual bool isDefault () const;
        virtual bool isEmptyElement () const; //X
        virtual int getParserColumnNumber () const; //X
        virtual int getParserLineNumber () const; //X

        virtual int getParserProp (int prop) const;
        virtual int setParserProp (int prop, int value);

        virtual std::string localName () const; //X
        virtual std::string namespaceUri () const; //X
        virtual std::string name () const; //X
        virtual int nodeType () const; //X
        virtual bool normalization () const;
        virtual std::string prefix () const;
        virtual int quoteChar () const;
        virtual int readState () const;
        virtual std::string value () const; //X
        virtual std::string xmlLang () const;

        virtual long byteConsumed () const; //X
//        virtual std::string string () const;
        virtual std::string xmlVersion () const; //X
        virtual bool next () const; //X
        virtual bool hasAttributes () const; //X
        virtual bool isNamespaceDecl () const;
        virtual bool isValid () const;
        virtual bool nextSibling () const;
        virtual int relaxNGValidate (const std::string &rng) const;
        virtual int schemaValidate (const std::string &xsd) const;
        virtual bool standalone () const;

/*--------------------------------------------------------------------------*/

        static std::string strReaderType (int type);

public:

        const static std::string DEFAULT_ENCODING;
        const static std::string DEFAULT_URL;
        const static int DEFAULT_OPTIONS;

private:

        xmlTextReaderPtr reader;

};

}

#endif /* XMLTEXTREADER_H_ */
