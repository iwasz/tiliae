/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMETA_H_
#define IMETA_H_

#include <map>
#include <list>
#include <stack>
#include "../elem/ListElem.h"
#include "metaStructure/interface/IDataVisitor.h"
#include "../../../../core/Pointer.h"
#include "../../../../core/ApiMacro.h"

namespace Container {
struct IMeta;
class Attributes;

typedef std::pair <std::string, Ptr <IMeta> > MetaPair;
typedef std::list <Ptr <IMeta> > MetaList;
typedef std::map <std::string, Ptr <IMeta> > MetaMap;
typedef std::stack <Ptr <IMeta> > MetaStack;
typedef std::stack <Ptr <IElem> > MetaElemStack;

/**
 * Obiekty tej klasy stoją w opozycji do obiektów typu IData. To
 * są obiekty nie-skalarne, czyli posiadające strukturę. Narazie
 * mamy obiekty mapped (bean, map) i indexed (list, set).
 * \ingroup Container
 */
struct TILIAE_API IMeta {

        virtual ~IMeta () {}

        /**
         * Scopes.
         */
        enum Scope { PROTOTYPE, BEAN, SINGLETON };

        /**
         * Ozwierciedla relacje rodzic-potomek. W XML zaimplementowane
         * przez atrybuty parent i copyOf.
         */
        // TODO Przez referencję.
        virtual ListElemList getConstructorArgs () const = 0;
        virtual void setConstructorArgs (const ListElemList &constructorArgs) = 0;
        virtual void addConstructorArgs (const ListElemList &constructorArgs) = 0;
        virtual void addConstructorArg (Ptr <ListElem> elem) = 0;

//        virtual Core::VariantMap const &getMetaInfo () const = 0;
//        virtual void setMetaInfo (const Core::VariantMap &metaInfo) = 0;
//        virtual void addMetaInfos (const Core::VariantMap &metaInfo) = 0;
//        virtual void addMetaInfo (const std::string &key, const Core::Variant &metaInfo) = 0;

        virtual const Attributes &getAttributes () const = 0;
        virtual void setAttributes (const Attributes &attributes) = 0;
        virtual void addAttributes (const Attributes &attributes) = 0;

/*--------------------------------------------------------------------------*/

        virtual bool getAbstract () const = 0;
        virtual void setAbstract (bool abstract) = 0;

        virtual bool getLazyInit () const = 0;
        virtual void setLazyInit (bool lazyInit) = 0;

//        virtual bool getSingleton () const = 0;
//        virtual void setSingleton (bool singleton) = 0;

        virtual Scope getScope () const = 0;
        virtual void setScope (Scope s) = 0;

        virtual std::string getId () const = 0;
        virtual void setId (const std::string &id) = 0;

        virtual  std::string getClass () const = 0;
        virtual void setClass (const std::string &clazz) = 0;

        virtual std::string getParent () const = 0;
        virtual void setParent (const std::string &parent) = 0;

        virtual std::string getDependsOn () const = 0;
        virtual void setDependsOn (const std::string &dependsOn) = 0;

        virtual std::string getInitMethod () const = 0;
        virtual void setInitMethod (const std::string &initMethod) = 0;

        virtual std::string getFactory () const = 0;
        virtual void setFactory (const std::string &factory) = 0;

        virtual std::string getEditor () const = 0;
        virtual void setEditor (const std::string &editor) = 0;

//        virtual std::string getDescription () const = 0;
//        virtual void setDescription (const std::string &description) = 0;

/*--------------------------------------------------------------------------*/

        /// Pobiera z getInnerMetas i z outer beans.
        virtual Ptr <IMeta> get (const std::string &key) const = 0;

        virtual const MetaMap &getInnerMetas () const = 0;
        virtual void setInnerMetas (const MetaMap &m) = 0;
        virtual void addInnerMeta (Ptr <IMeta> m) = 0;

        virtual IMeta *getOuterMeta () const = 0;
        virtual void setOuterMeta (IMeta *m) = 0;

/*-- attribute markers -----------------------------------------------------*/

        virtual bool containsAttribute (const std::string &key) const = 0;

/*--------------------------------------------------------------------------*/

        virtual void accept (IMetaVisitor *visitor) = 0;
};

}

#endif /* IMETA_H_ */
