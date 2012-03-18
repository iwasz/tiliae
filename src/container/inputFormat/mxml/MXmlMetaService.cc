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
#include "../../../core/Pointer.h"
#include "../../common/Exceptions.h"
#include "../../metaStructure/model/MetaContainer.h"
#include "../../metaStructure/model/meta/MappedMeta.h"
#include "../../metaStructure/model/meta/IndexedMeta.h"
#include "../../metaStructure/model/data/RefData.h"
#include "../../metaStructure/model/data/ValueData.h"
#include "../../metaStructure/model/data/NullData.h"

namespace Container {

/**
 * Tu się wykonuje cały algorytm. Ta implementacja jest ukryta przed użytkownikiem. Taki PIMPL.
 */
class Impl {
public:

        Impl (MetaContainer *c) : metaContainer (c) {}

        void onOpenElement (mxml_node_t *node);
        void onCloseElement (mxml_node_t *node);

        void onOpenBean (mxml_node_t *node);
        void onCloseBean (mxml_node_t *node);

        void onOpenList (mxml_node_t *node);
        void onCloseList (mxml_node_t *node);

        void onOpenMap (mxml_node_t *node);
        void onCloseMap (mxml_node_t *node);

        void onOpenProperty (mxml_node_t *node);
        void onCloseProperty (mxml_node_t *node);

        void onOpenCArg (mxml_node_t *node);
        void onCloseCArg (mxml_node_t *node);

        void onOpenEntry (mxml_node_t *node);
        void onCloseEntry (mxml_node_t *node);

        void onOpenValue (mxml_node_t *node);
        void onCloseValue (mxml_node_t *node);

        void onOpenRef (mxml_node_t *node);
        void onOpenNull (mxml_node_t *node);
        void onOpenKey (mxml_node_t *node);

        void onData (mxml_node_t *node);

/****************************************************************************/

        MappedMeta *pushNewMappedMeta ();
        IndexedMeta *pushNewIndexedMeta ();
        void fillMetaArguments (mxml_node_t *node, IMeta *meta);
        void popCurrentMeta ();
        Ptr <AbstractMeta> getCurrentMeta () const;
        Ptr <MappedMeta> getCurrentMappedMeta () const;
        Ptr <IndexedMeta> getCurrentIndexedMeta () const;

        Ptr <MapElem> pushNewMapElem ();
        void popCurrentMapElem ();
        Ptr <ListElem> pushNewListElem ();
        void popCurrentListElem ();

        Ptr <AbstractElem> getCurrentElem () const;
        Ptr <MapElem> getCurrentMapElem () const;
        Ptr <ListElem> getCurrentListElem () const;

        std::string const &getCurrentTag () const { return tagStack.back (); }
        std::string const &getPrevTag () const
        {
                if (tagStack.size () < 2) {
                        throw XmlMetaServiceException ("Impl::getPrevTag : no prev tag!");
                }

                return *(tagStack.end () - 2);
        }

private:

        Core::StringVector tagStack;

        /// Pamięć podręczna obiektów Meta (odzwierciadlających beany, mapy listy).
        MetaStack metaStack;

        /// Pamięć podręczna obiektów MetaElem (odzwierciadlających property beanów, elementy list i map).
        MetaElemStack metaElemStack;

        // Ten konteneru zuzupełniamy.
        MetaContainer *metaContainer;
};

/****************************************************************************/

void saxHandler (mxml_node_t *node, mxml_sax_event_t event, void *data)
{
        Impl *impl = static_cast <Impl *> (data);

        mxml_type_t type = mxmlGetType (node);

        switch (event) {
        case MXML_SAX_CDATA:
        case MXML_SAX_DATA:
                impl->onData (node);
                break;

        case MXML_SAX_ELEMENT_CLOSE:

                if (type == MXML_ELEMENT) {
                        impl->onCloseElement (node);
                }
                break;

        case MXML_SAX_ELEMENT_OPEN:

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
        Impl impl (container);
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

        tagStack.push_back (name);

        if (!strcmp (name, "bean")) {
                onOpenBean (node);
        }
        else if (!strcmp (name, "property")) {
                onOpenProperty (node);
        }
        else if (!strcmp (name, "list")) {
                onOpenList (node);
        }
        else if (!strcmp (name, "map")) {
                onOpenMap (node);
        }
        else if (!strcmp (name, "import")) {

        }
        else if (!strcmp (name, "alias")) {

        }
        else if (!strcmp (name, "constructor-arg") || !strcmp (name, "carg")) {
                onOpenCArg (node);
        }
        else if (!strcmp (name, "ref")) {
                onOpenRef (node);
        }
        else if (!strcmp (name, "value")) {
                onOpenValue (node);
        }
        else if (!strcmp (name, "null")) {
                onOpenNull (node);
        }
        else if (!strcmp (name, "entry")) {
                onOpenEntry (node);
        }
        else if (!strcmp (name, "key")) {
                onOpenKey (node);
        }
        else if (!strcmp (name, "beans")) {
        }
        else {
                throw XmlMetaServiceException ("Impl::onOpenElement : unknow tag name : " + std::string (name));
        }
}

/****************************************************************************/

void Impl::onCloseElement (mxml_node_t *node)
{
        char const *name = mxmlGetElement (node);

        if (!strcmp (name, "bean")) {
                onCloseBean (node);
        }
        else if (!strcmp (name, "property")) {
                onCloseProperty (node);
        }
        else if (!strcmp (name, "map")) {
                onCloseMap (node);
        }
        else if (!strcmp (name, "entry")) {
                onCloseEntry (node);
        }
        else if (!strcmp (name, "list")) {
                onCloseList (node);
        }
        else if (!strcmp (name, "value")) {
                onCloseValue (node);
        }

        tagStack.pop_back ();
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

void Impl::onCloseBean (mxml_node_t *node)
{
        popCurrentMeta ();
}

/****************************************************************************/

void Impl::onOpenProperty (mxml_node_t *node)
{
        Ptr <MapElem> elem = pushNewMapElem ();

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "value"))) {
                elem->setData (ValueData::create (argVal));
        }

