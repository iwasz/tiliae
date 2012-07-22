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
#include "CompactMetaService.h"
#include "Pointer.h"
#include "common/Exceptions.h"
#include "metaStructure/MetaStructure.h"
#include "../../../reflection/Manager.h"

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

//        void onOpenList (mxml_node_t *node);
//        void onCloseList (mxml_node_t *node);
//
//        void onOpenMap (mxml_node_t *node);
//        void onCloseMap (mxml_node_t *node);

//        void onOpenSet (mxml_node_t *node);
//        void onCloseSet (mxml_node_t *node);

        void onOpenEntry (mxml_node_t *node);

        void onOpenCArg (mxml_node_t *node);
        void onCloseCArg (mxml_node_t *node);

        void onOpenValue (mxml_node_t *node);
        void onCloseValue (mxml_node_t *node);

        void onOpenRef (mxml_node_t *node);
//        void onCloseRef (mxml_node_t *node);

        void onOpenNull (mxml_node_t *node);
        void onOpenImport (mxml_node_t *node);

        void onData (mxml_node_t *node);

/****************************************************************************/

        MetaObject *pushNewMeta ();
//        IndexedMeta *pushNewIndexedMeta ();
        void fillMetaArguments (mxml_node_t *node, MetaObject *meta);
        MetaObject *popCurrentMeta ();
        MetaObject *getCurrentMeta () const;
//        MetaObject *getCurrentMappedMeta () const;
//        IndexedMeta *getCurrentIndexedMeta () const;

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

        /**
         * Sprawdza, czy podana nazwa jest nazwąklasy odnajdywalną w reflekcji, czy nie.
         */
        bool checkIfClass (std::string const &name) const;

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

//        if (!strcmp (name, "bean")) {
//                onOpenBean (node);
//        }
//        if (!strcmp (name, "set")) {
//                onOpenSet (node);
//        }
//        else if (!strcmp (name, "entry")) {
//                onOpenEntry (node);
//        }
//        else if (!strcmp (name, "list")) {
//                onOpenList (node);
//        }
//        else if (!strcmp (name, "map")) {
//                onOpenMap (node);
//        }
        if (!strcmp (name, "import")) {
                onOpenImport (node);
        }
//        else if (!strcmp (name, "alias")) {
//
//        }
        else if (!strcmp (name, "carg")) {
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
                onOpenBean (node);
        }
}

/****************************************************************************/

void Impl::onCloseElement (mxml_node_t *node)
{
        char const *name = mxmlGetElement (node);

//        if (!strcmp (name, "set")) {
//                onCloseSet (node);
//        }
//        else if (!strcmp (name, "map")) {
//                onCloseMap (node);
//        }
//        else if (!strcmp (name, "list")) {
//                onCloseList (node);
//        }
        if (!strcmp (name, "value")) {
                onCloseValue (node);
        }
//        else if (!strcmp (name, "ref")) {
//                onCloseRef (node);
//        }
        else if (!strcmp (name, "carg")) {
                onCloseCArg (node);
        }
        else if (!strcmp (name, "beans") || !strcmp (name, "null") || !strcmp (name, "ref")) {
                // Ignore
        }
        else {
                onCloseBean (node);
        }

        tagStack.pop_back ();
}

/****************************************************************************/

