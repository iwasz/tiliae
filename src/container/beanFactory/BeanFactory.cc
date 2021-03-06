/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "container/beanFactory/BeanFactory.h"

#include "BeanFactoryContainer.h"
#include "BeanFactoryContext.h"
#include "beanWrapper/IBeanWrapper.h"
#include "beanWrapper/plugins/MethodPlugin.h"
#include "container/Defs.h"
#include "container/metaStructure/model/MetaObject.h"
#include "core/variant/Cast.h"
#include "factory/ReflectionFactory.h"
#include <boost/lexical_cast.hpp>

namespace Container {

/****************************************************************************/

BeanFactory::BeanFactory (BeanFactoryContainer *c)
    : flags (0x00),
      cArgs (NULL),
      attributes (NULL),
      cArgsEditor (NULL),
      editor (NULL),
      factory (NULL),
      beanWrapper (NULL),
      outerBeanFactory (NULL),
      innerBeanFactories (NULL),
      container (c),
      markForDeletion (false)
{
}

/****************************************************************************/

BeanFactory::~BeanFactory ()
{
        delete innerBeanFactories;
        delete cArgs;
        delete cArgsEditor;

        if (flags & INPUT_MAP) {
                delete inputMap;
        }
        else if (flags & INPUT_LIST) {
                delete inputList;
        }

        if (flags & DELETE_FACTORY) {
                delete factory;
        }

        if (flags & DELETE_EDITOR) {
                delete editor;
        }

        if (attributes) {
                Attributes::deleteHeapCopy (attributes);
        }
}

/****************************************************************************/

void BeanFactory::setAttributes (Attributes *attributes)
{
        this->attributes = attributes;
        id = getStringAttribute (Attributes::ID_ARGUMENT, false);
}

/****************************************************************************/

Core::Variant BeanFactory::create (const Core::VariantMap &, Core::DebugContext *context) const
{
        try {
                // Check nesting level.
                BeanFactoryContext *bfc = dynamic_cast<BeanFactoryContext *> (context);

                if (bfc) {
                        bfc->incNested ();

                        if (bfc->getNested () > MAX_BEAN_NESTING) {
                                // Nie bawimy się w fatale, bo to jest tak krytyczmny bład, że trzeba przerwać działanie programu.
                                throw TooDeepNestingException ("BeanFactory::create. Id : [" + id + "]. Too deep "
                                                                                                    "bean nesting. Max level of nested beans is : "
                                                               + boost::lexical_cast<std::string> (MAX_BEAN_NESTING));
                        }
                }

                MetaObject::Scope myScope = getScope ();
                if ((flags & FORCE_SINGLETON || myScope == MetaObject::SINGLETON) && !storedSingleton.isNone ()) {
                        return storedSingleton;
                }

                notifyBeforePropertiesSet ();

                assert (factory);
                assert (editor);

                Core::Variant output;
                /*
                 * Parametry dla Fabryki. Klucze pochodzą z ReflectionFactory, ale nie znaczy to, że
                 * konkretna fabryka musi być tego typu. Można wrzucić inną, ktora będzie trzymała się
                 * tej samej konwencji.
                 */
                Core::VariantMap factoryParams;
                Core::VariantVector list;
                Core::Variant cArgsEdited = Core::Variant (&list);

                // Trzeba sprawdzić, bo inaczej może się zamazać argument class (patrz test 24 myMap - class ustawione przez proxy).
                if (attributes->containsKey (Attributes::CLASS_ARGUMENT)) {
                        factoryParams[Factory::ReflectionFactory::CLASS_NAME] = Core::Variant (getStringAttribute (Attributes::CLASS_ARGUMENT));
                }

                bool err = false;
                dcBegin (context);

                if (cArgsEditor) {
                        if (!cArgsEditor->convert (Core::Variant (cArgs), &cArgsEdited, context)) {
                                dcCommit (context);
                                dcError (context, "Constructor args editor failed. ID : " + id);
                                return Core::Variant ();
                        }

                        factoryParams[Factory::ReflectionFactory::CONSTRUCTOR_ARGS] = cArgsEdited;
                }

                dcRollback (context);
                dcBegin (context);

                output = factory->create (factoryParams, context);

#if 0
                std::cerr << "BeanFactory:create. Container : " << container << ", id : " << id << ", output : " << output.toString () << std::endl;
#endif

                if (output.isNone ()) {
                        dcCommit (context);
                        dcError (context, "Factory in BeanFactory failed. ID : " + id);
                        return Core::Variant ();
                }

                if (output.isNull ()) {
                        dcCommit (context);
                        dcError (context, "BeanFactory::create : unable to create bean, factory returned none. ID = [" + id + "]");
                        return Core::Variant ();
                }

                dcRollback (context);
                dcBegin (context);

                if (!editor->convert (getInput (), &output, context)) {
                        dcCommit (context);
                        dcError (context, "Editor in BeanFactory failed. ID : " + id);
                        return Core::Variant ();
                }

                dcRollback (context);
                dcBegin (context);

                notifyAfterPropertiesSet ();

                // Uruchomienie metody init-method
                if (attributes->containsKey (Attributes::INITMETHOD_ARGUMENT)) {
                        assert (beanWrapper);
                        std::string initMethodName = getStringAttribute (Attributes::INITMETHOD_ARGUMENT);
                        beanWrapper->setWrappedObject (output);
                        Core::Variant v = beanWrapper->get (initMethodName, &err, context);

                        if (err || v.isNone ()) {
                                dcCommit (context);
                                dcError (context, "Cannot retrieve init-method of bean. Bean ID : " + id + ", init method name : [" + initMethodName + "]");
                                return Core::Variant ();
                        }

                        Ptr<Wrapper::Handler> handler = vcast<Ptr<Wrapper::Handler>> (v);

                        if (!fireMethod (handler, context)) {
                                return Core::Variant ();
                        }
                }
                else if (container && !container->getGlobalInitMethod ().empty ()) {
                        assert (beanWrapper);
                        beanWrapper->setWrappedObject (output);
                        Core::Variant v = beanWrapper->get (container->getGlobalInitMethod (), &err, context);

                        if (!err && !v.isNone ()) {
                                Ptr<Wrapper::Handler> handler = vcast<Ptr<Wrapper::Handler>> (v);

                                if (!fireMethod (handler, context)) {
                                        return Core::Variant ();
                                }
                        }
                }

                // Uruchomienie global id aware method
                if (container && !container->getGlobalIdAwareMethod ().empty ()) {
                        assert (beanWrapper);
                        beanWrapper->setWrappedObject (output);
                        Core::Variant v = beanWrapper->get (container->getGlobalIdAwareMethod (), &err, context);

                        if (!err && !v.isNone ()) {
                                Ptr<Wrapper::Handler> handler = vcast<Ptr<Wrapper::Handler>> (v);
                                Core::VariantVector params;
                                params.push_back (Core::Variant (id));

                                if (!fireMethod (handler, context, &params, false)) {
                                        return Core::Variant ();
                                }
                        }
                }

                if (bfc) {
                        bfc->decNested ();
                }

                if (flags & FORCE_SINGLETON || myScope == MetaObject::SINGLETON) {
                        storedSingleton = output;
                }

                if (myScope == MetaObject::SINGLETON || myScope == MetaObject::BEAN_SINGLETON) {
                        // Dodaj do mapy singletonów
                        if (myScope == MetaObject::BEAN_SINGLETON) {
                                container->addSingleton (NULL, output);
                        }
                        else {
                                Core::IAllocator *memoryAllocator = container->getMemoryAllocator ();
                                char *idCopy = (char *)memoryAllocator->malloc (id.length () + 1);
                                strcpy (idCopy, id.c_str ());

                                container->addSingleton (idCopy, output);
                        }
                }

                BeanFactoryMap *map = &container->getBeanFactoryMap ();

                /*
                 * Skasuj moje innerFactories jeśli jest pewność, że nie nie będą potrzebne, czyli:
                 * - Jeśli nie jestem rodzicem i moje dzieci mogą ich potrzebować.
                 * - Jeśli nie jestem dzieckiem rodzica, który ma (może mieć - nie sprawdzam czy ma) inne dzieci, które mogą ich potrzebować.
                 */
                if (!container->isStoreConfigurationForLinked ()) {
                        bool amIAParentOrChild = attributes->getBool (Attributes::IS_PARENT_ARGUMENT, true);
                        if (myScope == MetaObject::SINGLETON && !amIAParentOrChild) {
                                if (innerBeanFactories) {
                                        for (BeanFactoryMap::iterator i = innerBeanFactories->begin (); i != innerBeanFactories->end (); ++i) {
                                                std::string innerKey = i->first;
                                                BeanFactory *innerFactory = i->second;

                                                delete innerFactory;
                                                map->erase (innerKey);
                                        }
                                }
                        }

                        /*
                         * Skasuj mnie samego jeśli jestem singletonem i nie jestem rodzicem (wówczas jestem potrzebny dzieciom).
                         */
                        bool amIAParent = attributes->getBool (Attributes::IS_PARENT_ARGUMENT, false);
                        if (myScope == MetaObject::SINGLETON && !amIAParent) {
                                map = &container->getBeanFactoryMap ();
                                map->erase (id);

                                // Dodaj singleton
                                // delete this;
                                markForDeletion = true;
                        }
                }

                dcRollback (context);
                return output;
        }
        catch (TooDeepNestingException &e) {
                e.addContext (*context);
                throw;
        }
        catch (Core::Exception &e) {
                dcCommit (context);
                dcError (context, "BeanFactory::create. Id : [" + id + "] fullyInitialized : [" + boost::lexical_cast<std::string> (flags & FULLY_INITIALIZED)
                                 + "]. Exception caught : " + e.what ());
        }

        return Core::Variant ();
}

/****************************************************************************/

void BeanFactory::onBeforePropertiesSet (BeanFactory const *notifier) const
{
        MetaObject::Scope myScope = getScope ();

        if (myScope == MetaObject::BEAN_PROTOTYPE || myScope == MetaObject::BEAN_SINGLETON) {
                flags |= FORCE_SINGLETON;
        }
}

/****************************************************************************/

void BeanFactory::onAfterPropertiesSet (BeanFactory const *notifier) const
{
        MetaObject::Scope myScope = getScope ();

        if (myScope == MetaObject::BEAN_PROTOTYPE || myScope == MetaObject::BEAN_SINGLETON) {
                flags &= ~FORCE_SINGLETON;

                if (myScope != MetaObject::SINGLETON) {
                        storedSingleton = Core::Variant ();
                }
        }
}

/****************************************************************************/

void BeanFactory::notifyAfterPropertiesSet () const
{
        if (innerBeanFactories) {

                for (BeanFactoryMap::const_iterator i = innerBeanFactories->begin (); i != innerBeanFactories->end (); ++i) {

                        i->second->onAfterPropertiesSet (this);
                }
        }
}

/****************************************************************************/

void BeanFactory::notifyBeforePropertiesSet () const
{
        if (innerBeanFactories) {

                for (BeanFactoryMap::const_iterator i = innerBeanFactories->begin (); i != innerBeanFactories->end (); ++i) {

                        i->second->onBeforePropertiesSet (this);
                }
        }
}

/****************************************************************************/

std::string BeanFactory::toString () const
{
        std::string ret = "BeanFactory (";
        bool comma = false;

        if (attributes->containsKey (Attributes::ID_ARGUMENT, false)) {
                ret += "id=" + id;
                comma = true;
        }

        if (innerBeanFactories && !innerBeanFactories->empty ()) {
                if (comma) {
                        ret += ", ";
                }
                ret += "inner=" + ToStringHelper::toString (*innerBeanFactories);
        }

        ret += ")";
        return ret;
}

/****************************************************************************/

void BeanFactory::addInnerBeanFactory (BeanFactory *bf)
{
        if (!innerBeanFactories) {
                innerBeanFactories = new BeanFactoryMap ();
        }

        innerBeanFactories->operator[] (bf->getId ()) = bf;
        bf->setOuterBeanFactory (this);
}

/****************************************************************************/

BeanFactory *BeanFactory::getInnerBeanFactory (const std::string &myId) const
{
        if (innerBeanFactories) {

                BeanFactoryMap::const_iterator i = innerBeanFactories->find (myId);

                if (i != innerBeanFactories->end ()) {
                        return i->second;
                }
        }

        if (getOuterBeanFactory ()) {
                return getOuterBeanFactory ()->getInnerBeanFactory (myId);
        }

        return NULL;
}

/****************************************************************************/

Core::Variant BeanFactory::getInput () const
{
        if (flags & INPUT_LIST) {
                return Core::Variant (inputList);
        }
        else if (flags & INPUT_MAP) {
                return Core::Variant (inputMap);
        }

        return Core::Variant ();
}

/****************************************************************************/

MetaObject::Scope BeanFactory::getScope () const { return static_cast<MetaObject::Scope> (attributes->getInt (Attributes::SCOPE_ARGUMENT)); }

/****************************************************************************/

bool BeanFactory::fireMethod (Ptr<Wrapper::Handler> handler, Core::DebugContext *context, Core::VariantVector *list, bool initMethodErrorMessage) const
{
        std::string methodName;

        if (initMethodErrorMessage) {
                methodName = "init-method";
        }
        else {
                methodName = "globalIdAwareMethod";
        }

        try {
                handler->invoke (list);
        }
        catch (Core::Exception const &e) {
                if (context) {
                        context->addContext (e.getContext ());
                }
                dcCommit (context);
                dcError (context, "Invocation of " + methodName + " method in BeanFactory failed. Core::Exception has been thrown . ID : " + id);
                return false;
        }
        catch (std::exception const &e) {
                dcCommit (context);
                dcError (context, "Invocation of " + methodName + " in BeanFactory failed. ID : " + id + ". std::exception has been thrown : " + e.what ());
                return false;
        }
        catch (...) {
                dcCommit (context);
                dcError (context, "Invocation of " + methodName + " in BeanFactory failed. ID : " + id + ". Unknown exception has been thrown");
                return false;
        }

        return true;
}

/*##########################################################################*/

std::string ToStringHelper::toString (const BeanFactoryMap &bfm)
{
        std::string ret = "BeanFactoryMap (";

        for (BeanFactoryMap::const_iterator i = bfm.begin (); i != bfm.end (); ++i) {

                ret += i->second->toString () + ", ";
        }

        if (!bfm.empty ()) {
                ret.resize (ret.size () - 2);
        }

        return ret + ")";
}
}
