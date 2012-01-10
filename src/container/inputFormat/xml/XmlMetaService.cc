/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "XmlMetaService.h"
#include "metaStructure/model/MetaStructure.h"
#include "context/MachineContext.h"
#include "common/Exceptions.h"
#include "inputFormat/xml/XmlMetaServiceFactory.h"
#include "common/id/SimpleIdGenerator.h"
#include <cassert>
#include "../../../xml/XmlTextReader.h"
#include "../../../xml/XmlException.h"
#include "../../metaStructure/model/meta/MappedMeta.h"
#include "../../../core/Pointer.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/case_conv.hpp>

using namespace Core;
using namespace Xml;
using namespace std;
using StateMachine::MachineContext;
using Common::ILogger;
using boost::algorithm::to_lower;

/**
 * TODO To jest właściwie taki pomysł, a nie TODO. Zajebiście by było,
 * gdyby te metody-handlery dostawały jakieś parametry. Na przykład metoda
 * setCurrentId dostawałaby to ID do ustawienia etc. Ale to trzebaby
 * zaimplementować w FSM.
 */
namespace Container {

XmlMetaService::XmlMetaService ()
{
        machScope["service"] = Core::Variant (this);
        ctx.setMap (MachineContext::MACHINE, &machScope);
        machine = XmlMetaServiceFactory::createMachine ();
//        log = Ptr <Common::ILogger> (new Common::NullLogger());
//        log = Ptr <ILogger> (new Common::ConsoleLogger ());
//        machine->setLogger (log);
}

/****************************************************************************/

void XmlMetaService::runLog (bool back)
{
        if (!log) {
                return;
        }

        log->log ("------------");
        log->log (boost::lexical_cast <std::string> (getXmlReader ()->depth ()) + std::string ("Depth=") +
                boost::lexical_cast <std::string> (getXmlReader ()->depth ()) +
                ", nodeType=" + Xml::XmlTextReader::strReaderType (((back) ? (XML_READER_TYPE_END_ELEMENT) : (getXmlReader ()->nodeType ()))) +
                ", name=" + getXmlReader ()->name () +
                ", isEmpty=" + boost::lexical_cast <std::string> (getXmlReader ()->isEmptyElement ()) +
                ", attribCount=" + boost::lexical_cast <std::string> (getXmlReader ()->attributeCount ()) +
                ", hasAttrib=" + boost::lexical_cast <std::string> (getXmlReader ()->hasAttributes ()) +
                ", value=" + getXmlReader ()->value () + "\n");
}

/****************************************************************************/

void XmlMetaService::populate (const std::string &xmlFile)
{
        assert (getXmlReader ());
        assert (metaContainer);
        machine->reset ();

        VariantMap run;
        VariantMap transition;
        ctx.setMap (MachineContext::RUN, &run);
        ctx.setMap (MachineContext::TRANSITION, &transition);

        getXmlReader ()->readerForFilename (xmlFile);

        try {
                // Main loop
                while (xmlReader->read ()) {

                        runLog ();

                        // TODO zamęt, zmienić coś z obsługą contextu w Machine, wyjebać te cleary.
                        run.clear();
                        transition.clear();

                        // Optymalizacja. machine->run (&ctx) jest bardzo kosztowne, więc omijamy zbędne rozgałęzienia kodu. Zysk ok 15%
                        int nodeType = xmlReader->nodeType ();

                        if (nodeType != XML_READER_TYPE_ELEMENT &&
                                nodeType != XML_READER_TYPE_ATTRIBUTE &&
                                nodeType != XML_READER_TYPE_TEXT &&
                                nodeType != XML_READER_TYPE_END_ELEMENT) {
                                continue;
                        }

                        prepareInputs (&run, &transition, xmlReader);
                        machine->run (&ctx);

                        if (xmlReader->nodeType () == XML_READER_TYPE_ELEMENT) {

                                while (xmlReader->moveToNextAttribute ()) {
                                        runLog ();
                                        prepareInputs (&run, &transition, xmlReader);
                                        machine->run (&ctx);
                                }

                                getXmlReader ()->moveToElement ();

                                /*
                                 * Wykrywanie tagów, które są puste, np <value/>. To jest
                                 * taka symulacja tagu końcącego.
                                 */
                                if (getXmlReader ()->isEmptyElement ()) {
                                        runLog (true);
                                        prepareInputs (&run, &transition, xmlReader, true);
                                        machine->run (&ctx);
                                }

                        }
                }

                // A teraz importy, jeśli jakieś były.
//                for (StringList::iterator i = imports.begin (); i != imports.end ();) {
//                        StringList::iterator j = i;
//                        j++;
//                        populate (*i);
//                        imports.erase (i);
//                        i = j;
//                }

                while (!imports.empty ()) {
                        string path = imports.front ();
                        imports.pop ();
                        populate (path);
                }


        }
        catch (Xml::XmlException &e) {
                e.addMessage ("In XmlMetaService::populate, xmlFile : [" + xmlFile + "]");
                throw;
        }
}

/****************************************************************************/

void XmlMetaService::reset ()
{
        if (machine) {
                machine->reset ();
                // Wyczyść kolejkę importów.
                while (!imports.empty ()) {
                        imports.pop ();
                }
        }
}

/****************************************************************************/

void XmlMetaService::prepareType (Core::VariantMap *map, int nodeType) const
{
        Variant trueTmp = Core::Variant (true);

        switch (nodeType) {
        case XML_READER_TYPE_ELEMENT:
                map->operator[] ("typeElem") = trueTmp;
                break;

        case XML_READER_TYPE_ATTRIBUTE:
                map->operator[] ("typeAttr") = trueTmp;
                break;

        case XML_READER_TYPE_TEXT:
                map->operator[] ("typeText") = trueTmp;
                break;

        case XML_READER_TYPE_DOCUMENT_TYPE:
                map->operator[] ("typeDoc") = trueTmp;
                break;

        case XML_READER_TYPE_END_ELEMENT:
                map->operator[] ("typeEndElem") = trueTmp;
                break;

        default:
                break;
        }
}

/****************************************************************************/

void XmlMetaService::prepareInputs (Core::VariantMap *run,
                                    Core::VariantMap *transition,
                                    Ptr <Xml::IXmlReader> reader, bool end)
{
        if (!end) {
                prepareType (transition, xmlReader->nodeType ());
        }
        else {
                prepareType (transition, XML_READER_TYPE_END_ELEMENT);
        }

        transition->operator[] ("name") = Core::Variant (xmlReader->name ());
        *run = *transition;
        run->operator[] ("value") = Core::Variant (xmlReader->value());
}

/****************************************************************************/

Ptr <IMeta> XmlMetaService::getCurrentMeta () const
{
        if (!metaStack.size ()) {
                throw XmlMetaServiceException ("XmlMetaServiceException : metaStack is empty.");
        }

        Ptr <IMeta> meta = metaStack.top ();

        if (!meta) {
                throw XmlMetaServiceException ("Current meta is null.");
        }

        return meta;
}

/****************************************************************************/

Ptr <MappedMeta> XmlMetaService::getCurrentMappedMeta () const
{
        Ptr <MappedMeta> meta = dynamic_pointer_cast <MappedMeta> (getCurrentMeta ());

        if (!meta) {
                throw XmlMetaServiceException ("Can't cast to MappedMeta.");
        }

        return meta;
}

/****************************************************************************/

Ptr <IndexedMeta> XmlMetaService::getCurrentIndexedMeta () const
{
        Ptr <IndexedMeta> meta = dynamic_pointer_cast <IndexedMeta> (getCurrentMeta ());

        if (!meta) {
                throw XmlMetaServiceException ("Can't cast to IndexedMeta.");
        }

        return meta;
}

/****************************************************************************/

Ptr <IElem> XmlMetaService::getCurrentElem () const
{
        if (!metaElemStack.size ()) {
                throw XmlMetaServiceException ("XmlMetaServiceException : metaElemStack is empty.");
        }

        Ptr <IElem> elem = metaElemStack.top ();

        if (!elem) {
                throw XmlMetaServiceException ("Current metaElem is null.");
        }

        return elem;
}

/****************************************************************************/

Ptr <AbstractElem> XmlMetaService::getCurrentAbstractElem () const
{
        // TODO możnaby się pozbyć tego kastowania jakoś.
        Ptr <AbstractElem> m = dynamic_pointer_cast <AbstractElem> (getCurrentElem ());

        if (!m) {
                throw XmlMetaServiceException ("Can't cast to AbstractElem.");
        }

        return m;
}

/****************************************************************************/

Ptr <MapElem> XmlMetaService::getCurrentMapElem () const
{
        // TODO możnaby się pozbyć tego kastowania jakoś.
        Ptr <MapElem> m = dynamic_pointer_cast <MapElem> (getCurrentElem ());

        if (!m) {
                throw XmlMetaServiceException ("Can't cast to MapElem.");
        }

        return m;
}

/****************************************************************************/

Ptr <ListElem> XmlMetaService::getCurrentListElem () const
{
        // TODO możnaby się pozbyć tego kastowania jakoś.
        Ptr <ListElem> m = dynamic_pointer_cast <ListElem> (getCurrentElem ());

        if (!m) {
                throw XmlMetaServiceException ("Can't cast to ListElem.");
        }

        return m;
}

/*##########################################################################*/

void XmlMetaService::setDefaultLazyInit ()
{
        if (log) { log->log ("XmlMetaService::setDefaultLazyInit"); }
}

/****************************************************************************/

void XmlMetaService::setDefaultInitMethod ()
{
        if (log) { log->log ("XmlMetaService::setDefaultInitMethod"); }
}

/****************************************************************************/

void XmlMetaService::setDefaultMerge ()
{
        if (log) { log->log ("XmlMetaService::setDefaultMerge"); }
}

/****************************************************************************/

void XmlMetaService::popCurrentBean ()
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

