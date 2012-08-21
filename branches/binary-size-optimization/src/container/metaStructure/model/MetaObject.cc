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
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "Exceptions.h"
#include "MetaObject.h"
#include "StrUtil.h"

namespace Container {

MetaObject::MetaObject () : parent (NULL),
                            constructorArgs (NULL),
                            innerMetas (NULL),
                            fields (NULL),
                            lastField (NULL),
                            type (UNSPECIFIED)
{
        setScope (SINGLETON);
}

/****************************************************************************/

MetaObject::~MetaObject ()
{
        for (DataKey *dk = fields; dk; dk = dk->next) {
                dk->data->~IData ();
        }

        if (constructorArgs) {
                for (DataVector::iterator i = constructorArgs->begin (); i != constructorArgs->end (); ++i) {
                        (*i)->~IData ();
                }
        }

        delete constructorArgs;

//        if (innerMetas) {
//                for (MetaMap::iterator i = innerMetas->begin (); i != innerMetas->end (); ++i) {
//                        i->second->~MetaObject();
//                }
//        }

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

        innerMetas->operator [] (m->getId ()) = m;
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

                if ((i = innerMetas->find (key.c_str ())) != innerMetas->end ()) {
                        return i->second;
                }
        }

        return NULL;
}

/****************************************************************************/

void MetaObject::addMapField (DataKey *input)
{
        if (type == INDEXED) {
                throw ConfigurationException ("Meta::addMapField : this MetaObject is of INDEXED type, and you tried to add map-field to it.");
        }

        type = MAPPED;

        DataKey *dkParent = NULL;
        for (DataKey *dk = fields; dk; dk = dk->next) {
                if (!strcmpNull (dk->key, input->key)) {
                        if (dkParent) {
                                dkParent->next = dk->next;
                        }
                        else {
                                fields = dk->next;
                        }
                }

                dkParent = dk;
        }

        if (!fields) {
                fields = input;
        }

        if (lastField) {
                lastField->next = input;
        }

        lastField = input;
}

/****************************************************************************/

void MetaObject::addListField (DataKey *input)
{
        if (type == MAPPED) {
                throw ConfigurationException ("Meta::addListField : this MetaObject is of MAPPED type, and you tried to add list-field to it.");
        }

        type = INDEXED;

        if (!fields) {
                fields = input;
        }

        if (lastField) {
                lastField->next = input;
        }

        lastField = input;
}

/****************************************************************************/

DataKeyVector MetaObject::getFields () const
{
        if (type == INDEXED) {
                return getListFields ();
        }
        // MAPPED lub UNSPECIFIED
        else /*if (type == MAPPED)*/ {
                return getMapFields ();
        }
//
//        return DataKeyVector ();
}

/****************************************************************************/

DataKeyVector MetaObject::getMapFields () const
{
        DataKeyVector ret;

        if (parent) {
                DataKeyVector parFields = parent->getMapFields ();

                for (DataKeyVector::const_iterator i = parFields.begin (); i != parFields.end (); ++i) {

                        DataKey *parField = *i;

                        // Dodaj z parFields do ret, ale tylko jesli dziecko nie ma fielda o takim kluczu.
                        bool found = false;
                        for (DataKey *dk = fields; dk; dk = dk->next) {
                                if (!strcmpNull (parField->key, dk->key)) {
                                        found = true;
                                        break;
                                }
                        }

                        if (!found) {
                                ret.push_back (parField);
                        }
                }
        }

        for (DataKey *dk = fields; dk; dk = dk->next) {
                ret.push_back (dk);
        }

        return ret;
}

/****************************************************************************/

DataKeyVector MetaObject::getListFields () const
{
        DataKeyVector ret;

        if (parent) {
                ret = parent->getListFields ();
        }

        for (DataKey *dk = fields; dk; dk = dk->next) {
                ret.push_back (dk);
        }

        return ret;
}

/****************************************************************************/

Core::StringVector MetaObject::getDependsOn () const
{
        std::string deps = attributes.getString (Attributes::DEPENDS_ON_ARGUMENT);
        boost::erase_all (deps, " ");
        Core::StringVector ret;
        boost::split (ret, deps, boost::is_any_of (","), boost::token_compress_on);
        return ret;
}

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, MetaObject const &m)
{
        o << "MetaObject [" << m.getId () << "]";
        return o;
}


/****************************************************************************/

std::ostream &operator<< (std::ostream &o, MetaDeque const &m)
{
        o << "MetaDeque [";

        for (MetaDeque::const_iterator i = m.begin (); i != m.end ();) {
                o << **i;

                if (++i != m.end ()) {
                        o << ", ";
                }
        }

        o << "]";
        return o;
}

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, BidirectionalMetaIndex const &m)
{
        o << "BidirectionalMetaIndex [";

        for (BidirectionalMetaIndex::MetaToInt::const_iterator i = m.metaToInt.begin (); i != m.metaToInt.end ();) {
                o << i->second << "=" << *(i->first);

                if (++i != m.metaToInt.end ()) {
                        o << ", ";
                }
        }

        o << "]";
        return o;
}

/****************************************************************************/

size_t BidirectionalMetaIndex::get (MetaObject const *meta) const
{
        MetaToInt::const_iterator i = metaToInt.find (meta);

        if (i != metaToInt.end ()) {
                return i->second;
        }

        throw ConfigurationException ("BidirectionalMetaIndex::get : I can't find vertex descriptor (vertex number) for MetaObject in BidirectionalMetaIndex. Meta id : [" + std::string (meta->getId ()) + "]");
}

}
