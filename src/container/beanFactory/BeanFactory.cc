/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BeanFactory.h"

#include <boost/lexical_cast.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include "metaStructure/model/MetaObject.h"
#include "../../core/variant/Cast.h"
#include "IBeanWrapper.h"
#include "BeanFactoryContext.h"
#include "Defs.h"

namespace Container {

// Takie same nazwy jak w ReflectionFactory, jednak aktualna fabryka może być innego typu.
static const char *CONSTRUCTOR_ARGS_KEY = "constructor-args";
static const char *CLASS_NAME = "class";

/****************************************************************************/

BeanFactory::BeanFactory () :
        flags (0x00),
        id (NULL),
        cArgs (NULL),
        cArgsEditor (NULL),
        editor (NULL),
        factory (NULL),
        beanWrapper (NULL),
        outerBeanFactory (NULL),
        innerBeanFactories (NULL)
{
}

/****************************************************************************/

BeanFactory::~BeanFactory ()
{
        if (innerBeanFactories) {
                BeanFactoryMap *map = static_cast <BeanFactoryMap *> (innerBeanFactories);
                delete map;
        }

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
}

/****************************************************************************/

void BeanFactory::setAttributes (Ptr <Attributes> attributes)
{
        this->attributes = attributes;
        id = &(attributes->getString (Attributes::ID_ARGUMENT, false));
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
                                throw TooDeepNestingException ("BeanFactory::create. Id : [" + *id + "]. Too deep "
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
                Core::VariantMap factoryParams;
                Core::VariantVector list;
                Core::Variant cArgsEdited = Core::Variant (&list);

                // Trzeba sprawdzić, bo inaczej może się zamazać argument class (patrz test 24 myMap - class ustawione przez proxy).
                if (attributes->containsKey (Attributes::CLASS_ARGUMENT)) {
                        factoryParams[CLASS_NAME] = Core::Variant (attributes->getString (Attributes::CLASS_ARGUMENT));
                }

                bool err = false;
                dcBegin (context);

                if (cArgsEditor) {
                        if (!cArgsEditor->convert (Core::Variant (cArgs), &cArgsEdited, context)) {
                                dcCommit (context);
                                dcError (context, "Constructor args editor failed. ID : " + *id);
                                return Core::Variant ();
                        }

                        factoryParams[CONSTRUCTOR_ARGS_KEY] = cArgsEdited;
                }

                dcRollback (context);
                dcBegin (context);

                output = factory->create (factoryParams, context);

                if (output.isNone ()) {
                        dcCommit (context);
                        dcError (context,  "Factory in BeanFactory failed. ID : " + *id);
                        return Core::Variant ();
                }

                if (flags & FORCE_SINGLETON || getSingleton ()) {
                        storedSingleton = output;
                }
                else {
                        // Jeśli scope nie SINGLETON i nie BEAN, to konwertujemy prototypy na Ptr.
                        output = Core::convertVariantToSmart (output);
                }

                if (output.isNull ()) {
                        dcCommit (context);
                        dcError (context, "BeanFactory::create : unable to create bean, factory returned none. ID = [" + *id + "]");
                        return Core::Variant ();
                }

                dcRollback (context);
                dcBegin (context);

                if (!editor->convert (getInput (), &output, context)) {
                        dcCommit (context);
                        dcError (context, "Editor in BeanFactory failed. ID : " + *id);
                        return Core::Variant ();
                }

                dcRollback (context);
                dcBegin (context);

                notifyAfterPropertiesSet ();

                // Uruchomienie metody init-method
                if (attributes->containsKey (Attributes::INITMETHOD_ARGUMENT)) {
                        std::string initMethodName = attributes->getString (Attributes::INITMETHOD_ARGUMENT);
                        assert (beanWrapper);
                        beanWrapper->setWrappedObject (output);
                        beanWrapper->get (initMethodName, &err, context);

                        if (err) {
                                dcCommit (context);
                                dcError (context, "Invocation of init method in BeanFactory failed. ID : " + *id);
                                return Core::Variant ();
                        }
                }

                if (bfc) {
                        bfc->decNested ();
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
                dcError (context, "BeanFactory::create. Id : [" + *id +
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

                BeanFactoryMap *map = static_cast <BeanFactoryMap *> (innerBeanFactories);

                for (BeanFactoryMap::nth_index <1>::type::iterator i = map->get<1> ().begin ();
                     i  != map->get<1> (). end ();
                     ++i) {

                        (*i)->onAfterPropertiesSet (this);
                }
        }
}

/****************************************************************************/

void BeanFactory::notifyBeforePropertiesSet () const
{
        if (innerBeanFactories) {

                BeanFactoryMap *map = static_cast <BeanFactoryMap *> (innerBeanFactories);

                for (BeanFactoryMap::nth_index <1>::type::iterator i = map->get<1> ().begin ();
                     i  != map->get<1> (). end ();
                     ++i) {

                        (*i)->onBeforePropertiesSet (this);
                }
        }
}

/****************************************************************************/

std::string BeanFactory::toString () const
{
        std::string ret = "BeanFactory (";
        bool comma = false;

        if (attributes->containsKey (Attributes::ID_ARGUMENT, false)) {
                ret += "id=" + *id;
                comma = true;
        }

        BeanFactoryMap *map = static_cast <BeanFactoryMap *> (innerBeanFactories);

        if (map && !map->empty ()) {
                if (comma) { ret += ", "; }
                ret += "inner=" + ToStringHelper::toString (*map);
        }

        ret += ")";
        return ret;
}

/****************************************************************************/

void BeanFactory::addInnerBeanFactory (Ptr <BeanFactory> bf)
{
        if (!innerBeanFactories) {
                innerBeanFactories = new BeanFactoryMap ();
        }

        BeanFactoryMap *map = static_cast <BeanFactoryMap *> (innerBeanFactories);
        map->insert (bf);
        bf->setOuterBeanFactory (this);
}

/****************************************************************************/

Ptr <BeanFactory> BeanFactory::getInnerBeanFactory (const std::string &id) const
{
        if (innerBeanFactories) {

                BeanFactoryMap *map = static_cast <BeanFactoryMap *> (innerBeanFactories);

                BeanFactoryMap::nth_index <0>::type::iterator i = map->get<0> ().find (id);

                if (i != map->get<0> ().end ()) {
                        return *i;
                }
        }

        if (getOuterBeanFactory ()) {
                return getOuterBeanFactory ()->getInnerBeanFactory (id);
        }

        return Ptr <BeanFactory> ();
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

        for (BeanFactoryMap::nth_index <1>::type::iterator i = bfm.get<1> ().begin ();
             i  != bfm.get<1> (). end ();
             ++i) {

                ret += (*i)->toString () + ", ";
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

BeanFactoryContainer::BeanFactoryContainer (Core::VariantMap *s/*, Core::IAllocator *a*/) : singletons (s), linked (NULL)//, allocator (a)
{
        assert (s);
        conversionMethodEditor = vcast <Editor::StringFactoryMethodEditor *> (s->operator [](MAIN_METHOD_CONVERSION_EDITOR));
        typeEditor = vcast <Editor::TypeEditor *> (s->operator [](MAIN_TYPE_EDITOR));
        assert (conversionMethodEditor);
        assert (typeEditor);
}

/****************************************************************************/

BeanFactoryContainer::~BeanFactoryContainer ()
{
//        delete allocator;
}

/****************************************************************************/

std::string BeanFactoryContainer::toString () const
{
        std::string ret = "BeanFactoryContainer (" + ToStringHelper::toString (factoryMap);

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
        factoryMap.clear ();
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

        BeanFactoryMap::nth_index <0>::type::iterator j = factoryMap.get<0> ().find (name);
        Core::Variant ret;

        if (j != factoryMap.end ()) {
                Ptr <BeanFactory> fact = *j;
                assert (fact);
                ret = fact->create (singletons, &context);
        }
        else {
                throw ContainerException (context, "BeanFactoryContainer::getBean : can't find definition of bean [" + name + "].");
        }

        if (ret.isNone ()) {
                throw ContainerException (context, "BeanFactoryContainer::getBean" );
        }

        return ret;
}

/****************************************************************************/

bool BeanFactoryContainer::containsBean (const std::string &name) const
{
        return (singletons->find (name) != singletons->end ()) || (factoryMap.find (name) != factoryMap.end ());
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
                BeanFactoryMap::nth_index <0>::type::iterator j = factoryMap.get<0> ().find (id);
                ret = (j == factoryMap.get<0> ().end ()) ? (Ptr <BeanFactory> ()) : (*j);
        }

        if (!ret && getLinked ()) {
                ret = getLinked ()->getBeanFactory (id);

                if (!ret) {
                        throw ContainerException ("Container does not have any BeanFactory with name [" + id + "].");
                }
        }

        return ret;
}

/****************************************************************************/

void BeanFactoryContainer::addConversion (std::type_info const &type, Editor::StringFactoryMethodEditor::ConversionFunctionPtr function)
{
        assert (conversionMethodEditor);
        conversionMethodEditor->addConversion (type, function);
}

}