        if ((argVal = mxmlElementGetAttr (node, "ref"))) {
                elem->setData (RefData::create (argVal));
        }

        if ((argVal = mxmlElementGetAttr (node, "name"))) {
                elem->setKey (argVal);
        }
}

/****************************************************************************/

void Impl::onCloseProperty (mxml_node_t *node)
{
        popCurrentMapElem ();
}

/****************************************************************************/

void Impl::onOpenList (mxml_node_t *node)
{
        IndexedMeta *meta = pushNewIndexedMeta ();
        fillMetaArguments (node, meta);
}

/****************************************************************************/

void Impl::onCloseList (mxml_node_t *node)
{
        popCurrentMeta ();
}

/****************************************************************************/

void Impl::onOpenMap (mxml_node_t *node)
{
        MappedMeta *meta = pushNewMappedMeta ();
        fillMetaArguments (node, meta);
}

/****************************************************************************/

void Impl::onCloseMap (mxml_node_t *node)
{
        popCurrentMeta ();
}

/****************************************************************************/

void Impl::onOpenCArg (mxml_node_t *node)
{

}

/****************************************************************************/

void Impl::onCloseCArg (mxml_node_t *node)
{

}

/****************************************************************************/

void Impl::onOpenEntry (mxml_node_t *node)
{
        Ptr <MapElem> elem = pushNewMapElem ();

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "value"))) {
                elem->setData (ValueData::create (argVal));
        }

        if ((argVal = mxmlElementGetAttr (node, "ref"))) {
                elem->setData (RefData::create (argVal));
        }

        if ((argVal = mxmlElementGetAttr (node, "key"))) {
                elem->setKey (argVal);
        }
}

/****************************************************************************/

void Impl::onCloseEntry (mxml_node_t *node)
{
        popCurrentMapElem ();
}

/****************************************************************************/

void Impl::onOpenRef (mxml_node_t *node)
{

}

/****************************************************************************/

void Impl::onOpenValue (mxml_node_t *node)
{
        Ptr <AbstractElem> elem;

        if (getPrevTag () == "list") {
                elem = pushNewListElem ();
        }
        else {
                elem = getCurrentElem ();
        }

        Ptr <ValueData> valueData = ValueData::create ();
        elem->setData (valueData);

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "type"))) {
                valueData->setType (argVal);
        }
}

/****************************************************************************/

void Impl::onCloseValue (mxml_node_t *node)
{
        if (getPrevTag () == "list") {
                popCurrentListElem ();
        }
}

/****************************************************************************/

void Impl::onOpenNull (mxml_node_t *node)
{
        Ptr <AbstractElem> elem;

        if (getPrevTag () == "list") {
                Ptr <IndexedMeta> meta = getCurrentIndexedMeta ();
                Ptr <ListElem> elem = ListElem::create (NullData::create ());
                meta->addField (elem);
        }
        else {
                elem = getCurrentElem ();
                elem->setData (NullData::create ());
        }
}

/****************************************************************************/

void Impl::onOpenKey (mxml_node_t *node)
{

}

/****************************************************************************/

void Impl::onData (mxml_node_t *node)
{
        Ptr <AbstractElem> elem = getCurrentElem ();

        if (!elem) {
                return;
        }

        mxml_type_t type = mxmlGetType (node);
        char const *text = NULL;
        int whitespace;

        // Pobranie danych.
        switch (type) {
        case MXML_TEXT:
                text = mxmlGetText (node, &whitespace);
                break;

        case MXML_OPAQUE:
                text = mxmlGetOpaque (node);
                break;

        default:
                break;
        }

        // Obsługa konkretnych tagów.
        if (getCurrentTag () == "value") {

                // Szczególny przypadek, gdy jesteśmy w <key>
                if (getPrevTag () == "key") {
                        Ptr <MapElem> mE = boost::dynamic_pointer_cast <MapElem> (elem);

                        if (!elem) {
                                throw XmlMetaServiceException ("Impl::onData : Can't cast to MapElem.");
                        }

                        mE->setKey (text);
                }


                Ptr<IData> data = elem->getData ();
                Ptr<ValueData> valueData;

                if (!(valueData = boost::dynamic_pointer_cast <ValueData> (data))) {
                     return;
                }

                valueData->setData (text);
        }
        else if (getCurrentTag () == "key") {
                Ptr <MapElem> mE = boost::dynamic_pointer_cast <MapElem> (elem);

                if (!elem) {
                        throw XmlMetaServiceException ("Impl::onData : Can't cast to MapElem.");
                }

                mE->setKey (text);
        }
}

