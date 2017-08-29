/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORY_H_
#define BEANFACTORY_H_

#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "common/collection/OrderedVariantMap.h"
#include "container/common/Attributes.h"
#include "container/common/Exceptions.h"
#include "container/metaStructure/model/MetaObject.h"
#include "core/ApiMacro.h"
#include "core/IToStringEnabled.h"
#include "core/Pointer.h"
#include "core/StrUtil.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/variant/Variant.h"
#include "editor/IEditor.h"
#include "editor/StringFactoryMethodEditor.h"
#include "editor/TypeEditor.h"
#include "factory/IFactory.h"

namespace Wrapper {
class IBeanWrapper;
class Handler;
};

namespace Container {
class BeanFactory;
class BeanFactoryContainer;

typedef std::stack<BeanFactory *> BeanFactoryStack;
typedef std::map<std::string, BeanFactory *> BeanFactoryMap;

/**
 * Główny i najważniejszy element kontenera IoC (Container), który
 * tworzy beany. Jedna fabryka tworzy jeden typ beanów, czyli na
 * jeden element <bean> w XML przypada jedna taka fabryka.
 * \ingroup Container
 */
class TILIAE_API BeanFactory : public Factory::IFactory, public Core::IToStringEnabled {
public:
        BeanFactory (BeanFactoryContainer *c);
        virtual ~BeanFactory ();

        /**
         * Parametry to singletony, ktore sa opcjonalne.
         */
        virtual Core::Variant create (const Core::VariantMap &singletons = Core::VariantMap (), Core::DebugContext *context = NULL) const;

        /*--------------------------------------------------------------------------*/

        std::string toString () const;

        /*--------------------------------------------------------------------------*/

        std::string const &getId () const { return id; }

        /**
         * Pobiera fabrykę, która tworzy fizycznego beana. Najczęściej będzie to
         * fabryka typu ReflectionFacotory, lub lepiej ReflexionFactory w ProxyFactory.
         */
        Factory::IFactory *getFactory () const { return factory; }
        void setFactory (Factory::IFactory *factory, bool autoDelete = false)
        {
                this->factory = factory;
                if (autoDelete) {
                        flags |= DELETE_FACTORY;
                }
                else {
                        flags &= ~DELETE_FACTORY;
                }
        }

        /**
         * Pobiera edytor, który edytuje obiekt tymczasowy tempObject na beana.
         * Bean wcześniej jest tworzony przez fabryke factory. Najlepiej ustawić
         * tu ProxyEditor.
         */
        Editor::IEditor *getEditor () const { return editor; }
        void setEditor (Editor::IEditor *editor, bool autoDelete = false)
        {
                this->editor = editor;
                if (autoDelete) {
                        flags |= DELETE_EDITOR;
                }
                else {
                        flags &= ~DELETE_EDITOR;
                }
        }

        Editor::IEditor *getCArgsEditor () const { return cArgsEditor; }
        void setCArgsEditor (Editor::IEditor *cArgsEditor) { this->cArgsEditor = cArgsEditor; }

        void setAttributes (Attributes *attributes);
        std::string getStringAttribute (Attributes::AttributeName key, bool getFromParent = true) const
        {
                return toStr (attributes->getString (key, getFromParent));
        }
        int getIntAttribute (Attributes::AttributeName key, bool getFromParent = true) const { return attributes->getInt (key, getFromParent); }
        bool getBoolAttribute (Attributes::AttributeName key, bool getFromParent = true) const { return attributes->getInt (key, getFromParent); }

        Core::VariantList const *getInputList () const { return inputList; }
        void setInputList (Core::VariantList const *input)
        {
                this->inputList = input;
                flags |= INPUT_LIST;
                flags &= ~INPUT_MAP;
        }

        Common::OrderedVariantMap const *getInputMap () const { return inputMap; }
        void setInputMap (Common::OrderedVariantMap const *input)
        {
                this->inputMap = input;
                flags |= INPUT_MAP;
                flags &= ~INPUT_LIST;
        }

        Core::Variant getInput () const;

        Core::VariantList const *getCArgs () const { return cArgs; }
        void setCArgs (Core::VariantList const *cArgs) { this->cArgs = cArgs; }

        bool getFullyInitialized () const { return flags & FULLY_INITIALIZED; }
        void setFullyInitialized (bool fullyInitialized)
        {
                if (fullyInitialized) {
                        flags |= FULLY_INITIALIZED;
                }
                else {
                        flags &= ~FULLY_INITIALIZED;
                }
        }

        void setBeanWrapper (Wrapper::IBeanWrapper *bw) { beanWrapper = bw; }

        /*------Inner/outer-bean----------------------------------------------------*/

        void addInnerBeanFactory (BeanFactory *bf);
        BeanFactory *getInnerBeanFactory (const std::string &id) const;

        BeanFactory *getOuterBeanFactory () const { return outerBeanFactory; }
        void setOuterBeanFactory (BeanFactory *o) { outerBeanFactory = o; }

        void onBeforePropertiesSet (BeanFactory const *notifier) const;
        void onAfterPropertiesSet (BeanFactory const *notifier) const;

        enum Flags { FULLY_INITIALIZED = 0x01, FORCE_SINGLETON = 0x02, INPUT_LIST = 0x04, INPUT_MAP = 0x08, DELETE_FACTORY = 0x10, DELETE_EDITOR = 0x20 };

        MetaObject::Scope getScope () const;

        bool isMarkForDeletion () const { return markForDeletion; }

private:
        void notifyBeforePropertiesSet () const;
        void notifyAfterPropertiesSet () const;
        bool fireMethod (Ptr<Wrapper::Handler> handler, Core::DebugContext *context, Core::VariantVector *list = 0, bool initMethodErrorMessage = true) const;

private:
        mutable unsigned int flags;

        std::string id;

        union {
                Core::VariantList const *inputList;
                Common::OrderedVariantMap const *inputMap;
        };

        Core::VariantList const *cArgs;

        mutable Core::Variant storedSingleton;

        Attributes *attributes;
        Editor::IEditor *cArgsEditor;
        Editor::IEditor *editor;
        Factory::IFactory *factory;
        Wrapper::IBeanWrapper *beanWrapper;

        BeanFactory *outerBeanFactory;
        BeanFactoryMap *innerBeanFactories;
        BeanFactoryContainer *container;
        mutable bool markForDeletion;
};

struct ToStringHelper {
        static std::string toString (const BeanFactoryMap &bfm);
};
}

#endif /* BEANFACTORY_H_ */
