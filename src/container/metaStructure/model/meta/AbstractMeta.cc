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
#include <boost/algorithm/string/trim.hpp>
#include "../../../common/Exceptions.h"

namespace Container {

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

        if (innerMetas) {
                for (MetaMap::iterator i = innerMetas->begin (); i != innerMetas->end (); ++i) {
                        delete i->second;
                }
        }

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

        // Nie powinno się zdarzyć.
        if (boost::trim_copy (m->getId ()) == "") {
                throw ConfigurationException ("AbstractMeta::addInnerMeta : ID is empty. ID should be generated automatically or provided explicitly.");
        }

        if (getInnerMeta (m->getId ())) {
                throw ConfigurationException ("AbstractMeta::addInnerMeta : There is already a inner bean with ID [" + m->getId () + "].");
        }

        innerMetas->operator [] (m->getId ()) = m;
}

/****************************************************************************/

void AbstractMeta::addInnerMetaList (const MetaMap &m)
{
        initInnerMetas ();
        std::copy (m.begin (), m.end (), std::inserter (*innerMetas, innerMetas->end ()));
}

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

/****************************************************************************/

IMeta *AbstractMeta::getInnerMeta (const std::string &key) const
{
        IMeta *ret = NULL;

        if (parent) {
                ret = parent->getInnerMeta (key);

                if (ret) {
                        return ret;
                }
        }

#if 0
        std::cerr << getId () << ", parent == false, inner.size () == " << innerMetas.size () << std::endl;
#endif

        if (innerMetas) {
                MetaMap::const_iterator i;

                if ((i = innerMetas->find (key)) != innerMetas->end ()) {
                        return i->second;
                }
        }

        return NULL;
}

}
