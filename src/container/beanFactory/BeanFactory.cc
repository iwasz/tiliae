/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lexical_cast.hpp>
#include "BeanFactory.h"
#include "metaStructure/model/meta/AbstractMeta.h"
#include "../../core/variant/Cast.h"
#include "../../beanWrapper/IBeanWrapper.h"
#include "BeanFactoryContext.h"
#include "Defs.h"

namespace Container {

/****************************************************************************/

// Takie same nazwy jak w ReflectionFactory, jednak aktualna fabryka może być innego typu.
static const char *CONSTRUCTOR_ARGS_KEY = "constructor-args";
static const char *CLASS_NAME = "class";

/****************************************************************************/

void BeanFactory::setAttributes (const Attributes &attributes)
{
        this->attributes = attributes;
        id = attributes.getString (ID_ARGUMENT);
}

/****************************************************************************/

Core::Variant BeanFactory::create (const Core::VariantMap &, Common::Context *context) const
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

                if ((forceSingleton || getSingleton ()) && !storedSingleton.isNone ()) {
                        return storedSingleton;
                }

                notifyBeforePropertiesSet ();

                assert (factory);
                assert (editor);

                Core::Variant output;
                Core::VariantMap factoryParams;
                Core::VariantVector list;
                Core::Variant cArgsEdited = Core::Variant (&list);

                // Trzeba sprawdzić, bo inaczej może się zamazać argument class (patrz test 24 myMap - class ustawione przez proxy).
                if (attributes.containsKey (CLASS_ARGUMENT)) {
                        factoryParams[CLASS_NAME] = Core::Variant (attributes.getString (CLASS_ARGUMENT));
                }

                if (cArgsEditor) {
                        cArgsEditor->convert (cArgs, &cArgsEdited, context);
                        factoryParams[CONSTRUCTOR_ARGS_KEY] = cArgsEdited;
                }

                output = factory->create (factoryParams, context);

                if (forceSingleton || getSingleton ()) {
                        storedSingleton = output;
                }

                if (output.isNone () || output.isNull ()) {
                        fatal (context, ContainerException, Common::UNDEFINED_ERROR, "BeanFactory::create : unable to create bean, factory returned none. ID = [" + id + "]");
                        return Core::Variant ();
                }

                editor->convert (input, &output, context);
                notifyAfterPropertiesSet ();

                // Uruchomienie metody init-method
                if (attributes.containsKey (INITMETHOD_ARGUMENT)) {
                        std::string initMethodName = attributes.getString (INITMETHOD_ARGUMENT);
                        assert (beanWrapper);
                        beanWrapper->setWrappedObject (output);
                        beanWrapper->get (initMethodName, context);
                }

                if (bfc) {
                        bfc->decNested ();
                }

                return output;
        }
        catch (TooDeepNestingException const &) {
                throw;
        }
        catch (Core::Exception &e) {
                fatal (context, ContainerException, Common::UNDEFINED_ERROR, "BeanFactory::create. Id : [" + id +
                                "] fullyInitialized : [" + boost::lexical_cast <std::string> (fullyInitialized) + "]. Exception caught : " +
                                e.what ());
        }

        return Core::Variant ();
}

/****************************************************************************/

bool BeanFactory::getSingleton () const
{
        return (static_cast <IMeta::Scope> (attributes.getInt (SCOPE_ARGUMENT)) == IMeta::SINGLETON);
}

/****************************************************************************/

void BeanFactory::onBeforePropertiesSet (BeanFactory const *notifier) const
{
        if (static_cast <IMeta::Scope> (attributes.getInt (SCOPE_ARGUMENT)) == IMeta::BEAN) {
                forceSingleton = true;
        }
}

/****************************************************************************/

void BeanFactory::onAfterPropertiesSet (BeanFactory const *notifier) const
{
        if (static_cast <IMeta::Scope> (attributes.getInt (SCOPE_ARGUMENT)) == IMeta::BEAN) {
                forceSingleton = false;

                if (!getSingleton ()) {
                        storedSingleton = Core::Variant ();
                }
        }
}

/****************************************************************************/

void BeanFactory::notifyAfterPropertiesSet () const
{
        foreach (BeanFactoryMap::value_type v, innerBeanFactories) {
                Ptr <BeanFactory> bf = v.second;
                bf->onAfterPropertiesSet (this);
        }
}

/****************************************************************************/

void BeanFactory::notifyBeforePropertiesSet () const
{
        foreach (BeanFactoryMap::value_type v, innerBeanFactories) {
                Ptr <BeanFactory> bf = v.second;
                bf->onBeforePropertiesSet (this);
        }
}

/****************************************************************************/

