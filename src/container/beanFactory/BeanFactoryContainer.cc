/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BeanFactoryContainer.h"
#include "variant/Cast.h"
#include "BeanFactoryContext.h"
#include "Defs.h"
#include "../../reflection/Manager.h"
#include "../../reflection/model/Class.h"
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
        for (BeanFactoryMap::iterator i = factoryMap.begin ();
             i  != factoryMap.end ();
             ++i) {

                delete i->second;
        }

        for (SparseVariantMap::iterator i = singletons.begin (); i != singletons.end (); ++i) {
                Core::Variant &v = i->second;

                if (v.getType () != Core::Variant::POINTER &&
                    v.getType () != Core::Variant::POINTER_CONST &&
                    v.getType () != Core::Variant::OBJECT &&
                    v.getType () != Core::Variant::OBJECT_CONST) {
                        continue;
                }

                Reflection::Class *cls = Reflection::Manager::classForType (v.getTypeInfo ());

                if (cls) {
                        cls->destruct (&v);
                }
        }

        delete internalSingletons;
}

/****************************************************************************/

std::string BeanFactoryContainer::toString () const
{
        std::string ret = "BeanFactoryContainer (" + ToStringHelper::toString (factoryMap);

//        if (singletons) {
//                ret += ", ";
//                ret += singletons.toString ();
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

Core::Variant BeanFactoryContainer::getBean (const std::string &name) const
{
        BeanFactoryContext context;

        SparseVariantMap::const_iterator i = this->singletons.find (name.c_str ());

        if (i != this->singletons.end ()) {
                return i->second;
        }

        BeanFactoryMap::const_iterator j = factoryMap.find (name);
        Core::Variant ret;

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

        return ret;
}

/****************************************************************************/

Core::Variant BeanFactoryContainer::getSingleton (const char *name) const
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

        throw ContainerException ("BeanFactoryContainer::getSingleton : can't find definition of bean [" + std::string (name) + "].");
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
        singletons.operator[] (key) = singleton;
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

}
