/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORY_CONTAINER_H_
#define BEANFACTORY_CONTAINER_H_

#include "container/common/Exceptions.h"
#include "container/common/Attributes.h"
#include "core/string/String.h"
#include "core/Pointer.h"
#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "core/IToStringEnabled.h"
#include "core/ApiMacro.h"
#include "editor/StringFactoryMethodEditor.h"
#include "editor/TypeEditor.h"
#include "core/StrUtil.h"
#include "container/beanFactory/BeanFactory.h"
#include "core/allocator/ArrayRegionAllocator.h"
#include "container/common/SparseVariantMap.h"

namespace Container {
class MetaContainer;
class InternalSingletons;

/**
 *
 */
class TILIAE_API BeanFactoryContainer : public Core::IToStringEnabled {
public:

        BeanFactoryContainer ();
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
        void addSingleton (const char *key, const Core::Variant &singleton);
        Core::Variant getSingleton (const char *name) const;
        Core::Variant getSingletonNoThrow (const char *name) const;
        SparseVariantMap *getSingletons () { return &singletons; }

        void setInternalSingletons (InternalSingletons *s) { internalSingletons = s; }
        InternalSingletons *getInternalSingletons () { return internalSingletons; }

        BeanFactoryMap &getBeanFactoryMap () { return factoryMap; }

        BeanFactoryContainer const *getLinked () const { return linked; }
        void setLinked (BeanFactoryContainer const *l) { linked = l; }

        Ptr <MetaContainer> getMetaContainer () { return metaContainer; }
        void setMetaContainer (Ptr <MetaContainer> m) { metaContainer = m; }

        /**
         * Odpowiada na pytanie czy ten kontener zachowuje konfigurację (meta obiekty i fabryki beanów)
         * na później dla swoich ewentualnych podlinkowanych kontenerów.
         */
        bool isStoreConfigurationForLinked () const { return bool (metaContainer); }

        void addConversion (std::type_info const &type, Editor::StringFactoryMethodEditor::ConversionFunctionPtr function);
        Core::ArrayRegionAllocator <char> *getMemoryAllocator () { return &memoryAllocator; }

        friend class ContainerFactory;

private:

        void deleteSingleton (Core::Variant &v);

private:

        BeanFactoryMap factoryMap;
        // Singletony z kluczami - można je pobrać po kluczu. Są kasowane kiedy kasujemy container.
        SparseVariantMap singletons;
        // Singletony bez kluczy, które poprostu mają zostać skasowane kiedy kasujemy container.
        Core::VariantVector additionalSingletons;
        InternalSingletons *internalSingletons;
        BeanFactoryContainer const *linked;
        Ptr <MetaContainer> metaContainer;
        Editor::StringFactoryMethodEditor *conversionMethodEditor;
        Editor::TypeEditor *typeEditor;
        Core::ArrayRegionAllocator <char> memoryAllocator;

};

}

#endif /* BEANFACTORY_H_ */
