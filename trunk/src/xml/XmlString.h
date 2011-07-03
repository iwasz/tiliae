/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLSTRING_H_
#define XMLSTRING_H_

#include <libxml/xmlreader.h>
#include "../core/string/String.h"

namespace Xml {

#define CHAR_CAST(a) reinterpret_cast <char *> (a)
#define CONST_CHAR_CAST(a) reinterpret_cast <const char *> (a)

/****************************************************************************/

/**
 * Temp class, only for this implementation. Not to be
 * used elsewhere.
 */
class XmlString {
public:

        XmlString (const xmlChar *s) : body (NULL), bodyConst (s), autoFree (false) {}
        XmlString (xmlChar *s, bool a = true) : body (s), bodyConst (NULL), autoFree (a) {}
        ~XmlString () { if (autoFree && body) { xmlFree (body); } }

        // To jest najbardziej tricky
        operator std::string () const;
        operator bool () const { return bool (body) || bool (bodyConst); }

        static const xmlChar *toXmlChar (const std::string &s) { return xmlCharStrdup (s.c_str ()); }

private:

        xmlChar *body;
        const xmlChar *bodyConst;
        bool autoFree;

};

}

#endif /* XMLSTRING_H_ */
