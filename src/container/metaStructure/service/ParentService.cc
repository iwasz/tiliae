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
#include "../../common/Attributes.h"

namespace Container {

using namespace Core;

bool ParentService::onMetaBegin (MetaObject const *child)
{
        if (!child->containsAttribute (Attributes::PARENT_ARGUMENT)) {
                return NULL;
        }

        std::string parentName = child->getParent ();
        MetaContainer *container = getContext ()->getMetaContainer ();
        MetaObject const *parent = container->get (parentName);

        if (!parent) {
                throw NoSuchBeanException ("ParentService::onMetaBegin : Wrong 'parent' value. There is no bean with id =" + parentName);
        }

        if ((child->getType () == MetaObject::INDEXED && parent->getType () == MetaObject::MAPPED) ||
            (child->getType () == MetaObject::MAPPED && parent->getType () == MetaObject::INDEXED)) {
                throw ConfigurationException ("ParentService::onMetaBegin : parent is MAPPED and child is INDEXED or vice versa.");
        }

        // TODO to jest bardzo brzydko! Najlepiej, zeby metastruktura miała poustawiane parentu już przed tworzeniem BeanFactoryContainer.
        const_cast <MetaObject *> (child)->setParentMeta (parent);
        return true;
}

}
