/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef META_OBJECT_TILIAE_H_
#define META_OBJECT_TILIAE_H_

#include <sparsehash/sparse_hash_map>
#include <deque>
#include <stack>
#include <hash_fun.h>
#include "common/Attributes.h"
#include "Typedefs.h"
#include "ApiMacro.h"
#include "../interface/IDataVisitor.h"
#include "../../metaStructure/model/data/IData.h"
#include "../../common/Exceptions.h"

namespace Container {
class MetaObject;

struct Eqstr {
        bool operator()(const char* s1, const char* s2) const {
                return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
        }
};

typedef google::sparse_hash_map <const char*, MetaObject *, __gnu_cxx::hash<const char*>, Eqstr> MetaMap;

struct BidirectionalMetaIndex {

        void add (size_t index, MetaObject *meta)
        {
                metaToInt[meta] = index;
                intToMeta[index] = meta;
        }

        MetaObject *get (size_t index) { IntToMeta::iterator i = intToMeta.find (index); return (i != intToMeta.end ()) ? (i->second) : (NULL); }
        MetaObject const *get (size_t index) const { IntToMeta::const_iterator i = intToMeta.find (index); return (i != intToMeta.end ()) ? (i->second) : (NULL); }

        size_t get (MetaObject *meta) { MetaToInt::iterator i = metaToInt.find (meta); if (i != metaToInt.end ()) { return i->second; } throw ConfigurationException ("BidirectionalMetaIndex::get ()"); }
        size_t get (MetaObject *meta) const { MetaToInt::const_iterator i = metaToInt.find (meta); if (i != metaToInt.end ()) { return i->second; } throw ConfigurationException ("BidirectionalMetaIndex::get ()"); }

        typedef google::sparse_hash_map <MetaObject *, size_t> MetaToInt;
        typedef google::sparse_hash_map <size_t, MetaObject *> IntToMeta;
        friend std::ostream &operator<< (std::ostream &o, BidirectionalMetaIndex const &m);

        MetaToInt metaToInt;
        IntToMeta intToMeta;
};

typedef std::stack <MetaObject *> MetaStack;
typedef std::vector <MetaObject *> MetaVector;
typedef std::deque <MetaObject *> MetaDeque;

/**
 * W celach implemetacyjnych. Tu jest wspolny kod.
 * \ingroup Container
 */
class TILIAE_API MetaObject {
public:

        enum Scope { SINGLETON, PROTOTYPE, BEAN };
        enum Type { UNSPECIFIED, MAPPED, INDEXED };

        virtual ~MetaObject ();

        void accept (IMetaVisitor *visitor) { visitor->visit (this); }
        Type getType () const { return type; }

        DataVector getConstructorArgs () const;
        void addConstructorArg (IData *elem);

/*-- attribute markers -----------------------------------------------------*/

        Attributes *getAttributes () { return &attributes; }
        bool containsAttribute (Attributes::AttributeName key) const { return attributes.containsKey (key); }

/*--------------------------------------------------------------------------*/

        bool getAbstract () const { return attributes.getBool (Attributes::ABSTRACT_ARGUMENT, false); }
        void setAbstract (bool abstract) { attributes.setBool (Attributes::ABSTRACT_ARGUMENT, abstract); }

        bool getLazyInit () const { return attributes.getBool (Attributes::LAZYINIT_ARGUMENT); }
        void setLazyInit (bool lazyInit) { attributes.setBool (Attributes::LAZYINIT_ARGUMENT, lazyInit); }

        Scope getScope () const { return static_cast <Scope> (attributes.getInt (Attributes::SCOPE_ARGUMENT)); }
        void setScope (Scope s) { attributes.setInt (Attributes::SCOPE_ARGUMENT, s); }

        const char *getId () const { return attributes.getString (Attributes::ID_ARGUMENT, false); }
        void setId (const char *id) { attributes.setString (Attributes::ID_ARGUMENT, id); }

        const char *getClass () const { return attributes.getString (Attributes::CLASS_ARGUMENT); }
        void setClass (const char *clazz) { attributes.setString (Attributes::CLASS_ARGUMENT, clazz); }

        const char *getParent () const { return attributes.getString (Attributes::PARENT_ARGUMENT, false); }
        void setParent (const char *parent) { attributes.setString (Attributes::PARENT_ARGUMENT, parent); }

        const char *getInitMethod () const { return attributes.getString (Attributes::INITMETHOD_ARGUMENT); }
        void setInitMethod (const char *initMethod) { attributes.setString (Attributes::INITMETHOD_ARGUMENT, initMethod); }

        const char *getFactory () const { return attributes.getString (Attributes::FACTORY_ARGUMENT); }
        void setFactory (const char *factory) { attributes.setString (Attributes::FACTORY_ARGUMENT, factory); }

        const char *getEditor () const { return attributes.getString (Attributes::EDITOR_ARGUMENT); }
        void setEditor (const char *editor) { attributes.setString (Attributes::EDITOR_ARGUMENT, editor); }

/*--------------------------------------------------------------------------*/

        MetaMap getInnerMetas () const;
        MetaObject *getInnerMeta (const std::string &key) const;

        MetaObject *getParentMeta () { return parent; }
        void setParentMeta (MetaObject *m) { parent = m; attributes.setParentAttributes (m->getAttributes ()); }

/*--------------------------------------------------------------------------*/

        DataKeyVector getFields () const;
        void addMapField (DataKey *dataKey);
        void addListField (DataKey *dataKey);

private:

        void addInnerMeta (MetaObject *m);

private:

        MetaObject ();
        friend class MetaFactory;
        friend class MetaContainer;

        void initConstructorArgs ();
        void initInnerMetas ();
        DataKeyVector getMapFields () const;
        DataKeyVector getListFields () const;

protected:

        MetaObject *parent;

private:

        Attributes attributes;
        DataVector *constructorArgs;
        MetaMap *innerMetas;
        DataKey *fields;
        DataKey *lastField;
        Type type;
};

TILIAE_API std::ostream &operator<< (std::ostream &o, MetaObject const &m);
TILIAE_API std::ostream &operator<< (std::ostream &o, MetaDeque const &m);
TILIAE_API std::ostream &operator<< (std::ostream &o, BidirectionalMetaIndex const &m);

}

#endif /* ABSTRACTMETA_H_ */
