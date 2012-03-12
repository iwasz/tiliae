/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <iterator>
#include "AbstractMeta.h"

namespace Container {

const char *ABSTRACT_ARGUMENT = "abstract";
const char *LAZYINIT_ARGUMENT = "lazyInit";
const char *ID_ARGUMENT = "id";
const char *CLASS_ARGUMENT = "class";
const char *PARENT_ARGUMENT = "parent";
const char *DEPENDSON_ARGUMENT = "dependsOn";
const char *INITMETHOD_ARGUMENT = "initMethod";
const char *FACTORY_ARGUMENT = "factory";
const char *EDITOR_ARGUMENT = "editor";
const char *DESCRIPTION_ARGUMENT = "description";
const char *OUTER_ARGUMENT = "outer";
const char *SCOPE_ARGUMENT = "scope";

/*##########################################################################*/

void AbstractMeta::addInnerMeta (Ptr <IMeta> m)
{
        m->setOuterMeta (this);
        innerMetas[m->getId ()] = m;
}

/****************************************************************************/

Ptr <IMeta> AbstractMeta::get (const std::string &key) const
{
        MetaMap::const_iterator i = innerMetas.find (key);

        if (i == innerMetas.end () && getOuterMeta ()) {
                return getOuterMeta ()->get (key);
        }

        return (i == innerMetas.end ()) ? (Ptr <IMeta> ()) : (i->second);
}

/****************************************************************************/

void AbstractMeta::addInnerMetaList (const MetaMap &m)
{
        std::copy (m.begin (), m.end (), std::inserter (innerMetas, innerMetas.end ()));
}

/****************************************************************************/

void AbstractMeta::addConstructorArgs (const ListElemList &constructorArgs)
{
        std::copy (constructorArgs.begin (), constructorArgs.end (), std::back_inserter (this->constructorArgs));
}

/****************************************************************************/

//void AbstractMeta::addAttributes (const Attributes &attributes)
//{
//        this->attributes.addAttributes (attributes);
//}

/****************************************************************************/

ListElemList AbstractMeta::getConstructorArgs () const
{
        if (parent) {
                ListElemList ret = parent->getConstructorArgs ();
                std::copy (constructorArgs.begin (), constructorArgs.end (), std::back_inserter (ret));
                return ret;
        }

        return constructorArgs;
}

}
