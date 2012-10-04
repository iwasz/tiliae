/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BeanFactoryContainer.h"
#include "core/variant/Cast.h"
#include "BeanFactoryContext.h"
#include "container/Defs.h"
#include "reflection/Manager.h"
#include "reflection/model/Class.h"
#include "InternalSingletons.h"

namespace Container {

BeanFactoryContainer::BeanFactoryContainer () :
                internalSingletons (NULL),
                linked (NULL),
                conversionMethodEditor (NULL),
                typeEditor (NULL)
{
}

/****************************************************************************/

BeanFactoryContainer::~BeanFactoryContainer ()
{
        /*
         * Kasuj wszystko co zostało. Singletony i ich inner beany kasują się same i usuwają z factoryMap,
         * więc żadne inne dodatkowe sprawdzenia nie są potrzebne.
         */
        for (BeanFactoryMap::iterator i = factoryMap.begin (); i  != factoryMap.end (); ++i) {
                BeanFactory * bf = i->second;
                 delete bf;
        }

        for (SparseVariantMap::iterator i = singletons.begin (); i != singletons.end (); ++i) {
                Core::Variant &v = i->second;
                deleteSingleton (v);
        }

        for (Core::VariantVector::iterator i = additionalSingletons.begin (); i != additionalSingletons.end (); ++i) {
                deleteSingleton (*i);
        }

        if (!linked) {
                delete internalSingletons;
        }
}

/****************************************************************************/

void BeanFactoryContainer::deleteSingleton (Core::Variant &v)
{
        if (v.getType () != Core::Variant::POINTER &&
            v.getType () != Core::Variant::POINTER_CONST &&
            v.getType () != Core::Variant::OBJECT &&
            v.getType () != Core::Variant::OBJECT_CONST) {
                return;
        }

        Reflection::Class *cls = Reflection::Manager::classForType (v.getTypeInfo ());

        if (cls) {
                cls->destruct (&v);
        }
}

/****************************************************************************/

std::string BeanFactoryContainer::toString () const
{
        std::string ret = "BeanFactoryContainer (" + ToStringHelper::toString (factoryMap);
        ret += ")";
        return ret;
}

/****************************************************************************/

void BeanFactoryContainer::reset ()
{
        factoryMap.clear ();
}

/****************************************************************************/

Core::Variant BeanFactoryContainer::getBean (const std::string &name) const
{
        Core::Variant ret = getSingletonNoThrow (name.c_str ());

        if (!ret.isNone ()) {
                return ret;
        }

        BeanFactoryContext context;
        BeanFactoryMap::const_iterator j = factoryMap.find (name);

        if (j != factoryMap.end ()) {
                BeanFactory *fact = j->second;
                assert (fact);
                ret = fact->create (Core::VariantMap (), &context);
        }
        else {
                if (linked) {
                        return linked->getBean (name);
                }
        }

        if (ret.isNone ()) {
                throw ContainerException (context, "BeanFactoryContainer::getBean : can't find definition of bean [" + name + "].");
        }

        return ret;}

/****************************************************************************/

Core::Variant BeanFactoryContainer::getSingleton (const char *name) const
{
        Core::Variant ret = getSingletonNoThrow (name);

        if (ret.isNone ()) {
                throw ContainerException ("BeanFactoryContainer::getSingleton : can't find definition of bean [" + std::string (name) + "].");
        }

        return ret;
}

/****************************************************************************/

Core::Variant BeanFactoryContainer::getSingletonNoThrow (const char *name) const
{
        SparseVariantMap::const_iterator i;
        if ((i = singletons.find (name)) != singletons.end ()) {
                return i->second;
        }

        Core::Variant v = internalSingletons->get (name);

        if (!v.isNone ()) {
                return v;
        }

        if (linked) {
                return linked->getSingleton (name);
        }

        return Core::Variant ();
}

/****************************************************************************/

bool BeanFactoryContainer::containsBean (const std::string &name) const
{
        bool ret = (singletons.find (name.c_str()) != singletons.end ()) || (factoryMap.find (name) != factoryMap.end ());

        if (!ret && linked) {
                return linked->containsBean (name);
        }

        return ret;
}

/****************************************************************************/

void BeanFactoryContainer::addSingleton (const char *key, const Core::Variant &singleton)
{
        if (key) {
                singletons.operator[] (key) = singleton;
        }
        else {
                additionalSingletons.push_back (singleton);
        }
}

/****************************************************************************/

BeanFactory *BeanFactoryContainer::getBeanFactory (const std::string &id, BeanFactory *innerBean) const
{
        BeanFactory *ret = NULL;

        if (innerBean) {
                ret = innerBean->getInnerBeanFactory (id);
        }

        if (!ret) {
                BeanFactoryMap::const_iterator j = factoryMap.find (id);
                ret = (j == factoryMap.end ()) ? (NULL) : (j->second);
        }

        if (!ret && getLinked ()) {
                ret = getLinked ()->getBeanFactory (id);
        }

        return ret;
}

/****************************************************************************/

void BeanFactoryContainer::addConversion (std::type_info const &type, Editor::StringFactoryMethodEditor::ConversionFunctionPtr function)
{
        assert (internalSingletons->mainMethodConversionEditor);
        Editor::StringFactoryMethodEditor *conversionMethodEditor = dynamic_cast <Editor::StringFactoryMethodEditor *> (internalSingletons->mainMethodConversionEditor);
        conversionMethodEditor->addConversion (type, function);
}
/****************************************************************************/

void BeanFactoryContainer::addConversion (std::type_info const &type, Editor::IEditor *editor)
{
        assert (internalSingletons->mainTypeEditor);
        Editor::TypeEditor *typeEditor = dynamic_cast <Editor::TypeEditor *> (internalSingletons->mainTypeEditor);
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), type, editor));
}

}
