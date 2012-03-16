/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <mxml.h>
#include <iostream>
#include "MXmlMetaService.h"

namespace Container {

void saxHandler (mxml_node_t *node, mxml_sax_event_t event, void *data)
{
        switch (event) {
        case MXML_SAX_CDATA:
                break;

        case MXML_SAX_COMMENT:
                break;

        case MXML_SAX_DATA:
                break;

        case MXML_SAX_DIRECTIVE:
                break;

        case MXML_SAX_ELEMENT_CLOSE:
                {
                        char const *name = mxmlGetElement (node);
                        std::cerr << "Elem close : " << name << std::endl;
                }
                break;

        case MXML_SAX_ELEMENT_OPEN:
                {
                        char const *name = mxmlGetElement (node);
                        std::cerr << "Elem open : " << name << std::endl;
                }
                break;

        default:
                break;
        }
}

/****************************************************************************/

void MXmlMetaService::parse (std::string const &path)
{
        FILE *fp;
//        mxml_node_t *tree;

        fp = fopen (path.c_str (), "r");

        mxmlSAXLoadFile (NULL, fp, MXML_TEXT_CALLBACK, saxHandler, NULL);

        fclose(fp);
}

} /* namespace Container */
