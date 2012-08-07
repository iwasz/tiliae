/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef META_OBJECT_TILIAE_H_
#define META_OBJECT_TILIAE_H_

#include <map>
#include <list>
#include <stack>
#include "common/Attributes.h"
#include "Typedefs.h"
#include "ApiMacro.h"
#include "../interface/IDataVisitor.h"
#include "../../metaStructure/model/data/IData.h"

namespace Container {
class MetaObject;

typedef std::pair <std::string, Ptr <MetaObject> > MetaPair;
typedef std::list <Ptr <MetaObject> > MetaList;
typedef std::map <std::string, MetaObject *> MetaMap;
typedef std::stack <MetaObject *> MetaStack;

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
        void setInnerMetas (const MetaMap &m);
        void addInnerMeta (MetaObject *m);
        void addInnerMetaList (const MetaMap &m);

        MetaObject *getParentMeta () { return parent; }
        void setParentMeta (MetaObject *m) { parent = m; attributes.setParentAttributes (m->getAttributes ()); }

/*--------------------------------------------------------------------------*/

        DataKeyVector getFields () const;
        void addMapField (DataKey *dataKey);
        void addListField (DataKey *dataKey);

private:

        MetaObject ();
        friend class MetaFactory;

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

}

#endif /* ABSTRACTMETA_H_ */
