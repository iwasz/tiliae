/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <mxml.h>
#include <iostream>
#include <queue>
#include <boost/lexical_cast.hpp>
#include "MXmlMetaService.h"
#include "Pointer.h"
#include "common/Exceptions.h"
#include "metaStructure/MetaStructure.h"

#ifdef ANDROID
#include <android/asset_manager.h>
#include <android/log.h>
#endif

namespace Container {

namespace {

/**
 * Tu się wykonuje cały algorytm. Ta implementacja jest ukryta przed użytkownikiem. Taki PIMPL.
 */
struct Impl {

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

        void onOpenEntry (mxml_node_t *node);

        void onOpenCArg (mxml_node_t *node);
        void onCloseCArg (mxml_node_t *node);

        void onOpenValue (mxml_node_t *node);
        void onCloseValue (mxml_node_t *node);

        void onOpenRef (mxml_node_t *node);
        void onCloseRef (mxml_node_t *node);

        void onOpenNull (mxml_node_t *node);
        void onOpenImport (mxml_node_t *node);

        void onData (mxml_node_t *node);

/****************************************************************************/

        MetaObject *pushNewMeta ();
        void fillMetaArguments (mxml_node_t *node, MetaObject *meta);
        MetaObject *popCurrentMeta ();
        MetaObject *getCurrentMeta () const;

        DataKey &pushNewDataKey ();
        void popCurrentDataKeyAddToMapped ();
        void popCurrentDataKeyAddToIndexed ();
        DataKey *getCurrentDataKey ();

        std::string const &getCurrentTag () const { return tagStack.back (); }
        std::string const &getPrevTag () const
        {
                if (tagStack.size () < 2) {
                        throw XmlMetaServiceException ("Impl::getPrevTag : no prev tag!");
                }

                return *(tagStack.end () - 2);
        }


        std::string generateId (MetaObject *m) const { return m->getClass() + "_" + boost::lexical_cast <std::string> (singetinNumber++); }

        /// Tu odkładają się nazwy kolejnych (zagnieżdżonych tagów).
        Core::StringVector tagStack;

        /// Pamięć podręczna obiektów Meta (odzwierciadlających beany, mapy listy).
        MetaStack metaStack;

        /// Pamięć podręczna obiektów DataKey (odzwierciadlających property beanów, elementy list i map).
        DataKeyStack dataKeyStack;

        // Ten konteneru zuzupełniamy.
        MetaContainer *metaContainer;

        /// Paths to files to import.
        std::queue <std::string> imports;

        /// Do automatycznego generowania ID.
        static int singetinNumber;
};

int Impl::singetinNumber = 0;

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
        else if (!strcmp (name, "entry")) {
                onOpenEntry (node);
        }
        else if (!strcmp (name, "list")) {
                onOpenList (node);
        }
        else if (!strcmp (name, "map")) {
                onOpenMap (node);
        }
        else if (!strcmp (name, "import")) {
                onOpenImport (node);
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
        else if (!strcmp (name, "beans") || !strcmp (name, "key")) {
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
        else if (!strcmp (name, "property") || !strcmp (name, "entry")) {
                // Entry i property działa tak samo.
                onCloseProperty (node);
        }
        else if (!strcmp (name, "map")) {
                onCloseMap (node);
        }
        else if (!strcmp (name, "list")) {
                onCloseList (node);
        }
        else if (!strcmp (name, "value")) {
                onCloseValue (node);
        }
        else if (!strcmp (name, "ref")) {
                onCloseRef (node);
        }
        else if (!strcmp (name, "constructor-arg") || !strcmp (name, "carg")) {
                onCloseCArg (node);
        }

        tagStack.pop_back ();
}

/****************************************************************************/

void Impl::fillMetaArguments (mxml_node_t *node, MetaObject *meta)
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
                meta->setScope ((!strcmp (argVal, "true")) ? (MetaObject::SINGLETON) : (MetaObject::PROTOTYPE));
        }

        if ((argVal = mxmlElementGetAttr (node, "scope"))) {
                if (!strcmp (argVal, "singleton")) {
                        meta->setScope (MetaObject::SINGLETON);
                }
                else if (!strcmp (argVal, "prototype")) {
                        meta->setScope (MetaObject::PROTOTYPE);
                }
                else if (!strcmp (argVal, "bean")) {
                        meta->setScope (MetaObject::BEAN);
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

        if ((argVal = mxmlElementGetAttr (node, "abstract"))) {
                meta->setAbstract (!strcmp (argVal, "true"));
        }
}

/****************************************************************************/

void Impl::onOpenBean (mxml_node_t *node)
{
        MetaObject *meta = pushNewMeta ();
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
        DataKey &elem = pushNewDataKey ();

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "value"))) {
                elem.data = new ValueData (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "ref"))) {
                elem.data = new RefData (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "name"))) {
                elem.key = argVal;
        }
}