void Impl::fillMetaArguments (mxml_node_t *node, MetaObject *meta)
{
        std::string name = mxmlGetElement (node);

        if (checkIfClass (name)) {
                meta->setClass (name);
        }
        else {
                meta->setParent (name);
        }

        mxml_attr_t *attr = node->value.element.attrs;
        for (int i = 0; i < node->value.element.num_attrs; ++i) {
                mxml_attr_t *cur = attr + i;
                std::string name = cur->name;
                std::string value = cur->value;

#if 0
                std::cerr << name << ", " << value << std::endl;
#endif

                // Standardowe atrybuty:
                if (name == "id") {
                        meta->setId (value);
                }
                else if (name == "singleton") {
                        meta->setScope ((value == "true") ? (MetaObject::SINGLETON) : (MetaObject::PROTOTYPE));
                }
                else if (name == "scope") {
                        if (value == "singleton") {
                                meta->setScope (MetaObject::SINGLETON);
                        }
                        else if (value == "prototype") {
                                meta->setScope (MetaObject::PROTOTYPE);
                        }
                        else if (value == "bean") {
                                meta->setScope (MetaObject::BEAN);
                        }
                        else {
                                throw XmlMetaServiceException ("Impl::onOpenBean : wrong value for argument 'scope'. Correct values are : 'singleton', 'prototype' and 'bean'. You provided : " + std::string (value));
                        }
                }
                else if (name == "lazy-init") {
                        meta->setLazyInit (value == "true");
                }
                else if (name == "init-method") {
                        meta->setInitMethod (value);
                }
                else if (name == "editor") {
                        meta->setEditor (value);
                }
                else if (name == "factory") {
                        meta->setFactory (value);
                }
                else if (name == "abstract") {
                        meta->setAbstract (value == "true");
                }
                // Property
                else {
                        DataKey dk;
                        dk.key = name;

                        if (!value.empty () && value[0] == '@') {
                                dk.data = new RefData (value.substr (1));
                        }
                        else {
                                dk.data = new ValueData (value);
                        }

                        MetaObject *meta =  getCurrentMeta ();
                        meta->addMapField (dk);
                }
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
//
//void Impl::onOpenSet (mxml_node_t *node)
//{
//        mxml_attr_t *attr = node->value.element.attrs;
//        for (int i = 0; i < node->value.element.num_attrs; ++i) {
//                mxml_attr_t *cur = attr + i;
//                std::string value = cur->value;
//
//                DataKey dk;
//                dk.key = cur->name;
//
//                if (!value.empty () && value[0] == '@') {
//                        dk.data = new RefData (value);
//                }
//                else {
//                        dk.data = new ValueData (value);
//                }
//
//                MetaObject *meta =  getCurrentMeta ();
//                meta->addMapField (dk);
//        }
//}

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

///****************************************************************************/
//
//void Impl::onOpenList (mxml_node_t *node)
//{
//        MetaObject *meta = pushNewMeta ();
//        fillMetaArguments (node, meta);
//}
//
///****************************************************************************/
//
//void Impl::onCloseList (mxml_node_t *node)
//{
//        popCurrentMeta ();
//}
//
///****************************************************************************/
//
//void Impl::onOpenMap (mxml_node_t *node)
//{
//        MetaObject *meta = pushNewMeta ();
//        fillMetaArguments (node, meta);
//}
//
///****************************************************************************/
//
//void Impl::onCloseMap (mxml_node_t *node)
//{
//        popCurrentMeta ();
//}

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
        DataKey elem;
        RefData *refData = new RefData ();
        elem.data = refData;
        char const *argVal = NULL;
        MetaObject *meta =  getCurrentMeta ();

        if ((argVal = mxmlElementGetAttr (node, "set-as"))) {
                elem.key = argVal;
        }
        // TODO to jakoś inaczej będzie obsługiwane
        else if ((argVal = mxmlElementGetAttr (node, "add-to"))) {
                elem.key = argVal;
        }

        if ((argVal = mxmlElementGetAttr (node, "bean"))) {
                refData->setData (argVal);
        }

        if (!elem.key.empty ()) {
                meta->addMapField (elem);
        }
        else {
                meta->addListField (refData);
        }
}

/****************************************************************************/

void Impl::onOpenValue (mxml_node_t *node)
{
        DataKey *elem = &pushNewDataKey ();

        ValueData *valueData = new ValueData ();
        elem->data = valueData;

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "set-as"))) {
                elem->key = argVal;
        }
        // TODO to jakoś inaczej będzie obsługiwane
        else if ((argVal = mxmlElementGetAttr (node, "add-to"))) {
                elem->key = argVal;
        }

        if ((argVal = mxmlElementGetAttr (node, "type"))) {
                valueData->setType (argVal);
        }
}