        if (log) {
                log->log ("Adding meta object with id : " + meta->getId ());
                log->log ("XmlMetaService::popCurrentBean");
        }
}

/****************************************************************************/

void XmlMetaService::popCurrentMetaAndGenerateRef ()
{
        // Pobierz aktualny meta
        Ptr <IMeta> meta = getCurrentMeta ();
        std::string metaId = meta->getId ();

        // Wygeneruj mu ID
        if (metaId.empty ()) {
                metaId = idGenerator->generate (meta.get ());
                meta->setId (metaId);
        }

//        // Zdejmij.
//        metaStack.pop ();
//
//        // Umiesc ten gotowy meta w kontenerze.
//        metaContainer->add (meta);

        popCurrentBean ();

        /*
         * Nowy map elem z referencją do tego poprzedniego meta.
         * Dodajemy go do stpsu tak jak by parser natrafił na tag
         * <ref/>.
         */
        Ptr <AbstractElem> elem = getCurrentAbstractElem ();
        elem->setData (RefData::create (metaId));

        if (log) {
                log->log ("Adding meta object with id : " + meta->getId ());
                log->log ("XmlMetaService::popCurrentMetaAndGenerateRef");
        }
}

/****************************************************************************/

void XmlMetaService::pushNewMappedMeta ()
{
        // 1. Stworzyć nowy obiekt Meta
        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();

        // 2. Umieścić go na wierzchołku stosu Meta w serwisie.
        metaStack.push (meta);
        if (log) { log->log ("XmlMetaService::pushNewMappedMeta"); }
}

