/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ParentService.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/Exceptions.h"
#include "../../../core/string/String.h"
#include <cassert>

namespace Container {

using namespace Core;

bool ParentService::onMetaBegin (IMeta *child)
{
        if (!child->containsAttribute (PARENT_ARGUMENT)) {
                return NULL;
        }

        std::string parentName = child->getParent ();
        MetaContainer *container = getContext ()->getMetaContainer ();
        Ptr <IMeta> parent = container->get (parentName);

        if (!parent) {
                throw NoSuchBeanException ("NoSuchBeanException @ ParentService::onMeta id=" + parentName);
        }

        child->setParentMeta (parent.get ());
        return true;
}

/****************************************************************************/

// Kopiuje tylko atrybuty, meta-info i constructor-args.
IMeta *ParentService::onMeta (IMeta *child)
{
        if (!child->containsAttribute (PARENT_ARGUMENT)) {
                return NULL;
        }

        std::string parentName = child->getParent ();
        MetaContainer *container = getContext ()->getMetaContainer ();
        Ptr <IMeta> parent = container->get (parentName);

        if (!parent) {
                throw NoSuchBeanException ("NoSuchBeanException @ ParentService::onMeta id=" + parentName);
        }

        // TODO oznacz child jako "załatwiony", żeby nie był obsłużony jeszcze raz.
//        copyData (parent.get (), child);
        return parent.get ();
}

/****************************************************************************/

bool ParentService::onMappedMetaBegin (MappedMeta *data)
{
        IMeta *source = onMeta (data);

        if (!source) {
                return false;
        }
//
//        // Kopiuj pola
//        MappedMeta *dynSource = dynamic_cast <MappedMeta *> (source);
//        assert (dynSource);
//
//        // TODO zrobić to w miejscu, to znaczy jakąćMetode addFront czy cos.
//        MapElemList tmp = data->getFieldsAsList ();
//        data->clearFields ();
//        data->addFields (dynSource->getFieldsAsList ());
//        data->addFields (tmp);

#if 0
        std::cerr << data->getId() << " " << source->getInnerMetas().containsKey ("ID_0") << std::endl;
#endif

        data->addInnerMetaList (source->getInnerMetas());

        return true;
}

/****************************************************************************/

bool ParentService::onIndexedMetaBegin (IndexedMeta *data)
{
//        IMeta *source = onMeta (data);
//
//        if (!source) {
//                return false;
//        }
//
//        IndexedMeta *dynSource = dynamic_cast <IndexedMeta *> (source);
//        assert (dynSource);
//        data->addFields (dynSource->getFields ());
        return true;
}

/****************************************************************************/

void ParentService::copyData (IMeta *parent, IMeta *child)
{
        assert (parent);
        assert (child);

//        copyAttributes (parent, child);
//        copyConstructorArgs (parent, child);
}

/****************************************************************************/

//void ParentService::copyAttributes (IMeta *parent, IMeta *child)
//{
//        assert (parent);
//        assert (child);
//        Attributes tmp = parent->getAttributes ();
//
//        // Nie chcemy kopiowac id i parent
//        tmp.removeAttribute (ID_ARGUMENT);
//        tmp.removeAttribute (PARENT_ARGUMENT);
//
//        // Skopiuj (prawie) wszystkie elementy z attributes z parent
//        child->addAttributes (tmp);
//}

/****************************************************************************/

void ParentService::copyConstructorArgs (IMeta *parent, IMeta *child)
{
        assert (parent);
        assert (child);

        // TODO Zrobić metodę addFrontConstructorArgs i jej użyć tu .
        ListElemList tmp  = child->getConstructorArgs ();
        child->setConstructorArgs (parent->getConstructorArgs ());
        child->addConstructorArgs (tmp);
}

}
