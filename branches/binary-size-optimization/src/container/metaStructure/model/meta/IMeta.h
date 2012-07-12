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
#include "metaStructure/interface/IDataVisitor.h"
#include "../../../../core/Pointer.h"
#include "../../../../core/ApiMacro.h"
#include "../data/IData.h"
#include "../../../common/Attributes.h"

namespace Container {
struct IMeta;
class Attributes;

typedef std::pair <std::string, Ptr <IMeta> > MetaPair;
typedef std::list <Ptr <IMeta> > MetaList;
typedef std::map <std::string, IMeta *> MetaMap;
typedef std::stack <IMeta *> MetaStack;
//typedef std::stack <Ptr <IElem> > MetaElemStack;

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
        enum Type { MAPPED, INDEXED };

        virtual Type getType () const = 0;

        /**
         * Ozwierciedla relacje rodzic-potomek. W XML zaimplementowane
         * przez atrybuty parent.
         */
        virtual DataVector getConstructorArgs () const = 0;
        virtual void addConstructorArg (IData *elem) = 0;

        virtual Ptr <Attributes> getAttributes () = 0;

/*--------------------------------------------------------------------------*/

        virtual bool getAbstract () const = 0;
        virtual void setAbstract (bool abstract) = 0;

        virtual bool getLazyInit () const = 0;
        virtual void setLazyInit (bool lazyInit) = 0;

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

/*--------------------------------------------------------------------------*/

        virtual MetaMap getInnerMetas () const = 0;
        virtual void setInnerMetas (const MetaMap &m) = 0;
        virtual void addInnerMeta (IMeta *m) = 0;
        virtual void addInnerMetaList (const MetaMap &m) = 0;

        virtual IMeta *getParentMeta () = 0;
        virtual void setParentMeta (IMeta *m) = 0;

/*-- attribute markers -----------------------------------------------------*/

        virtual bool containsAttribute (Attributes::AttributeName key) const = 0;

/*--------------------------------------------------------------------------*/

        virtual void accept (IMetaVisitor *visitor) = 0;
};

}

#endif /* IMETA_H_ */
