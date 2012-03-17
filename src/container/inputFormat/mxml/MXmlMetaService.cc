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
#include "../../common/Exceptions.h"
#include "../../metaStructure/model/MetaContainer.h"
#include "../../metaStructure/model/meta/MappedMeta.h"
#include "../../metaStructure/model/meta/IndexedMeta.h"

namespace Container {

/**
 * Tu się wykonuje cały algorytm. Ta implementacja jest ukryta przed użytkownikiem. Taki PIMPL.
 */
class Impl {
public:

        void onOpenElement (mxml_node_t *node);
        void onCloseElement (mxml_node_t *node);

        void onOpenBean (mxml_node_t *node);
        void onOpenProperty (mxml_node_t *node);

/****************************************************************************/

        MappedMeta *pushNewMappedMeta ();
        IndexedMeta *pushNewIndexedMeta ();
        void fillMetaArguments (mxml_node_t *node, IMeta *meta);

        MapElem *pushNewMapElem ();
        ListElem *pushNewListElem ();

private:

        /// Pamięć podręczna obiektów Meta (odzwierciadlających beany, mapy listy).
        MetaStack metaStack;

        /// Pamięć podręczna obiektów MetaElem (odzwierciadlających property beanów, elementy list i map).
        MetaElemStack metaElemStack;
};

/****************************************************************************/

void saxHandler (mxml_node_t *node, mxml_sax_event_t event, void *data)
{
        Impl *impl = static_cast <Impl *> (data);

        mxml_type_t type = mxmlGetType (node);

        switch (type) {
        case MXML_ELEMENT:
                std::cerr << "MXML_ELEMENT ";
                break;

        case MXML_INTEGER:
                std::cerr << "MXML_INTEGER ";
                break;

        case MXML_OPAQUE:
                std::cerr << "MXML_OPAQUE ";
                break;

        case MXML_REAL:
                std::cerr << "MXML_REAL ";
                break;

        case MXML_TEXT:
                std::cerr << "MXML_TEXT ";
                break;

        default:
                break;
        }

        switch (event) {
        case MXML_SAX_CDATA:
                {
//                        char const *data = mxmlGetCDATA (node);
                        std::cerr << "MXML_SAX_CDATA" << std::endl;
                }
                break;

        case MXML_SAX_DATA:
                {
                        std::cerr << "MXML_SAX_DATA" << std::endl;
                }
                break;

        case MXML_SAX_ELEMENT_CLOSE:

                if (type == MXML_ELEMENT) {
                        impl->onCloseElement (node);
                }
                break;

        case MXML_SAX_ELEMENT_OPEN:
//                {
//                        char const *name = mxmlGetElement (node);
//                        std::cerr << "Elem open : " << name << std::endl;
//
//                        if (type == MXML_ELEMENT) {
//
//                                int numAttrs = node->value.element.num_attrs;
//                                std::cerr << " Name : " << node->value.element.name << ", numAtrs = " << numAttrs << std::endl;
//
//                                for (int i = 0; i < numAttrs; ++i) {
//                                        mxml_attr_t attr = node->value.element.attrs[i];
//
//                                        std::cerr << " Attr name=" << attr.name << ", value=" << attr.value << std::endl;
//                                }
//                        }
//                }

                if (type == MXML_ELEMENT) {
                        impl->onOpenElement (node);
                }

                break;

        default:
                break;
        }
}

/****************************************************************************/

MetaContainer *MXmlMetaService::parse (std::string const &path, MetaContainer *container) const
{
        Impl impl;
        FILE *fp;

        fp = fopen (path.c_str (), "r");

        if (!fp) {
                int errsv = errno;
                throw XmlMetaServiceException ("MXmlMetaService::parse : could not open file. Message : " + std::string (strerror (errsv)));
        }

        mxmlSAXLoadFile (NULL, fp, MXML_TEXT_CALLBACK, saxHandler, &impl);

        fclose(fp);

        return container;
}

/****************************************************************************/

void Impl::onOpenElement (mxml_node_t *node)
{
        char const *name = mxmlGetElement (node);

        if (!strcmp (name, "beans")) {
        }
        else if (!strcmp (name, "bean")) {
                onOpenBean (node);
        }
        else if (!strcmp (name, "list")) {
//                onOpenList (node);
        }
        else if (!strcmp (name, "map")) {

        }
        else if (!strcmp (name, "import")) {

        }
        else if (!strcmp (name, "alias")) {

        }
        else if (!strcmp (name, "property")) {
                onOpenProperty (node);
        }
        else if (!strcmp (name, "constructor-arg") || !strcmp (name, "carg")) {

        }
//        else if (!strcmp (name, "")) {
//
//        }
        else {
                throw XmlMetaServiceException ("Impl::onOpenElement : unknow tag name : " + std::string (name));
        }

}

/****************************************************************************/

void Impl::onCloseElement (mxml_node_t *node)
{

}

/****************************************************************************/

void Impl::fillMetaArguments (mxml_node_t *node, IMeta *meta)
{
        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "id"))) {
                meta->setId (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "class"))) {
                meta->setClass (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "parent"))) {
                meta->setParent (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "singleton"))) {
                meta->setScope ((!strcmp (argVal, "true")) ? (IMeta::SINGLETON) : (IMeta::PROTOTYPE));
        }

        if ((argVal = mxmlElementGetAttr (node, "scope"))) {
                if (!strcmp (argVal, "singleton")) {
                        meta->setScope (IMeta::SINGLETON);
                }
                else if (!strcmp (argVal, "prototype")) {
                        meta->setScope (IMeta::PROTOTYPE);
                }
                else if (!strcmp (argVal, "bean")) {
                        meta->setScope (IMeta::BEAN);
                }
                else {
                        throw XmlMetaServiceException ("Impl::onOpenBean : wrong value for argument 'scope'. Correct values are : 'singleton', 'prototype' and 'bean'. You provided : " + std::string (argVal));
                }
        }

        if ((argVal = mxmlElementGetAttr (node, "lazy-init"))) {
                meta->setLazyInit (!strcmp (argVal, "true"));
        }

        if ((argVal = mxmlElementGetAttr (node, "init-method"))) {
                meta->setInitMethod (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "editor"))) {
                meta->setEditor (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "factory"))) {
                meta->setFactory (argVal);
        }
}

/****************************************************************************/

void Impl::onOpenBean (mxml_node_t *node)
{
        MappedMeta *meta = pushNewMappedMeta ();
        fillMetaArguments (node, meta);
}

/****************************************************************************/

void Impl::onOpenProperty (mxml_node_t *node)
{
        MapElem *elem = pushNewMapElem ();

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "value"))) {
                meta->setId (argVal);
        }

}

/****************************************************************************/

MappedMeta *Impl::pushNewMappedMeta ()
{
        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();
        metaStack.push (meta);
        return meta.get ();
}

/****************************************************************************/

IndexedMeta *Impl::pushNewIndexedMeta ()
{
        Ptr <IndexedMeta> meta = boost::make_shared <IndexedMeta> ();
        metaStack.push (meta);
        return meta.get ();
}

/****************************************************************************/

MapElem *Impl::pushNewMapElem ()
{
        Ptr <MapElem> e = MapElem::create ();
        metaElemStack.push (e);
        return e.get ();
}

/****************************************************************************/

ListElem *Impl::pushNewListElem ()
{
        Ptr <ListElem> e = ListElem::create ();
        metaElemStack.push (e);
        return e.get ();
}

} /* namespace Container */
