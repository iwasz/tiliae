/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORY_H_
#define BEANFACTORY_H_

#include <map>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include "common/Exceptions.h"
#include "common/Attributes.h"
#include "../../core/string/String.h"
#include "../../core/Pointer.h"
#include "../../core/variant/Variant.h"
#include "../../core/Typedefs.h"
#include "../../core/IToStringEnabled.h"
#include "../../factory/IFactory.h"
#include "../../editor/IEditor.h"
#include "../../core/ApiMacro.h"

namespace Wrapper {
class IBeanWrapper;
};

namespace Editor {
class LazyEditor;
}

namespace Container {
class MetaContainer;

/**
 * Główny i najważniejszy element kontenera IoC (Container), który
 * tworzy beany. Jedna fabryka tworzy jeden typ beanów, czyli na
 * jeden element <bean> w XML przypada jedna taka fabryka.
 * \ingroup Container
 */
class TILIAE_API BeanFactory : public Factory::IFactory, public Core::IToStringEnabled {
public:

        BeanFactory ();
        virtual ~BeanFactory ();

        /**
         * Parametry to singletony, ktore sa opcjonalne.
         */
        virtual Core::Variant create (const Core::VariantMap &singletons = Core::VariantMap (),
                                      Core::Context *context = NULL) const;

/*--------------------------------------------------------------------------*/

        std::string toString () const;

/*--------------------------------------------------------------------------*/

        std::string getId () const { return id; }

        /**
         * Pobiera fabrykę, która tworzy fizycznego beana. Najczęściej będzie to
         * fabryka typu ReflectionFacotory, lub lepiej ReflexionFactory w ProxyFactory.
         */
        Ptr <Factory::IFactory> getFactory () const { return factory; }
        void setFactory (Ptr <Factory::IFactory> factory) { this->factory = factory; }

        /**
         * Pobiera edytor, który edytuje obiekt tymczasowy tempObject na beana.
         * Bean wcześniej jest tworzony przez fabryke factory. Najlepiej ustawić
         * tu ProxyEditor.
         */
        Ptr <Editor::IEditor> getEditor () const { return editor; }
        void setEditor (Ptr <Editor::IEditor> editor) { this->editor = editor; }

        Ptr<Editor::IEditor> getCArgsEditor () const { return cArgsEditor; }
        void setCArgsEditor (Ptr<Editor::IEditor> cArgsEditor) { this->cArgsEditor = cArgsEditor; }

        const Attributes &getAttributes () const { return attributes; }
        void setAttributes (const Attributes &attributes);

        const Core::Variant &getInput () const { return input; }
        void setInput (const Core::Variant &input) { this->input = input; }

        const Core::Variant &getCArgs () const { return cArgs; }
        void setCArgs (const Core::Variant &cArgs) { this->cArgs = cArgs; }

        bool getFullyInitialized() const { return fullyInitialized; }
        void setFullyInitialized(bool fullyInitialized) { this->fullyInitialized = fullyInitialized; }

        Ptr <Wrapper::IBeanWrapper> getBeanWrapper () const { return beanWrapper; }
        void setBeanWrapper (Ptr <Wrapper::IBeanWrapper> bw) { beanWrapper = bw; }

/*------Inner/outer-bean----------------------------------------------------*/

        void addInnerBeanFactory (Ptr <BeanFactory> bf);
        Ptr <BeanFactory> getInnerBeanFactory (const std::string &id) const;

        BeanFactory *getOuterBeanFactory () const { return outerBeanFactory; }
        void setOuterBeanFactory (BeanFactory *o) { outerBeanFactory = o; }

        void onBeforePropertiesSet (BeanFactory const *notifier) const;
        void onAfterPropertiesSet (BeanFactory const *notifier) const;

private:

        void notifyBeforePropertiesSet () const;
        void notifyAfterPropertiesSet () const;

/*--------------------------------------------------------------------------*/

private:

        bool getSingleton () const;

private:

        bool fullyInitialized;
        mutable bool forceSingleton;

        std::string id;
        Core::Variant input;
        Core::Variant cArgs;
        mutable Core::Variant storedSingleton;
        Attributes attributes;

        Ptr <Editor::IEditor> cArgsEditor;
        Ptr <Editor::IEditor> editor;
        Ptr <Factory::IFactory> factory;
        Ptr <Wrapper::IBeanWrapper> beanWrapper;

        BeanFactory *outerBeanFactory;
//        BeanFactoryMap innerBeanFactories;
        void *innerBeanFactories;
};

typedef std::list <Ptr <BeanFactory> > BeanFactoryList;
typedef std::stack <Ptr <BeanFactory> > BeanFactoryStack;

/**
 * Mapa, która trzyma kolejność elementów.
 */
typedef boost::multi_index::multi_index_container<
        Ptr <BeanFactory>,
        boost::multi_index::indexed_by<
                // Jak mapa
                boost::multi_index::ordered_non_unique<
                        boost::multi_index::const_mem_fun <BeanFactory, std::string, &BeanFactory::getId>
                >,
                // Jak lista
                boost::multi_index::sequenced<>
        >
> BeanFactoryMap;

struct ToStringHelper {
        static std::string toString (const BeanFactoryMap &bfm);
        static std::string toString (const BeanFactoryList &bfl);
};

/*##########################################################################*/

/**
 *
 */
class TILIAE_API BeanFactoryContainer : public Core::IToStringEnabled {
public:

        virtual std::string toString () const;

/*--------------------------------------------------------------------------*/

        void reset ();

        /**
         * Głowna metod tego interfejsu. Jako parameters można podać dodatkową
         * mapę singletonów. Jest to alternatywa do dodawania singletonów za
         * pomocą addSingleton.
         * @param singletons Dodatkowa mapa singletonów.
         * @return Obiekt.
         */
        Core::Variant getBean (const std::string &name, const Core::VariantMap &singletons = Core::VariantMap ()) const;
        bool containsBean (const std::string &name) const;

        Ptr <BeanFactory> getBeanFactory (const std::string &name, Ptr <BeanFactory> innerBean = Ptr <BeanFactory> ()) const;

        /**
         * Taka metoda będzie bardzo przydanta, gdyż za jej pomocą można
         * dodać do kontenera COKOLWIEK. Można przede wszystkim dodać sam
         * kontener (addSingleton (@this, this)), oraz mnóstwo jego elementów
         * składowych, do których będzie można się odwoływać potem jawnie
         * (na przykad w XMLu). Będzie można dodać edytory i fabryki, które
         * tworzą ValueData etc. Dodatkowo także i user będzie mógł dodać
         * to co będzie chciał.
         */
        void addSingleton (const std::string &key, const Core::Variant &singleton);

        Ptr <Core::VariantMap> getSingletons () { return singletons; }
        void setSingletons (Ptr <Core::VariantMap> s) { singletons = s; }

        Ptr <BeanFactoryMap> getBeanFactoryMap () { return factoryMap; }
        void setBeanFactoryMap (Ptr <BeanFactoryMap> m) { factoryMap = m; }

        Ptr <BeanFactoryContainer const> getLinked () const { return linked; }
        void setLinked (Ptr <BeanFactoryContainer const> l) { linked = l; }

        Ptr <MetaContainer const> getMetaContainer () const { return metaContainer; }
        void setMetaContainer (Ptr <MetaContainer const> m) { metaContainer = m; }

private:

        Ptr <BeanFactoryMap> factoryMap;
        Ptr <Core::VariantMap> singletons;
        Ptr <BeanFactoryContainer const> linked;
        Ptr <MetaContainer const> metaContainer;

};


}

#endif /* BEANFACTORY_H_ */
