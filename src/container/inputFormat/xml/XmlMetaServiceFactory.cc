/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "XmlMetaServiceFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "Machine.h"
#include "SubMachineState.h"
#include "ChainMachine.h"
#include "condition/Condition.h"
#include "action/Action.h"
#include "extension/StackStateExtension.h"
#include "common/id/SimpleIdGenerator.h"
#include "XmlMetaService.h"
#include "../../../xml/XmlTextReader.h"
#include "../../common/id/SimpleIdGenerator.h"
#include "../../../common/logger/NullLogger.h"
#include "../../../common/logger/ILogger.h"
#include "../../../core/Pointer.h"

namespace Container {
using namespace Wrapper;
using namespace Core;
using namespace StateMachine;

Ptr <XmlMetaService> XmlMetaServiceFactory::createXmlMetaServiceFactory ()
{
        Ptr <XmlMetaService> metaService (new XmlMetaService ());
        metaService->setXmlReader (Ptr <Xml::IXmlReader> (new Xml::XmlTextReader));
        metaService->setIdGenerator (Ptr <IIdGenerator> (new SimpleIdGenerator));
        return metaService;
}

/****************************************************************************/

Ptr <Machine> XmlMetaServiceFactory::createMachine ()
{
        Ptr <Machine> machine = Machine::create ();
        MachineExtensionList extList;
        Ptr <StackStateExtension> ext (new StackStateExtension);
        // TODO to powinien być ten sam logger co w reszcie maszyny!
        ext->setLogger (Ptr <Common::ILogger> (new Common::NullLogger));
        extList.push_back (ext);
        machine->setExtensionList (extList);
        machine->setInitialStateName ("init");

        Ptr <Transition> transition;
        Ptr <State> state;

/*------init----------------------------------------------------------------*/

        /// Początek działania kontenera.
        state = State::create ("init");
        machine->addState (state);

        state->addTransition (Transition::create ("init", "idle",
            machine->createCondition ("$!typeElem && $!name == 'beans'")));

/*------idle----------------------------------------------------------------*/

        /// Jesteśmy pomiędzy jakimikolwiek deklaracjami beanów, czyli w ROOT-elemencie <beans>.
        state = State::create ("idle");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'default-lazy-init'"),
                                                      K202Action::create ("$service.setDefaultLazyInit ($value == 'true')")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'default-init-method'"),
                                                      K202Action::create ("$service.setDefaultInitMethod ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'default-merge'"),
                                                      K202Action::create ("$service.setDefaultMerge ($value == 'true')")));

        state->addTransition (Transition::create ("idle", "bean",
            machine->createCondition ("$!typeElem && $!name == 'bean'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        state->addTransition (Transition::create ("idle", "list",
            machine->createCondition ("$!typeElem && $!TRANSITION.name == 'list'"),
            K202Action::create ("$service.pushNewIndexedMeta ()")));

        state->addTransition (Transition::create ("idle", "map",
            machine->createCondition ("$!typeElem && $!name == 'map'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        state->addTransition (Transition::create ("idle", "alias",
            machine->createCondition ("$!typeElem && $!name == 'alias'")));

        state->addTransition (Transition::create ("idle", "import",
            machine->createCondition ("$!typeElem && $!name == 'import'")));

        state->addTransition (Transition::create ("idle", "@shutDown",
            machine->createCondition ("$!typeEndElem && $!name == 'beans'")));

/*------bean----------------------------------------------------------------*/

        /// Nowy bean (tworzy się za pomocą taga <bean>).
        state = State::create ("bean");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'id'"),
                                                      K202Action::create ("$service.setMetaId ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'class'"),
                                                      K202Action::create ("$service.setMetaClass ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'parent'"),
                                                      K202Action::create ("$service.setMetaParent ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'singleton'"),
                                                      K202Action::create ("$service.setMetaSingleton ($value == 'true')")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'lazy-init'"),
                                                      K202Action::create ("$service.setMetaLazyInit ($value == 'true')")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'scope'"),
                                                      K202Action::create ("$service.setMetaScope ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'init-method'"),
                                                      K202Action::create ("$service.setMetaInitMethod ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'editor'"),
                                                      K202Action::create ("$service.setMetaEditor ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'factory'"),
                                                      K202Action::create ("$service.setMetaFactory ($value)")));


        state->addTransition (Transition::create ("bean", "property",
            machine->createCondition ("$!typeElem && $!name == 'property'"),
            K202Action::create ("$service.pushNewMapElem ()")));

        state->addTransition (Transition::create ("bean", "carg",
            machine->createCondition ("$!typeElem && $!name == 'constructor-arg'"),
            K202Action::create ("$service.pushNewListElem ()")));

        // TODO Może tn warunek zmienc na $prevState != 'idle', a ten na końcu $prevState == 'idle'
        state->addTransition (Transition::create ("bean", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'bean' && ($!prevState == 'property' || $!prevState == 'carg' || $!prevState == 'entry')"),
            K202Action::create ("$service.popCurrentMetaAndGenerateRef ()")));

        state->addTransition (Transition::create ("bean", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'bean' && $!prevState == 'list'"),
            K202Action::create ("$service.popCurrentMetaAndGenerateRef (); $service.popCurrentIndexedElem ()")));

        // TODO Potrzebny warunek na brak $prevState
        state->addTransition (Transition::create ("bean", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'bean' && $!prevState == 'idle'"),
            K202Action::create ("$service.popCurrentBean ()")));