/****************************************************************************/

void XmlMetaService::pushNewIndexedMeta ()
{
        Ptr <IndexedMeta> meta = boost::make_shared <IndexedMeta> ();
        metaStack.push (meta);
        if (log) { log->log ("XmlMetaService::pushNewIndexedMeta"); }
}

/****************************************************************************/

void XmlMetaService::pushNewMapElem ()
{
        Ptr <MapElem> e = MapElem::create ();
        metaElemStack.push (e);
        if (log) { log->log ("XmlMetaService::pushNewMapElem"); }
}

/****************************************************************************/

void XmlMetaService::pushNewListElem ()
{
        Ptr <ListElem> e = ListElem::create ();
        metaElemStack.push (e);
        if (log) { log->log ("XmlMetaService::pushNewListElem"); }
}

/****************************************************************************/

void XmlMetaService::popCurrentMapElem ()
{
        // 1. Pobierz aktualny Meta
        Ptr <MappedMeta> meta = getCurrentMappedMeta ();

        // 2. Pobierz aktualny (juz gotowy) metaElem
        Ptr <MapElem> elem = getCurrentMapElem ();

        // 3. Zdejmij go.
        metaElemStack.pop ();

        // 4. Dodaj go.
        meta->addField (elem);

        if (log) { log->log ("XmlMetaService::popCurrentMapElem key=(" + elem->getKey() + "), data=(" + ((elem->getData()) ? (elem->getData()->getData ()) : std::string ()) + ")"); }
}

/****************************************************************************/

void XmlMetaService::popCurrentIndexedElem ()
{
        // 1. Pobierz aktualny Meta
        Ptr <IndexedMeta> meta = getCurrentIndexedMeta ();

        // 2. Pobierz aktualny (juz gotowy) metaElem
        Ptr <ListElem> elem = getCurrentListElem ();

        // 3. Zdejmij go.
        metaElemStack.pop ();

        // 4. Dodaj go.
        meta->addField (elem);

        if (log) { log->log ("XmlMetaService::popCurrentIndexedElem"); }
}

/****************************************************************************/

void XmlMetaService::popCurrentCArg ()
{
        // 1. Pobierz aktualny Meta
        Ptr <IMeta> meta = getCurrentMeta ();

        // 2. Pobierz aktualny (juz gotowy) metaElem
        Ptr <ListElem> elem = getCurrentListElem ();

        // 3. Zdejmij go.
        metaElemStack.pop ();

        // 4. Dodaj go jako cArg.
        meta->addConstructorArg (elem);

        if (log) { log->log ("XmlMetaService::popCurrentCArg"); }
}

