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

bool ParentService::onMetaBegin (IMeta *child)
{
        if (!child->containsAttribute (Attributes::PARENT_ARGUMENT)) {
                return NULL;
        }

        std::string parentName = child->getParent ();
        MetaContainer *container = getContext ()->getMetaContainer ();
        IMeta *parent = container->get (parentName);

        if (!parent) {
                throw NoSuchBeanException ("NoSuchBeanException @ ParentService::onMeta id=" + parentName);
        }

        if ((child->getType () == IMeta::INDEXED && parent->getType () == IMeta::MAPPED) ||
            (child->getType () == IMeta::MAPPED && parent->getType () == IMeta::INDEXED)) {
                throw ConfigurationException ("ParentService::onMetaBegin : parent is MAPPED and child is INDEXED or vice versa.");
        }

        // TODO wywalić dynamic cast, jak MetaObject nie będzie polimorficzny.
        child->setParentMeta (dynamic_cast <AbstractMeta *> (parent));
        return true;
}

}