/*------property------------------------------------------------------------*/

        /// Weszliśmy w obsługę taga <property> dalej będą sub-maszyny.
        state = State::create ("property");
        machine->addState (state);

        /// Atrybut property name.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'name'"),
                                                      K202Action::create ("$service.setCurrentMapElemKey ($value)")));

        /// Atrybut property ref.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'ref'"),
                                                      K202Action::create ("$service.newRefData (); $service.setCurrentRefDataData ($value)")));

        /// Atrybut property value.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'value'"),
                                                      K202Action::create ("$service.newValueData (); $service.setCurrentValueDataData ($value)")));

        /// Przejścia
        state->addTransition (Transition::create ("property", "bean",
            machine->createCondition ("$!typeElem && $!name == 'bean'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        state->addTransition (Transition::create ("property", "ref",
            machine->createCondition ("$!typeElem && $!name == 'ref'")));

        state->addTransition (Transition::create ("property", "idref",
            machine->createCondition ("$!typeElem && $!name == 'idref'")));

        state->addTransition (Transition::create ("property", "value",
            machine->createCondition ("$!typeElem && $!name == 'value'")));

        state->addTransition (Transition::create ("property", "null",
            machine->createCondition ("$!typeElem && $!name == 'null'")));

        state->addTransition (Transition::create ("property", "list",
            machine->createCondition ("$!typeElem && $!name == 'list'"),
            K202Action::create ("$service.pushNewIndexedMeta ()")));

        state->addTransition (Transition::create ("property", "map",
            machine->createCondition ("$!typeElem && $!name == 'map'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        /*
         * Wyjscie ze stanu property do bean.
         */
        state->addTransition (Transition::create ("property", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'property'"),
            K202Action::create ("$service.popCurrentMapElem ()")));

/*------c-args-------------------------------------------------------*/

        state = State::create ("carg");
        machine->addState (state);

        /// Atrybut property ref.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'ref'"),
                                                      K202Action::create ("$service.newRefData (); $service.setCurrentRefDataData ($value)")));

        /// Atrybut property value.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'value'"),
                                                      K202Action::create ("$service.newValueData (); $service.setCurrentValueDataData ($value)")));

        /// Przejścia
        state->addTransition (Transition::create ("carg", "bean",
            machine->createCondition ("$!typeElem && $!name == 'bean'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        state->addTransition (Transition::create ("carg", "ref",
            machine->createCondition ("$!typeElem && $!name == 'ref'")));

        state->addTransition (Transition::create ("carg", "idref",
            machine->createCondition ("$!typeElem && $!name == 'idref'")));

        state->addTransition (Transition::create ("carg", "value",
            machine->createCondition ("$!typeElem && $!name == 'value'")));

        state->addTransition (Transition::create ("carg", "null",
            machine->createCondition ("$!typeElem && $!name == 'null'")));

        state->addTransition (Transition::create ("carg", "list",
            machine->createCondition ("$!typeElem && $!name == 'list'"),
            K202Action::create ("$service.pushNewIndexedMeta ()")));

        state->addTransition (Transition::create ("carg", "map",
            machine->createCondition ("$!typeElem && $!name == 'map'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        /*
         * Wyjscie ze stanu property do bean.
         */
        state->addTransition (Transition::create ("carg", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'constructor-arg'"),
            K202Action::create ("$service.popCurrentCArg ()")));

/*------list----------------------------------------------------------------*/

        state = State::create ("list");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'id'"),
                                                      K202Action::create ("$service.setMetaId ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'class'"),
                                                      K202Action::create ("$service.setMetaClass ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'singleton'"),
                                                      K202Action::create ("$service.setMetaSingleton ($value == 'true')")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'lazy-init'"),
                                                      K202Action::create ("$service.setMetaLazyInit ($value == 'true')")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'scope'"),
                                                      K202Action::create ("$service.setMetaScope ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'parent'"),
                                                      K202Action::create ("$service.setMetaParent ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'editor'"),
                                                      K202Action::create ("$service.setMetaEditor ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'factory'"),
                                                      K202Action::create ("$service.setMetaFactory ($value)")));

        state->addTransition (Transition::create ("list", "bean",
            machine->createCondition ("$!typeElem && $!name == 'bean'"),
            K202Action::create ("$service.pushNewListElem (); $service.pushNewMappedMeta ()")));

        state->addTransition (Transition::create ("list", "ref",
            machine->createCondition ("$!typeElem && $!name == 'ref'"),
            K202Action::create ("$service.pushNewListElem (); $service.newRefData ()")));

        state->addTransition (Transition::create ("list", "idref",
            machine->createCondition ("$!typeElem && $!name == 'idref'")));

        state->addTransition (Transition::create ("list", "listValue",
            machine->createCondition ("$!typeElem && $!name == 'value'"),
            K202Action::create ("$service.pushNewListElem ()")));

        state->addTransition (Transition::create ("list", "null",
            machine->createCondition ("$!typeElem && $!name == 'null'"),
            K202Action::create ("$service.pushNewListElem ()")));

        state->addTransition (Transition::create ("list", "list",
            machine->createCondition ("$!typeElem && $!TRANSITION.name == 'list'"),
            K202Action::create ("$service.pushNewListElem (); $service.pushNewIndexedMeta ()")));

        state->addTransition (Transition::create ("list", "map",
            machine->createCondition ("$!typeElem && $!name == 'map'"),
            K202Action::create ("$service.pushNewListElem (); $service.pushNewMappedMeta ()")));



        /// Wyjście
        state->addTransition (Transition::create ("list", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'list' && ($!prevState == 'property' || $!prevState == 'carg' || $!prevState == 'entry')"),
            K202Action::create ("$service.popCurrentMetaAndGenerateRef ()")));

        state->addTransition (Transition::create ("list", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'list' && $!prevState == 'list'"),
            K202Action::create ("$service.popCurrentMetaAndGenerateRef (); $service.popCurrentIndexedElem ()")));

        state->addTransition (Transition::create ("list", "@back",
                            machine->createCondition ("$!typeEndElem && $!name == 'list' && $!prevState == 'idle'"),
                            K202Action::create ("$service.popCurrentBean ()")));

///*------meta----------------------------------------------------------------*/
// TODO A może to meta by się jednak przydało? Na przykłąd do podania ReflectionFactory, czy ma zwracać Ptr'y, czy *
//        state1 = Ptr <State> (new State ("meta"));
//        machine->addState (state1);
//
//        sc = SimpleCondition::create ("XML_READER_TYPE_ATTRIBUTE", "KEY");
//        state1->addInputAction (Ptr <InputActions> (new InputActions (sc, "SET_META_KEY")));
//
//        sc = SimpleCondition::create ("XML_READER_TYPE_ATTRIBUTE", "VALUE");
//        state1->addInputAction (Ptr <InputActions> (new InputActions (sc, "SET_META_VALUE")));
//
//        sc = SimpleCondition::create ("XML_READER_TYPE_END_ELEMENT", "META");
//        state->addTransition (Transition::create ("meta", "back", sc));

/*------ref-----------------------------------------------------------------*/

        state = State::create ("ref");
        state->addEntryAction (K202Action::create ("$service.newRefData ()"));
        machine->addState (state);

        /// Property ref, czyli bean lub local.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'bean'"),
                                                      K202Action::create ("$service.setCurrentRefDataData ($value)")));

        state->addTransition (Transition::create ("ref", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'ref'")));

        machine->addTransitionAction (TransitionAction::create ("ref", "list", K202Action::create ("$service.popCurrentIndexedElem ()")));

/*------idref---------------------------------------------------------------*/

        state = State::create ("idref");
        machine->addState (state);

        /// Property idref, czyli tak samo jak ref bean lub local.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr"),
                                                      K202Action::create ("$service.setIdRefArgument ($value)")));

        state->addTransition (Transition::create ("idref", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'idref'")));

/*------value---------------------------------------------------------------*/

        state = State::create ("value1");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'type'"),
                                                      K202Action::create ("$service.setCurrentValueDataType ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeText == true"),
                                                      K202Action::create ("$service.setCurrentValueDataData ($value)")));

        Ptr <Machine> subMachineRegular = Machine::create ();
        subMachineRegular->addState (state);
        subMachineRegular->setInitialStateName ("value1");





        // Maszyna i substan - dla zwykłego procesowania value
        Ptr <SubMachineState> subState = SubMachineState::create ("value", subMachineRegular);
        subState->addEntryAction (K202Action::create ("$service.newValueData ()"));
        machine->addState (subState);

        // Wyjście ze stanu
        subState->addTransition (Transition::create ("value", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'value'")));

        /*
         * Substan dla value w list. Alternatywnie możnaby to zaimplementować za pomocą
         * nowych przejść dodawanych bezpośrednio do maszyny, a nie do stanu.
         */
        Ptr <SubMachineState> subStateListValue = SubMachineState::create ("listValue", subMachineRegular);
        subStateListValue->addEntryAction (K202Action::create ("$service.newValueData ()"));
        subStateListValue->addExitAction (K202Action::create ("$service.popCurrentIndexedElem ()"));
        machine->addState (subStateListValue);

        // Wyjście ze stanu
        subStateListValue->addTransition (Transition::create ("listValue", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'value'")));

/*------null----------------------------------------------------------------*/

        state = State::create ("null");
        machine->addState (state);

        state->addEntryAction (K202Action::create ("$service.newNullData ()"));

        state->addTransition (Transition::create ("null", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'null'")));

        machine->addTransitionAction (TransitionAction::create ("null", "list",
                        K202Action::create ("$service.popCurrentIndexedElem ()")));

/*------map-----------------------------------------------------------------*/

        state = State::create ("map");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'id'"),
                                                      K202Action::create ("$service.setMetaId ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'class'"),
                                                      K202Action::create ("$service.setMetaClass ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'singleton'"),
                                                      K202Action::create ("$service.setMetaSingleton ($value == 'true')")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'lazy-init'"),
                                                      K202Action::create ("$service.setMetaLazyInit ($value == 'true')")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'scope'"),
                                                      K202Action::create ("$service.setMetaScope ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'parent'"),
                                                      K202Action::create ("$service.setMetaParent ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'editor'"),
                                                      K202Action::create ("$service.setMetaEditor ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'factory'"),
                                                      K202Action::create ("$service.setMetaFactory ($value)")));

        state->addTransition (Transition::create ("map", "entry",
            machine->createCondition ("$!typeElem && $!name == 'entry'"),
            K202Action::create ("$service.pushNewMapElem ()")));

        /// Wyjścia
        state->addTransition (Transition::create ("map", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'map' && ($!prevState == 'property' || $!prevState == 'carg' || $!prevState == 'entry')"),
            K202Action::create ("$service.popCurrentMetaAndGenerateRef ()")));

        state->addTransition (Transition::create ("map", "@back",
            machine->createCondition ("$!typeEndElem && $!name == 'map' && $!prevState == 'list'"),
            K202Action::create ("$service.popCurrentMetaAndGenerateRef (); $service.popCurrentIndexedElem ()")));

        // TODO działanie maszyny zalezy od kolejności wykonania transition Actios. Tu powinien byc warunek na prev state == idle, czy coś takiego
        state->addTransition (Transition::create ("map", "@back",
                            machine->createCondition ("$!typeEndElem && $!name == 'map' && $!prevState == 'idle'"),
                            K202Action::create ("$service.popCurrentBean ()")));

/*------entry---------------------------------------------------------------*/

        state = State::create ("entry");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'key'"),
                                                      K202Action::create ("$service.setCurrentMapElemKey ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'value'"),
                                                      K202Action::create ("$service.newValueData (); $service.setCurrentValueDataData ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'ref'"),
                                                      K202Action::create ("$service.newRefData (); $service.setCurrentRefDataData ($value)")));

        state->addTransition (Transition::create ("entry", "key",
            machine->createCondition ("$!typeElem && $!name == 'key'")));

        state->addTransition (Transition::create ("entry", "bean",
            machine->createCondition ("$!typeElem && $!name == 'bean'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        state->addTransition (Transition::create ("entry", "ref",
            machine->createCondition ("$!typeElem && $!name == 'ref'")));

        state->addTransition (Transition::create ("entry", "idref",
            machine->createCondition ("$!typeElem && $!name == 'idref'")));

        state->addTransition (Transition::create ("entry", "value",
            machine->createCondition ("$!typeElem && $!name == 'value'")));

        state->addTransition (Transition::create ("entry", "null",
            machine->createCondition ("$!typeElem && $!name == 'null'")));

        state->addTransition (Transition::create ("entry", "list",
            machine->createCondition ("$!typeElem && $!name == 'list'"),
            K202Action::create ("$service.pushNewIndexedMeta ()")));

        state->addTransition (Transition::create ("entry", "map",
            machine->createCondition ("$!typeElem && $!name == 'map'"),
            K202Action::create ("$service.pushNewMappedMeta ()")));

        /// Wyjście ze stanu
        state->addTransition (Transition::create ("entry", "@back",
                            machine->createCondition ("$!typeEndElem && $!name == 'entry'"),
                            K202Action::create ("$service.popCurrentMapElem ()")));

/*------key-----------------------------------------------------------------*/

        state = State::create ("key");
        machine->addState (state);

        /// Wartość wewnątrz taga value lub bezpośrednio.
        state->addInputAction (InputActions::create (machine->createCondition ("$!typeText == true"),
                                                      K202Action::create ("$service.setCurrentMapElemKey ($value)")));

        state->addTransition (Transition::create ("key", "@back", machine->createCondition ("$!typeEndElem && $!name == 'key'")));

/*------alias---------------------------------------------------------------*/

        state = State::create ("alias");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'name'"),
                                                      K202Action::create ("$service.setAliasName ($value)")));

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'alias'"),
                                                      K202Action::create ("$service.setAlias ($value)")));

        state->addTransition (Transition::create ("alias", "idle", machine->createCondition ("$!typeEndElem && $!name == 'alias'")));

/*------import--------------------------------------------------------------*/

        state = State::create ("import");
        machine->addState (state);

        state->addInputAction (InputActions::create (machine->createCondition ("$!typeAttr && $!name == 'resource'"),
                                                      K202Action::create ("$service.importFile ($value)")));

        state->addTransition (Transition::create ("import", "idle", machine->createCondition ("$!typeEndElem && $!name == 'import'")));

/*--------------------------------------------------------------------------*/

        return machine;
}

}
