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

bool ParentService::onMetaBegin (MetaObject *child)
{
        if (!child->containsAttribute (Attributes::PARENT_ARGUMENT)) {
                return NULL;
        }

        std::string parentName = child->getParent ();
        MetaContainer *container = getContext ()->getMetaContainer ();
        MetaObject *parent = container->get (parentName);

        if (!parent) {
                throw NoSuchBeanException ("ParentService::onMetaBegin : Wrong 'parent' value. There is no bean with id =" + parentName);
        }

        if ((child->getType () == MetaObject::INDEXED && parent->getType () == MetaObject::MAPPED) ||
            (child->getType () == MetaObject::MAPPED && parent->getType () == MetaObject::INDEXED)) {
                throw ConfigurationException ("ParentService::onMetaBegin : parent is MAPPED and child is INDEXED or vice versa.");
        }

        // TODO wywalić dynamic cast, jak MetaObject nie będzie polimorficzny.
        child->setParentMeta (dynamic_cast <MetaObject *> (parent));
        return true;
}

}
