/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "container/beanFactory/BeanFactory.h"

#include <boost/lexical_cast.hpp>
#include "container/metaStructure/model/MetaObject.h"
#include "core/variant/Cast.h"
#include "beanWrapper/IBeanWrapper.h"
#include "BeanFactoryContext.h"
#include "container/Defs.h"
#include "factory/ReflectionFactory.h"
#include "BeanFactoryContainer.h"

namespace Container {

/****************************************************************************/

BeanFactory::BeanFactory (BeanFactoryContainer *c) :
        flags (0x00),
        cArgs (NULL),
        attributes (NULL),
        cArgsEditor (NULL),
        editor (NULL),
        factory (NULL),
        beanWrapper (NULL),
        outerBeanFactory (NULL),
        innerBeanFactories (NULL),
        container (c)
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
                BeanFactoryContext *bfc = dynamic_cast <BeanFactoryContext *> (context);

                if (bfc) {
                        bfc->incNested ();

                        if (bfc->getNested () > MAX_BEAN_NESTING) {
                                // Nie bawimy się w fatale, bo to jest tak krytyczmny bład, że trzeba przerwać działanie programu.
                                throw TooDeepNestingException ("BeanFactory::create. Id : [" + id + "]. Too deep "
                                      "bean nesting. Max level of nested beans is : " + boost::lexical_cast <std::string> (MAX_BEAN_NESTING));
                        }
                }

                if ((flags & FORCE_SINGLETON || getSingleton ()) && !storedSingleton.isNone ()) {
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

                if (output.isNone ()) {
                        dcCommit (context);
                        dcError (context,  "Factory in BeanFactory failed. ID : " + id);
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
                        std::string initMethodName = getStringAttribute (Attributes::INITMETHOD_ARGUMENT);
                        assert (beanWrapper);
                        beanWrapper->setWrappedObject (output);
                        beanWrapper->get (initMethodName, &err, context);

                        if (err) {
                                dcCommit (context);
                                dcError (context, "Invocation of init method in BeanFactory failed. ID : " + id);
                                return Core::Variant ();
                        }
                }

                if (bfc) {
                        bfc->decNested ();
                }

                if (flags & FORCE_SINGLETON || getSingleton ()) {
                        storedSingleton = output;
                }

                if (getSingleton ()) {
                        Core::IAllocator *memoryAllocator = container->getMemoryAllocator ();
                        char *idCopy = (char *)memoryAllocator->malloc (id.length () + 1);
                        strcpy (idCopy, id.c_str ());

                        // Dodaj do mapy singletonów
                        container->addSingleton (idCopy, output);

                        BeanFactoryMap *map = &container->getBeanFactoryMap();
                        map->erase (id);

                        // Dodaj singleton
                        delete this;
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
                dcError (context, "BeanFactory::create. Id : [" + id +
                                "] fullyInitialized : [" + boost::lexical_cast <std::string> (flags & FULLY_INITIALIZED) + "]. Exception caught : " +
                                e.what ());
        }

        return Core::Variant ();
}

/****************************************************************************/

bool BeanFactory::getSingleton () const
{
        return (static_cast <MetaObject::Scope> (attributes->getInt (Attributes::SCOPE_ARGUMENT)) == MetaObject::SINGLETON);
}

/****************************************************************************/

void BeanFactory::onBeforePropertiesSet (BeanFactory const *notifier) const
{
        if (static_cast <MetaObject::Scope> (attributes->getInt (Attributes::SCOPE_ARGUMENT)) == MetaObject::BEAN) {
                flags |= FORCE_SINGLETON;
        }
}

/****************************************************************************/

void BeanFactory::onAfterPropertiesSet (BeanFactory const *notifier) const
{
        if (static_cast <MetaObject::Scope> (attributes->getInt (Attributes::SCOPE_ARGUMENT)) == MetaObject::BEAN) {
                flags &= ~FORCE_SINGLETON;

                if (!getSingleton ()) {
                        storedSingleton = Core::Variant ();
                }
        }
}

/****************************************************************************/

void BeanFactory::notifyAfterPropertiesSet () const
{
        if (innerBeanFactories) {

                for (BeanFactoryMap::const_iterator i = innerBeanFactories->begin ();
                     i  != innerBeanFactories->end ();
                     ++i) {

                        i->second->onAfterPropertiesSet (this);
                }
        }
}

/****************************************************************************/

void BeanFactory::notifyBeforePropertiesSet () const
{
        if (innerBeanFactories) {

                for (BeanFactoryMap::const_iterator i = innerBeanFactories->begin ();
                     i  != innerBeanFactories->end ();
                     ++i) {

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
                if (comma) { ret += ", "; }
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

/*##########################################################################*/

std::string ToStringHelper::toString (const BeanFactoryMap &bfm)
{
        std::string ret = "BeanFactoryMap (";

        for (BeanFactoryMap::const_iterator i = bfm.begin ();
             i  != bfm.end ();
             ++i) {

                ret += i->second->toString () + ", ";
        }

        if (!bfm.empty ()) {
                ret.resize (ret.size () - 2);
        }

        return ret + ")";
}

}
