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
#include "../../../../core/Typedefs.h"
#include "../../../../core/ApiMacro.h"

namespace Container {

/**
 * W celach implemetacyjnych. Tu jest wspolny kod.
 * \ingroup Container
 */
class TILIAE_API AbstractMeta : public IMeta {
public:

        virtual ~AbstractMeta ();

        DataVector getConstructorArgs () const;
        void addConstructorArg (IData *elem);

/*-- attribute markers -----------------------------------------------------*/

        Ptr <Attributes> getAttributes () { return attributes; }
        bool containsAttribute (Attributes::AttributeName key) const { return attributes->containsKey (key); }

/*--------------------------------------------------------------------------*/

        bool getAbstract () const { return attributes->getBool (Attributes::ABSTRACT_ARGUMENT, false); }
        void setAbstract (bool abstract) { attributes->setBool (Attributes::ABSTRACT_ARGUMENT, abstract); }

        bool getLazyInit () const { return attributes->getBool (Attributes::LAZYINIT_ARGUMENT); }
        void setLazyInit (bool lazyInit) { attributes->setBool (Attributes::LAZYINIT_ARGUMENT, lazyInit); }

        Scope getScope () const { return static_cast <Scope> (attributes->getInt (Attributes::SCOPE_ARGUMENT)); }
        void setScope (Scope s) { attributes->setInt (Attributes::SCOPE_ARGUMENT, s); }

        std::string getId () const { return attributes->getString (Attributes::ID_ARGUMENT, false); }
        void setId (const std::string &id) { attributes->setString (Attributes::ID_ARGUMENT, id); }

        std::string getClass () const { return attributes->getString (Attributes::CLASS_ARGUMENT); }
        void setClass (const std::string &clazz) { attributes->setString (Attributes::CLASS_ARGUMENT, clazz); }

        std::string getParent () const { return attributes->getString (Attributes::PARENT_ARGUMENT, false); }
        void setParent (const std::string &parent) { attributes->setString (Attributes::PARENT_ARGUMENT, parent); }

        std::string getDependsOn () const { return attributes->getString (Attributes::DEPENDSON_ARGUMENT); }
        void setDependsOn (const std::string &dependsOn) { attributes->setString (Attributes::DEPENDSON_ARGUMENT, dependsOn); }

        std::string getInitMethod () const { return attributes->getString (Attributes::INITMETHOD_ARGUMENT); }
        void setInitMethod (const std::string &initMethod) { attributes->setString (Attributes::INITMETHOD_ARGUMENT, initMethod); }

        std::string getFactory () const { return attributes->getString (Attributes::FACTORY_ARGUMENT); }
        void setFactory (const std::string &factory) { attributes->setString (Attributes::FACTORY_ARGUMENT, factory); }

        std::string getEditor () const { return attributes->getString (Attributes::EDITOR_ARGUMENT); }
        void setEditor (const std::string &editor) { attributes->setString (Attributes::EDITOR_ARGUMENT, editor); }

/*--------------------------------------------------------------------------*/

        MetaMap getInnerMetas () const;
        IMeta *getInnerMeta (const std::string &key) const;
        void setInnerMetas (const MetaMap &m);
        void addInnerMeta (IMeta *m);
        void addInnerMetaList (const MetaMap &m);

        IMeta *getParentMeta () { return parent; }
        void setParentMeta (IMeta *m) { parent = m; attributes->setParentAttributes (m->getAttributes ()); }

protected:

        AbstractMeta ();

private:

        void initConstructorArgs ();
        void initInnerMetas ();

protected:

        IMeta *parent;

private:

        Ptr <Attributes> attributes;
        DataVector *constructorArgs;
        MetaMap *innerMetas;

};

}

#endif /* ABSTRACTMETA_H_ */
