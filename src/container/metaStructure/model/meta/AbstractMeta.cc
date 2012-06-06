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

//const char *ABSTRACT_ARGUMENT = "abstract";
//const char *LAZYINIT_ARGUMENT = "lazyInit";
//const char *ID_ARGUMENT = "id";
//const char *CLASS_ARGUMENT = "c";
//const char *PARENT_ARGUMENT = "parent";
//const char *DEPENDSON_ARGUMENT = "dependsOn";
//const char *INITMETHOD_ARGUMENT = "initMethod";
//const char *FACTORY_ARGUMENT = "factory";
//const char *EDITOR_ARGUMENT = "editor";
//const char *DESCRIPTION_ARGUMENT = "description";
//const char *OUTER_ARGUMENT = "outer";
//const char *SCOPE_ARGUMENT = "scope";

/*##########################################################################*/

AbstractMeta::AbstractMeta () : parent (NULL),
                                attributes (boost::make_shared <Attributes> ()),
                                constructorArgs (NULL),
                                innerMetas (NULL)
{
        setScope (SINGLETON);
}

/****************************************************************************/

AbstractMeta::~AbstractMeta ()
{
        if (constructorArgs) {
                for (DataVector::iterator i = constructorArgs->begin (); i != constructorArgs->end (); ++i) {
                        delete *i;
                }
        }

        delete constructorArgs;
        delete innerMetas;
}

/****************************************************************************/

void AbstractMeta::initConstructorArgs ()
{
        if (!constructorArgs) {
                constructorArgs = new DataVector;
        }
}

/****************************************************************************/

void AbstractMeta::initInnerMetas ()
{
        if (!innerMetas) {
                innerMetas = new MetaMap;
        }
}

/****************************************************************************/

void AbstractMeta::setInnerMetas (const MetaMap &m)
{
        initInnerMetas ();
        *innerMetas = m;
}

/****************************************************************************/

void AbstractMeta::addInnerMeta (IMeta *m)
{
        initInnerMetas ();
        innerMetas->operator [] (m->getId ()) = m;
}

/****************************************************************************/

void AbstractMeta::addInnerMetaList (const MetaMap &m)
{
        initInnerMetas ();
        std::copy (m.begin (), m.end (), std::inserter (*innerMetas, innerMetas->end ()));
}

/****************************************************************************/

//void AbstractMeta::addConstructorArgs (const ListElemList &constructorArgs)
//{
//        initConstructorArgs ();
//        std::copy (constructorArgs.begin (), constructorArgs.end (), std::back_inserter (*this->constructorArgs));
//}
//
///****************************************************************************/
//
//void AbstractMeta::setConstructorArgs (const ListElemList &constructorArgs)
//{
//        initConstructorArgs ();
//        *this->constructorArgs = constructorArgs;
//}

/****************************************************************************/

void AbstractMeta::addConstructorArg (IData *elem)
{
        initConstructorArgs ();
        constructorArgs->push_back (elem);
}

/****************************************************************************/

DataVector AbstractMeta::getConstructorArgs () const
{
        if (parent) {
                DataVector ret = parent->getConstructorArgs ();

                if (constructorArgs) {
                        std::copy (constructorArgs->begin (), constructorArgs->end (), std::back_inserter (ret));
                }

                return ret;
        }

        if (constructorArgs) {
                return *constructorArgs;
        }

        return DataVector ();
}

/****************************************************************************/

MetaMap AbstractMeta::getInnerMetas () const
{
        if (parent) {
                MetaMap ret = parent->getInnerMetas ();

                if (innerMetas) {
                        std::copy (innerMetas->begin (), innerMetas->end (), std::inserter (ret, ret.end ()));
                }

#if 0
                std::cerr << getId () << ", parent == true, inner.size () == " << ret.size () << std::endl;
#endif

                return ret;
        }

#if 0
        std::cerr << getId () << ", parent == false, inner.size () == " << innerMetas.size () << std::endl;
#endif

        if (innerMetas) {
                return *innerMetas;
        }

        return MetaMap ();
}

}