/****************************************************************************/

void Impl::onCloseValue (mxml_node_t *node)
{
        DataKey *dk = getCurrentDataKey ();

        // Jest klucz, czyli dodajemy do mapy, lub beana.
        if (!dk->key.empty ()) {
                popCurrentDataKeyAddToMapped ();
        }
        else {
                popCurrentDataKeyAddToIndexed ();
        }
}

/****************************************************************************/

void Impl::onOpenNull (mxml_node_t *node)
{
        DataKey *elem = &pushNewDataKey ();

        NullData *nullData = new NullData ();
        elem->data = nullData;

        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr (node, "set-as"))) {
                elem->key = argVal;
        }
        // TODO to jakoś inaczej będzie obsługiwane
        else if ((argVal = mxmlElementGetAttr (node, "add-to"))) {
                elem->key = argVal;
        }

        if (!elem->key.empty ()) {
                popCurrentDataKeyAddToMapped ();
        }
        else {
                popCurrentDataKeyAddToIndexed ();
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

//IndexedMeta *Impl::pushNewIndexedMeta ()
//{
//        IndexedMeta *meta = new IndexedMeta ();
//        metaStack.push (meta);
//        return meta;
//}

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

//MetaObject *Impl::getCurrentMappedMeta () const
//{
//        MetaObject *meta = dynamic_cast <MetaObject *> (getCurrentMeta ());
//
//        if (!meta) {
//                throw XmlMetaServiceException ("Impl::getCurrentMappedMeta : Can't cast to MappedMeta.");
//        }
//
//        return meta;
//}

/****************************************************************************/

//IndexedMeta *Impl::getCurrentIndexedMeta () const
//{
//        IndexedMeta *meta = dynamic_cast <IndexedMeta *> (getCurrentMeta ());
//
//        if (!meta) {
//                throw XmlMetaServiceException ("Impl::getCurrentIndexedMeta : Can't cast to IndexedMeta.");
//        }
//
//        return meta;
//}

/****************************************************************************/

DataKey *Impl::getCurrentDataKey ()
{
        if (dataKeyStack.empty ()) {
                return NULL;
        }

        return &dataKeyStack.back ();
}

/****************************************************************************/

//Ptr <MapElem> Impl::getCurrentMapElem () const
//{
//        Ptr <AbstractElem> elem = getCurrentDataKey ();
//
//        if (!elem) {
//                return Ptr <MapElem> ();
//        }
//
//        Ptr <MapElem> m = boost::dynamic_pointer_cast <MapElem> (elem);
//
//        if (!m) {
//                throw XmlMetaServiceException ("Impl::getCurrentMapElem : Can't cast to MapElem.");
//        }
//
//        return m;
//}
//
///****************************************************************************/
//
//Ptr <ListElem> Impl::getCurrentListElem () const
//{
//        Ptr <AbstractElem> elem = getCurrentDataKey ();
//
//        if (!elem) {
//                return Ptr <ListElem> ();
//        }
//
//        Ptr <ListElem> m = boost::dynamic_pointer_cast <ListElem> (elem);
//
//        if (!m) {
//                throw XmlMetaServiceException ("Impl::getCurrentListElem : Can't cast to ListElem.");
//        }
//
//        return m;
//}

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

                if (outerMeta->getType () == MetaObject::MAPPED) {
                        DataKey *dk = getCurrentDataKey ();
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

/****************************************************************************/

bool Impl::checkIfClass (std::string const &name) const
{
        return static_cast <bool> (Reflection::Manager::classForName (name));
}


} // namespace {

/****************************************************************************/

Ptr <MetaContainer> CompactMetaService::parseFile (std::string const &path, Ptr <MetaContainer> container)
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

} /* namespace Container */