/****************************************************************************/

void Impl::onOpenEntry (mxml_node_t *node)
{
        DataKey &elem = pushNewDataKey ();

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "value"))) {
                elem.data = new ValueData (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "ref"))) {
                elem.data = new RefData (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "key"))) {
                elem.key = argVal;
        }
}

/****************************************************************************/

void Impl::onCloseProperty (mxml_node_t *node)
{
        popCurrentDataKeyAddToMapped ();
}

/****************************************************************************/

void Impl::onOpenList (mxml_node_t *node)
{
        MetaObject *meta = pushNewMeta ();
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
        MetaObject *meta = pushNewMeta ();
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
        DataKey &elem = pushNewDataKey ();

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "value"))) {
                elem.data = new ValueData (argVal);
        }

        if ((argVal = mxmlElementGetAttr (node, "ref"))) {
                elem.data = new RefData (argVal);
        }
}

/****************************************************************************/

void Impl::onCloseCArg (mxml_node_t *node)
{
        MetaObject *meta = getCurrentMeta ();
        DataKey *elem = getCurrentDataKey ();
        dataKeyStack.pop_back ();
        meta->addConstructorArg (elem->data);
}

/****************************************************************************/

void Impl::onOpenRef (mxml_node_t *node)
{
        RefData *refData = new RefData ();

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "bean"))) {
                refData->setData (argVal);
        }

        if (getPrevTag () == "list") {
                MetaObject *meta = getCurrentMeta ();
                meta->addListField (refData);
        }
        else {
                DataKey *elem = getCurrentDataKey ();
                elem->data = refData;
        }
}

/****************************************************************************/

void Impl::onCloseRef (mxml_node_t *node)
{

}

/****************************************************************************/

void Impl::onOpenValue (mxml_node_t *node)
{
        DataKey *elem = NULL;

        if (getPrevTag () == "list") {
                elem = &pushNewDataKey ();
        }
        else {
                elem = getCurrentDataKey ();
        }

        ValueData *valueData = new ValueData ();
        elem->data = valueData;

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "type"))) {
                valueData->setType (argVal);
        }
}

/****************************************************************************/

void Impl::onCloseValue (mxml_node_t *node)
{
        if (getPrevTag () == "list") {
                popCurrentDataKeyAddToIndexed ();
        }
}

/****************************************************************************/

void Impl::onOpenNull (mxml_node_t *node)
{
        if (getPrevTag () == "list") {
                MetaObject *meta = getCurrentMeta ();
                meta->addListField (new NullData ());
        }
        else {
                DataKey *elem = getCurrentDataKey ();
                elem->data = new NullData ();
        }
}

/****************************************************************************/

void Impl::onOpenImport (mxml_node_t *node)
{
        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "resource"))) {
                imports.push (argVal);
        }
}

/****************************************************************************/

void Impl::onData (mxml_node_t *node)
{
        DataKey *elem = getCurrentDataKey ();

        if (!elem) {
                return;
        }

        mxml_type_t type = mxmlGetType (node);
        char const *text = NULL;
        int whitespace;
        std::string buffer;

        // Pobranie danych.
        switch (type) {
        case MXML_TEXT:
                text = mxmlGetText (node, &whitespace);
                break;

        case MXML_OPAQUE:
                text = mxmlGetOpaque (node);
                break;

        case MXML_ELEMENT:
        {
                // CDATA
                text = mxmlGetElement (node);
                char const *start = NULL;
                char const *end = NULL;
                char const *end2 = NULL;

                char c, cnt = 0;
                while ((c = *text++)) {
                        if (c == '[') {
                                ++cnt;
                        }

                        if (cnt == 2) {
                                start = text;
                                cnt = 0;
                        }

                        if (c == ']') {
                                end2 = end - 1;
                                end = text;
                        }
                }

                std::copy (start, end2, std::back_inserter (buffer));
                text = buffer.c_str ();
        }
                break;

        default:
                break;
        }

        // Obsługa konkretnych tagów.
        if (getCurrentTag () == "value") {

                // Szczególny przypadek, gdy jesteśmy w <key>
                if (getPrevTag () == "key") {
                        elem->key = text;
                }


                ValueData *valueData;

                if (!(valueData = dynamic_cast <ValueData *> (elem->data))) {
                     return;
                }

                valueData->setData (text);
        }
        else if (getCurrentTag () == "key") {
                elem->key = text;
        }
}

/*##########################################################################*/

MetaObject *Impl::pushNewMeta ()
{
        MetaObject *meta = new MetaObject ();
        metaStack.push (meta);
        return meta;
}

/****************************************************************************/

DataKey &Impl::pushNewDataKey ()
{
        dataKeyStack.push_back (DataKey ());
        return dataKeyStack.back ();
}

/****************************************************************************/

