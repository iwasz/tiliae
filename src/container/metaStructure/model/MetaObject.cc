/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <iterator>
#include <boost/algorithm/string/trim.hpp>
#include "../../common/Exceptions.h"
#include "MetaObject.h"

namespace Container {

MetaObject::MetaObject () : parent (NULL),
                                attributes (boost::make_shared <Attributes> ()),
                                constructorArgs (NULL),
                                innerMetas (NULL),
                                mapFields (NULL),
                                listFields (NULL),
                                type (UNSPECIFIED)
{
        setScope (SINGLETON);
}

/****************************************************************************/

MetaObject::~MetaObject ()
{
        if (listFields) {
                for (DataVector::iterator i = listFields->begin (); i != listFields->end (); ++i) {
//                        delete *i;
                        (*i)->~IData ();
                }
                delete listFields;
        }

        if (mapFields) {
                for (DataKeyIterator0 i = mapFields->begin (); i != mapFields->end (); ++i) {
//                        delete i->data;
                        i->data->~IData ();
                }
                delete mapFields;
        }

        if (constructorArgs) {
                for (DataVector::iterator i = constructorArgs->begin (); i != constructorArgs->end (); ++i) {
//                        delete *i;
                        (*i)->~IData ();
                }
        }

        delete constructorArgs;

        if (innerMetas) {
                for (MetaMap::iterator i = innerMetas->begin (); i != innerMetas->end (); ++i) {
//                        delete i->second;
                        i->second->~MetaObject();
                }
        }

        delete innerMetas;
}

/****************************************************************************/

void MetaObject::initConstructorArgs ()
{
        if (!constructorArgs) {
                constructorArgs = new DataVector;
        }
}

/****************************************************************************/

void MetaObject::initInnerMetas ()
{
        if (!innerMetas) {
                innerMetas = new MetaMap;
        }
}

/****************************************************************************/

void MetaObject::setInnerMetas (const MetaMap &m)
{
        initInnerMetas ();
        *innerMetas = m;
}

/****************************************************************************/

void MetaObject::addInnerMeta (MetaObject *m)
{
        initInnerMetas ();
        std::string id = m->getId ();

        // Nie powinno się zdarzyć.
        if (boost::trim_copy (id) == "") {
                throw ConfigurationException ("AbstractMeta::addInnerMeta : ID is empty. ID should be generated automatically or provided explicitly.");
        }

        if (getInnerMeta (id)) {
                throw ConfigurationException ("AbstractMeta::addInnerMeta : There is already a inner bean with ID [" + id + "].");
        }

        innerMetas->operator [] (id) = m;
}

/****************************************************************************/

void MetaObject::addInnerMetaList (const MetaMap &m)
{
        initInnerMetas ();
        std::copy (m.begin (), m.end (), std::inserter (*innerMetas, innerMetas->end ()));
}

/****************************************************************************/

void MetaObject::addConstructorArg (IData *elem)
{
        initConstructorArgs ();
        constructorArgs->push_back (elem);
}

/****************************************************************************/

DataVector MetaObject::getConstructorArgs () const
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

MetaMap MetaObject::getInnerMetas () const
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

MetaObject *MetaObject::getInnerMeta (const std::string &key) const
{
        MetaObject *ret = NULL;

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

/****************************************************************************/

IData *MetaObject::getMapField (const std::string &key)
{
        if (type == INDEXED) {
                throw ConfigurationException ("AbstractMeta::getMapField : you tried to get map-field from MetaObject which is of INDEXED type.");
        }

        if (mapFields) {
                DataKeyIterator0 iter = mapFields->get <0> ().find (key);

                if (iter != mapFields->get <0> ().end ()) {
                        return iter->data;
                }
        }

        if (parent) {
                return parent->getMapField (key);
        }

        return NULL;
}

/****************************************************************************/

void MetaObject::addMapField (DataKey const &dataKey)
{
        if (type == INDEXED) {
                throw ConfigurationException ("Meta::addMapField : this MetaObject is of INDEXED type, and you tried to add map-field to it.");
        }

        type = MAPPED;

        if (!mapFields) {
                mapFields = new DataMap ();
        }

        mapFields->erase (dataKey.key);
        mapFields->get <1> ().push_back (dataKey);
}

/****************************************************************************/

DataMap MetaObject::getMapFields () const
{
        if (type == INDEXED) {
                throw ConfigurationException ("AbstractMeta::getMapFields : you tried to get map-field from MetaObject which is of INDEXED type.");
        }

        if (parent) {
                DataMap ret = parent->getMapFields ();

                if (mapFields) {
                        std::copy (mapFields->get <1> ().begin (), mapFields->get <1> ().end (), std::back_inserter (ret.get <1> ()));

                        for (DataKeyIterator1 i = mapFields->get <1> ().begin (); i != mapFields->get <1> ().end (); ++i) {
                                ret.erase (i->key);
                                ret.get <1> ().push_back (*i);
                        }
                }

                return ret;
        }

        if (mapFields) {
                return *mapFields;
        }

        return DataMap ();
}

/****************************************************************************/

DataVector MetaObject::getListFields () const
{
        if (type == MAPPED) {
                throw ConfigurationException ("AbstractMeta::getListFields : you tried to get list-field from MetaObject which is of MAPPED type.");
        }

        if (parent) {
                DataVector ret = parent->getListFields ();

                if (listFields) {
                        std::copy (listFields->begin (), listFields->end (), std::back_inserter (ret));
                }

                return ret;
        }

        if (listFields) {
                return *listFields;
        }

        return DataVector ();
}

/****************************************************************************/

void MetaObject::addListField (IData *field)
{
        if (type == MAPPED) {
                throw ConfigurationException ("Meta::addListField : this MetaObject is of MAPPED type, and you tried to add list-field to it.");
        }

        type = INDEXED;

        if (!listFields) {
                listFields = new DataVector ();
        }


        listFields->push_back (field);
}

}