std::string BeanFactory::toString () const
{
        std::string ret = "BeanFactory (";
        bool comma = false;

        if (attributes.containsKey (ID_ARGUMENT)) {
                ret += "id=" + id;
                comma = true;
        }

        if (!innerBeanFactories.empty ()) {
                if (comma) { ret += ", "; }
                ret += "inner=" + ToStringHelper::toString (innerBeanFactories);
        }

        ret += ")";
        return ret;
}

/****************************************************************************/

void BeanFactory::addInnerBeanFactory (Ptr <BeanFactory> bf)
{
        innerBeanFactories[bf->getId ()] = bf;
        bf->setOuterBeanFactory (this);
}

/****************************************************************************/

Ptr <BeanFactory> BeanFactory::getInnerBeanFactory (const std::string &id) const
{
        BeanFactoryMap::const_iterator i = innerBeanFactories.find (id);

        if (i != innerBeanFactories.end ()) {
                return i->second;
        }

        if (getOuterBeanFactory ()) {
                return getOuterBeanFactory ()->getInnerBeanFactory (id);
        }

        return Ptr <BeanFactory> ();
}

/*##########################################################################*/


std::string ToStringHelper::toString (const BeanFactoryMap &bfm)
{
        std::string ret = "BeanFactoryMap (";

        foreach (BeanFactoryMap::value_type v, bfm) {
                ret += v.second->toString () + ", ";
        }

        if (!bfm.empty ()) {
                ret.resize (ret.size () - 2);
        }

        return ret + ")";
}

/****************************************************************************/

std::string ToStringHelper::toString (const BeanFactoryList &bfl)
{
        std::string ret = "BeanFactoryList (";

        foreach (Ptr <BeanFactory> b, bfl) {
                ret += b->toString () + ", ";
        }

        if (!bfl.empty ()) {
                ret.resize (ret.size () - 2);
        }

        return ret + ")";
}

/*##########################################################################*/

std::string BeanFactoryContainer::toString () const
{
        std::string ret = "BeanFactoryContainer (";

        if (factoryMap) {
                ret += ToStringHelper::toString (*factoryMap);
        }

//        if (singletons) {
//                ret += ", ";
//                ret += singletons->toString ();
//        }

        ret += ")";
        return ret;
}

/****************************************************************************/

void BeanFactoryContainer::reset ()
{
        factoryMap->clear ();
}

/****************************************************************************/

Core::Variant BeanFactoryContainer::getBean (const std::string &name, const Core::VariantMap &singletons) const
{
        /*
         * TODO sprawdz, czy pierwszy znak to nir jest @ lub &. Jesli tak, to wyciagnij factory lub editor
                Ptr <BeanFactory> fact = factoryMap.get (name);
                return fact->getFactory ();
                return fact->getEditor ();
         */

        BeanFactoryContext context;

        Core::VariantMap::const_iterator i = this->singletons->find (name);

        if (i != this->singletons->end ()) {
                return i->second;
        }

        BeanFactoryMap::const_iterator j = factoryMap->find (name);
        Core::Variant ret;

        if (j != factoryMap->end ()) {
                Ptr <BeanFactory> fact = j->second;
                assert (fact);
                ret = fact->create (singletons, &context);
        }
        else {
                throw ContainerException ("BeanFactoryContainer::getBean : can't find definition of bean [" + name + "].");
        }

        if (ret.isNone ()) {
                throw ContainerException ("BeanFactoryContainer::getBean : " + context.getMessage ());
        }

        return ret;
}

/****************************************************************************/

bool BeanFactoryContainer::containsBean (const std::string &name) const
{
        return (singletons->find (name) != singletons->end ()) || (factoryMap->find (name) != factoryMap->end ());
}

/****************************************************************************/

void BeanFactoryContainer::addSingleton (const std::string &key, const Core::Variant &singleton)
{
        singletons->operator[] (key) = singleton;
}

/****************************************************************************/

Ptr <BeanFactory> BeanFactoryContainer::getBeanFactory (const std::string &id, Ptr <BeanFactory> innerBean) const
{
        Ptr <BeanFactory> ret;

        if (innerBean) {
                ret = innerBean->getInnerBeanFactory (id);
        }

        if (!ret) {
                BeanFactoryMap::const_iterator j = factoryMap->find (id);
                ret = (j == factoryMap->end ()) ? (Ptr <BeanFactory> ()) : (j->second);
        }

        if (!ret && getLinked ()) {
                ret = getLinked ()->getBeanFactory (id);

                if (!ret) {
                        throw ContainerException ("Container does not have any BeanFactory with name [" + id + "].");
                }
        }

        return ret;
}

}