void Impl::popCurrentDataKeyAddToMapped ()
{
        MetaObject *meta =  getCurrentMeta ();
        DataKey *dk = getCurrentDataKey ();
        meta->addMapField (*dk);
        dataKeyStack.pop_back ();
}

/****************************************************************************/

void Impl::popCurrentDataKeyAddToIndexed ()
{
        MetaObject *meta =  getCurrentMeta ();
        DataKey *dk = getCurrentDataKey ();
        meta->addListField (dk->data);
        dataKeyStack.pop_back ();
}

/****************************************************************************/

MetaObject *Impl::getCurrentMeta () const
{
        if (!metaStack.size ()) {
                throw XmlMetaServiceException ("Impl::getCurrentMeta : metaStack is empty.");
        }

        MetaObject *meta = metaStack.top ();

        if (!meta) {
                throw XmlMetaServiceException ("Impl::getCurrentMeta : current meta is null.");
        }

        return static_cast <MetaObject *> (meta);
}

/****************************************************************************/

DataKey *Impl::getCurrentDataKey ()
{
        if (dataKeyStack.empty ()) {
                return NULL;
        }

        return &dataKeyStack.back ();
}

/****************************************************************************/

MetaObject *Impl::popCurrentMeta ()
{
        // 1. Pobierz
        MetaObject *meta = getCurrentMeta ();

        // 2. Zdejmij.
        metaStack.pop ();

#if 0
        std::cerr << "[" << meta->getId () << "], " << meta->getScope () << std::endl;
#endif

        // 3. Umiesc ten gotowy meta w kontenerze lub w outermeta (jeśli zagnieżdżenie).
        if (!metaStack.empty ()) {
                MetaObject *outerMeta = getCurrentMeta ();

                std::string id;

                if ((id = meta->getId ()).empty ()) {
                        // Generujemy też referencję do zagnieżdzonego beana.
                        id = generateId (meta);
                        meta->setId (id);
                }

                outerMeta->addInnerMeta (meta);

                if (getPrevTag () == "constructor-arg" || getPrevTag () == "carg") {
                        DataKey *dk = getCurrentDataKey ();
                        dk->data = new RefData (id);
                        return meta;
                }

                DataKey *dk = getCurrentDataKey ();

                if (dk) {
                        dk->data = new RefData (id);
                }
                else {
                        outerMeta->addListField (new RefData (id));
                }
        }
        else {
                metaContainer->add (meta);
        }

        return meta;
}

}

/****************************************************************************/

Ptr <MetaContainer> MXmlMetaService::parseFile (std::string const &path, Ptr <MetaContainer> container)
{
        if (!container) {
                container = boost::make_shared <MetaContainer> ();
        }

        Impl impl (container.get ());
        FILE *fp;

        fp = fopen (path.c_str (), "r");

        if (!fp) {
                int errsv = errno;
                throw XmlMetaServiceException ("MXmlMetaService::parse : could not open file. Message : " + std::string (strerror (errsv)) + ". Path : [" + path + "]");
        }

        mxmlSAXLoadFile (NULL, fp, MXML_TEXT_CALLBACK, saxHandler, &impl);

        fclose(fp);

        while (!impl.imports.empty ()) {
                std::string path = impl.imports.front ();
                impl.imports.pop ();
                parseFile (path, container);
        }

        return container;
}

/****************************************************************************/

#ifdef ANDROID
Ptr <MetaContainer> MXmlMetaService::parseAndroidAsset (AAssetManager *assetManager, std::string const &path, Ptr <MetaContainer> container)
{
        if (!container) {
                container = boost::make_shared <MetaContainer> ();
        }

        Impl impl (container.get ());

        AAsset *asset = AAssetManager_open (assetManager, path.c_str (), AASSET_MODE_UNKNOWN);

        if (!asset) {
                throw XmlMetaServiceException ("MXmlMetaService::parseAndroidAsset : could not open resource. Path : [" + path + "]");
        }

        int bytesRead;
        char buffer[BUFSIZ];
        std::string xml;

        while ((bytesRead = AAsset_read (asset, buffer, BUFSIZ - 1))) {

                if (bytesRead < 0) {
                        throw XmlMetaServiceException ("MXmlMetaService::parseAndroidAsset : could not read from resource. Path : [" + path + "]");
                }

                buffer[bytesRead] = '\0';

#if 0
        __android_log_print(ANDROID_LOG_INFO, "bajka", "bytes read...");
#endif

                xml += buffer;
        }

        AAsset_close (asset);

#if 0
        __android_log_print(ANDROID_LOG_INFO, "bajka", xml.c_str());
#endif

        mxmlSAXLoadString (NULL, xml.c_str (), MXML_TEXT_CALLBACK, saxHandler, &impl);

        while (!impl.imports.empty ()) {
                std::string path = impl.imports.front ();
                impl.imports.pop ();
                parseAndroidAsset (assetManager, path, container);
        }

        return container;
}
#endif

} /* namespace Container */