/*##########################################################################*/

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

Ptr <MapElem> Impl::pushNewMapElem ()
{
        Ptr <MapElem> e = MapElem::create ();
        metaElemStack.push (e);
        return e;
}

/****************************************************************************/

Ptr <ListElem> Impl::pushNewListElem ()
{
        Ptr <ListElem> e = ListElem::create ();
        metaElemStack.push (e);
        return e;
}

/****************************************************************************/

void Impl::popCurrentMapElem ()
{
        Ptr <IndexedMeta> meta = getCurrentIndexedMeta ();
        Ptr <ListElem> elem = getCurrentListElem ();
        metaElemStack.pop ();
        meta->addField (elem);
}

/****************************************************************************/

void Impl::popCurrentListElem ()
{
        Ptr <IndexedMeta> meta = getCurrentIndexedMeta ();
        Ptr <ListElem> elem = getCurrentListElem ();
        metaElemStack.pop ();
        meta->addField (elem);
}

/****************************************************************************/

Ptr <AbstractMeta> Impl::getCurrentMeta () const
{
        if (!metaStack.size ()) {
                throw XmlMetaServiceException ("Impl::getCurrentMeta : metaStack is empty.");
        }

        Ptr <IMeta> meta = metaStack.top ();

        if (!meta) {
                throw XmlMetaServiceException ("Impl::getCurrentMeta : current meta is null.");
        }

        return boost::static_pointer_cast <AbstractMeta> (meta);
}

/****************************************************************************/

Ptr <MappedMeta> Impl::getCurrentMappedMeta () const
{
        Ptr <MappedMeta> meta = boost::dynamic_pointer_cast <MappedMeta> (getCurrentMeta ());

        if (!meta) {
                throw XmlMetaServiceException ("Impl::getCurrentMappedMeta : Can't cast to MappedMeta.");
        }

        return meta;
}

/****************************************************************************/

Ptr <IndexedMeta> Impl::getCurrentIndexedMeta () const
{
        Ptr <IndexedMeta> meta = boost::dynamic_pointer_cast <IndexedMeta> (getCurrentMeta ());

        if (!meta) {
                throw XmlMetaServiceException ("Impl::getCurrentIndexedMeta : Can't cast to IndexedMeta.");
        }

        return meta;
}

/****************************************************************************/

Ptr <AbstractElem> Impl::getCurrentElem () const
{
        if (metaElemStack.empty ()) {
                return Ptr <AbstractElem> ();
        }

        Ptr <IElem> elem = metaElemStack.top ();

        if (!elem) {
                throw XmlMetaServiceException ("Impl::getCurrentElem : Current metaElem is null.");
        }

        return boost::static_pointer_cast <AbstractElem> (elem);
}

/****************************************************************************/

Ptr <MapElem> Impl::getCurrentMapElem () const
{
        Ptr <AbstractElem> elem = getCurrentElem ();

        if (!elem) {
                return Ptr <MapElem> ();
        }

        Ptr <MapElem> m = boost::dynamic_pointer_cast <MapElem> (elem);

        if (!m) {
                throw XmlMetaServiceException ("Impl::getCurrentMapElem : Can't cast to MapElem.");
        }

        return m;
}

/****************************************************************************/

Ptr <ListElem> Impl::getCurrentListElem () const
{
        Ptr <AbstractElem> elem = getCurrentElem ();

        if (!elem) {
                return Ptr <ListElem> ();
        }

        Ptr <ListElem> m = boost::dynamic_pointer_cast <ListElem> (elem);

        if (!m) {
                throw XmlMetaServiceException ("Impl::getCurrentListElem : Can't cast to ListElem.");
        }

        return m;
}

/****************************************************************************/

void Impl::popCurrentMeta ()
{
        // 1. Pobierz
        Ptr <IMeta> meta = getCurrentMeta ();

        // 2. Zdejmij.
        metaStack.pop ();

#if 0
        std::cerr << "[" << meta->getId () << "], " << meta->getScope () << std::endl;
#endif

        // 3. Umiesc ten gotowy meta w kontenerze lub w outermeta (jeśli zagnieżdżenie).
        if (!metaStack.empty ()) {
                Ptr <IMeta> outer = getCurrentMeta ();
                outer->addInnerMeta (meta);
        }
        else {
                metaContainer->add (meta);
        }
}

} /* namespace Container */