/****************************************************************************/

void XmlMetaService::setCurrentMapElemKey (const std::string &s)
{
        // TODO możnaby się pozbyć tego kastowania jakoś.
        Ptr <MapElem> m = dynamic_pointer_cast <MapElem> (getCurrentElem ());

        if (!m) {
                throw XmlMetaServiceException ("Can't cast to MapElem.");
        }

        m->setKey (s);

        if (log) { log->log ("XmlMetaService::setCurrentMapElemKey (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::newValueData ()
{
        Ptr <AbstractElem> m = getCurrentAbstractElem ();
        m->setData (ValueData::create ());
        if (log) { log->log ("XmlMetaService::newValueData"); }
}

/****************************************************************************/

void XmlMetaService::newRefData ()
{
        Ptr <AbstractElem> m = getCurrentAbstractElem ();
        m->setData (RefData::create ());
        if (log) { log->log ("XmlMetaService::newRefData"); }
}


/****************************************************************************/

void XmlMetaService::newNullData ()
{
        Ptr <AbstractElem> ae = getCurrentAbstractElem ();
        ae->setData (NullData::create ());
        if (log) { log->log ("XmlMetaService::newNullData"); }
}

/****************************************************************************/

void XmlMetaService::setCurrentValueDataType (const std::string &s)
{
        Ptr <IElem> m = getCurrentElem ();
        Ptr <ValueData> v = dynamic_pointer_cast <ValueData> (m->getData ());

        if (!v) {
                throw XmlMetaServiceException ("Can't cast currentProperty to ValueData.");
        }

        v->setType (s);

        if (log) { log->log ("XmlMetaService::setCurrentValueDataType (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setCurrentValueDataData (const std::string &s)
{
        Ptr <AbstractElem> m = getCurrentAbstractElem ();
        Ptr <ValueData> v = dynamic_pointer_cast <ValueData> (m->getData ());

        if (!v) {
                throw XmlMetaServiceException ("Can't cast currentProperty to ValueData.");
        }

        v->setData (s);

        if (log) { log->log ("XmlMetaService::setCurrentValueDataData (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setCurrentRefDataData (const std::string &s)
{
        Ptr <AbstractElem> m = getCurrentAbstractElem ();
        Ptr <RefData> v = dynamic_pointer_cast <RefData> (m->getData ());

        if (!v) {
                throw XmlMetaServiceException ("Can't cast currentProperty to RefData.");
        }

        v->setData (s);

        if (log) { log->log ("XmlMetaService::setCurrentRefDataData (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaId (const std::string &id)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setId (id);
        if (log) { log->log ("XmlMetaService::setMetaId (" + id + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaClass (const std::string &s)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setClass (s);
        if (log) { log->log ("XmlMetaService::setMetaClass (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaParent (const std::string &s)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setParent (s);
        if (log) { log->log ("XmlMetaService::setMetaParent (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaFactory (const std::string &s)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setFactory (s);
        if (log) { log->log ("XmlMetaService::setMetaFactory (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaEditor (const std::string &s)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setEditor (s);
        if (log) { log->log ("XmlMetaService::setMetaEditor (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaSingleton (bool b)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setScope ((b) ? (IMeta::SINGLETON) : (IMeta::PROTOTYPE));
        if (log) { log->log (std::string ("XmlMetaService::setMetaSingleton (") + boost::lexical_cast <std::string> (b) + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaLazyInit (bool b)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setLazyInit (b);
        if (log) { log->log (std::string ("XmlMetaService::setMetaLazyInit (") + boost::lexical_cast <std::string> (b) + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaScope (const std::string &scope)
{
        Ptr <IMeta> m = getCurrentMeta ();
        std::string s = boost::to_lower_copy (scope);

        if (s == "singleton") {
                m->setScope (IMeta::SINGLETON);
        }
        else if (s == "prototype") {
                m->setScope (IMeta::PROTOTYPE);
        }
        else if (s == "bean") {
                m->setScope (IMeta::BEAN);
        }
        else {
                throw XmlMetaServiceException ("Wrong argument to scope=... arg. Correnct values are : singleton | prototype | bean. You passed : [" + scope + "]");
        }

        if (log) { log->log (std::string ("XmlMetaService::setMetaScope (") + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::setMetaInitMethod (const std::string &s)
{
        Ptr <IMeta> m = getCurrentMeta ();
        m->setInitMethod (s);
        if (log) { log->log ("XmlMetaService::setMetaInitMethod (" + s + ")"); }
}

/****************************************************************************/

void XmlMetaService::importFile (const std::string &s)
{
        imports.push (s);
        if (log) { log->log ("XmlMetaService::importFile (" + s + ")"); }
}

}
