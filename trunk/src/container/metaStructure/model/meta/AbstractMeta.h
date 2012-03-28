/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMETA_H_
#define ABSTRACTMETA_H_

#include "IMeta.h"
#include "common/Attributes.h"
#include "../elem/ListElem.h"
#include "../../../../core/Typedefs.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

extern TILIAE_API const char *ABSTRACT_ARGUMENT;
extern TILIAE_API const char *LAZYINIT_ARGUMENT;
extern TILIAE_API const char *ID_ARGUMENT;
extern TILIAE_API const char *CLASS_ARGUMENT;
extern TILIAE_API const char *PARENT_ARGUMENT;
extern TILIAE_API const char *DEPENDSON_ARGUMENT;
extern TILIAE_API const char *INITMETHOD_ARGUMENT;
extern TILIAE_API const char *FACTORY_ARGUMENT;
extern TILIAE_API const char *EDITOR_ARGUMENT;
extern TILIAE_API const char *DESCRIPTION_ARGUMENT;
extern TILIAE_API const char *OUTER_ARGUMENT;
extern TILIAE_API const char *SCOPE_ARGUMENT;

/**
 * W celach implemetacyjnych. Tu jest wspolny kod.
 * \ingroup Container
 */
class TILIAE_API AbstractMeta : public IMeta {
public:

        virtual ~AbstractMeta ();

        DataVector getConstructorArgs () const;
//        void setConstructorArgs (const ListElemList &constructorArgs);
//        void addConstructorArgs (const ListElemList &constructorArgs);
        void addConstructorArg (IData *elem);

/*-- attribute markers -----------------------------------------------------*/

        Ptr <Attributes> getAttributes () { return attributes; }
        bool containsAttribute (const std::string &key) const { return attributes->containsKey (key); }

/*--------------------------------------------------------------------------*/

        bool getAbstract () const { return attributes->getBool (ABSTRACT_ARGUMENT); }
        void setAbstract (bool abstract) { attributes->setBool (ABSTRACT_ARGUMENT, abstract); }

        bool getLazyInit () const { return attributes->getBool (LAZYINIT_ARGUMENT); }
        void setLazyInit (bool lazyInit) { attributes->setBool (LAZYINIT_ARGUMENT, lazyInit); }

        Scope getScope () const { return static_cast <Scope> (attributes->getInt (SCOPE_ARGUMENT)); }
        void setScope (Scope s) { attributes->setInt (SCOPE_ARGUMENT, s); }

        std::string getId () const { return attributes->getString (ID_ARGUMENT, false); }
        void setId (const std::string &id) { attributes->setString (ID_ARGUMENT, id); }

        std::string getClass () const { return attributes->getString (CLASS_ARGUMENT); }
        void setClass (const std::string &clazz) { attributes->setString (CLASS_ARGUMENT, clazz); }

        std::string getParent () const { return attributes->getString (PARENT_ARGUMENT, false); }
        void setParent (const std::string &parent) { attributes->setString (PARENT_ARGUMENT, parent); }

        std::string getDependsOn () const { return attributes->getString (DEPENDSON_ARGUMENT); }
        void setDependsOn (const std::string &dependsOn) { attributes->setString (DEPENDSON_ARGUMENT, dependsOn); }

        std::string getInitMethod () const { return attributes->getString (INITMETHOD_ARGUMENT); }
        void setInitMethod (const std::string &initMethod) { attributes->setString (INITMETHOD_ARGUMENT, initMethod); }

        std::string getFactory () const { return attributes->getString (FACTORY_ARGUMENT); }
        void setFactory (const std::string &factory) { attributes->setString (FACTORY_ARGUMENT, factory); }

        std::string getEditor () const { return attributes->getString (EDITOR_ARGUMENT); }
        void setEditor (const std::string &editor) { attributes->setString (EDITOR_ARGUMENT, editor); }

/*--------------------------------------------------------------------------*/

        MetaMap getInnerMetas () const;
        void setInnerMetas (const MetaMap &m);
        void addInnerMeta (IMeta *m);
        void addInnerMetaList (const MetaMap &m);

        IMeta *getParentMeta () { return parent; }
        void setParentMeta (IMeta *m) { parent = m; attributes->setParentAttributes (m->getAttributes ()); }

protected:

        AbstractMeta () : parent (NULL), scope (IMeta::PROTOTYPE), attributes (boost::make_shared <Attributes> ()), constructorArgs (NULL), innerMetas (NULL) {}
        AbstractMeta (const AbstractMeta &) : parent (NULL), scope (IMeta::PROTOTYPE), attributes (boost::make_shared <Attributes> ()), constructorArgs (NULL), innerMetas (NULL) {}

private:

        void initConstructorArgs ();
        void initInnerMetas ();

protected:

        IMeta *parent;

private:

        Scope scope;
        Ptr <Attributes> attributes;
        DataVector *constructorArgs;
        MetaMap *innerMetas;

};

}

#endif /* ABSTRACTMETA_H_ */
