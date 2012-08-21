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

namespace Container {

BeanFactoryContainer::BeanFactoryContainer (SparseVariantMap *s) : singletons (s), linked (NULL)
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
        for (BeanFactoryMap::iterator i = factoryMap.begin ();
             i  != factoryMap.end ();
             ++i) {

                delete i->second;
        }
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

Core::Variant BeanFactoryContainer::getBean (const std::string &name) const
{
        BeanFactoryContext context;

        SparseVariantMap::const_iterator i = this->singletons->find (name);

        if (i != this->singletons->end ()) {
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

Core::Variant BeanFactoryContainer::getSingleton (const std::string &name) const
{
        if (!singletons) {
                return Core::Variant ();
        }

        SparseVariantMap::const_iterator i;
        if ((i = singletons->find (name)) != singletons->end ()) {
                return i->second;
        }

        if (linked) {
                return linked->getSingleton (name);
        }

        throw ContainerException ("BeanFactoryContainer::getSingleton : can't find definition of bean [" + name + "].");
}

/****************************************************************************/

bool BeanFactoryContainer::containsBean (const std::string &name) const
{
        bool ret = (singletons->find (name) != singletons->end ()) || (factoryMap.find (name) != factoryMap.end ());

        if (!ret && linked) {
                return linked->containsBean (name);
        }

        return ret;
}

/****************************************************************************/

void BeanFactoryContainer::addSingleton (const std::string &key, const Core::Variant &singleton)
{
        singletons->operator[] (key) = singleton;
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
        assert (conversionMethodEditor);
        conversionMethodEditor->addConversion (type, function);
}

}
