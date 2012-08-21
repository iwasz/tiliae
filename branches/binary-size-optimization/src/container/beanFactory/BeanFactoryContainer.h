/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORY_CONTAINER_H_
#define BEANFACTORY_CONTAINER_H_

#include <sparsehash/sparse_hash_map>
#include "common/Exceptions.h"
#include "common/Attributes.h"
#include "string/String.h"
#include "Pointer.h"
#include "variant/Variant.h"
#include "Typedefs.h"
#include "IToStringEnabled.h"
#include "ApiMacro.h"
#include "StringFactoryMethodEditor.h"
#include "TypeEditor.h"
#include "StrUtil.h"
#include "BeanFactory.h"

namespace Container {
class MetaContainer;

typedef google::sparse_hash_map <std::string, Core::Variant> SparseVariantMap;

/**
 *
 */
class TILIAE_API BeanFactoryContainer : public Core::IToStringEnabled {
public:

        BeanFactoryContainer (SparseVariantMap *s);
        virtual ~BeanFactoryContainer ();

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
        Core::Variant getBean (const std::string &name) const;
        bool containsBean (const std::string &name) const;

        BeanFactory *getBeanFactory (const std::string &name, BeanFactory *innerBean = NULL) const;

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
        Core::Variant getSingleton (const std::string &name) const;
        SparseVariantMap *getSingletons () { return singletons; }

        BeanFactoryMap &getBeanFactoryMap () { return factoryMap; }

        BeanFactoryContainer const *getLinked () const { return linked; }
        void setLinked (BeanFactoryContainer const *l) { linked = l; }

        Ptr <MetaContainer> getMetaContainer () { return metaContainer; }
        void setMetaContainer (Ptr <MetaContainer> m) { metaContainer = m; }

        void addConversion (std::type_info const &type, Editor::StringFactoryMethodEditor::ConversionFunctionPtr function);

        friend class ContainerFactory;

private:

        BeanFactoryMap factoryMap;
        SparseVariantMap *singletons;
        BeanFactoryContainer const *linked;
        Ptr <MetaContainer> metaContainer;
        Editor::StringFactoryMethodEditor *conversionMethodEditor;
        Editor::TypeEditor *typeEditor;

};

}

#endif /* BEANFACTORY_H_ */
