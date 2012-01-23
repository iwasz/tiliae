/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SERVICEREPOSITORYIMPL_404238_H
#define SERVICEREPOSITORYIMPL_404238_H

#include "IBeanWrapper.h"
#include "path/IPath.h"
#include "plugins/IBeanWrapperPlugin.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"
#include "../../core/Context.h"
#include "../../editor/IEditor.h"
#include "Reflection.h"

namespace Wrapper {

/**
 * Nie zawiera getBeanWrapperForPropertyPath, poniewaz nie bede
 * pchal funkcjonalnosci tworzenia skomplikowanego obiektu tutaj,
 * do BeanWrappera. Niech tym sie zajmie jakas fabryka IFactory.
 */
class TILIAE_API BeanWrapper : public IBeanWrapper, public Core::IToStringEnabled {
public:

        REFLECTION_CONSTRUCTOR_ (void)
        BeanWrapper () {}
        BeanWrapper (const Core::Variant &bean) { setWrappedObject (bean); }

        virtual ~BeanWrapper () {}

        /**
         * Pomocnicza, tworzy typową konfigurację BeanWrappera (z typowym zestawem
         * pluginów).
         */
        static Ptr <BeanWrapper> create (const Core::Variant &bean = Core::Variant ());

/*------IPropertyAccessor---------------------------------------------------------*/

        /**
         * Ustawia pole (property), lub cały obiekt, jeśli ścieżka to "".
         * Zrzuci wyjatek (narazie AssertionException), gdy ustawiamy
         * property, a wrapowany obiektjest none lub nie null. Czyli
         * gdy object.isNone () || object.isNull ().
         */
        virtual void set (const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL);
        virtual void set (Core::Variant *bean, const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL);

        /**
         * Zwraca pole (property), lub cały obiekt, jeśli ścieżka to "".
         * Zrzuci wyjatek (narazie AssertionException), gdy ustawiamy
         * property, a wrapowany obiektjest none lub nie null. Czyli
         * gdy object.isNone () || object.isNull ().
         * TODO test, czy faktycznie zrzuca!
         */
        virtual Core::Variant get (const std::string &path, Core::Context *ctx = NULL) const;
        virtual Core::Variant get (const Core::Variant *bean, const std::string &path, Core::Context *ctx = NULL) const;

        virtual void add (const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL);
        virtual void add (Core::Variant *bean, const std::string &path, const Core::Variant &object, Core::Context *ctx = NULL);

        virtual Ptr <Core::IIterator> iterator (const std::string &path, Core::Context *ctx = NULL) const;
        virtual Ptr <Core::IIterator> iterator (const Core::Variant *bean, const std::string &path, Core::Context *ctx = NULL) const;

/*------IBeanWrapper--------------------------------------------------------*/

        virtual void setWrappedObject (const Core::Variant &object) { wrappedObject = object; }
        virtual Core::Variant getWrappedObject () const { return wrappedObject; }

/*--------------------------------------------------------------------------*/

        /**
         *  Zamienia na postac stringowa - do debagowania.
         */
        std::string toString () const;

/*------BeanWrapper-setters/getters-------------------------------------*/

        Ptr <BeanWrapperPluginList> getPluginList () const { return pluginList; }
        REFLECTION_METHOD (setPluginList) void setPluginList (Ptr <BeanWrapperPluginList> pluginList) { this->pluginList = pluginList; }

        /**
         * Opcjonalny edytor do edytowania (narazie tylko) ustawianych obiektów. Jeśli jest ustawiony,
         * to kazdy ustawiany za pomocą set obiekt jest przepuszczany przez ten edytor (przynajmniej w
         * niektórych pluginach).
         */
        Ptr <Editor::IEditor> getEditor () const { return editor; }
        REFLECTION_METHOD (setEditor) void setEditor (Ptr <Editor::IEditor> e) { editor = e; }

protected:

/*------Helper-methods------------------------------------------------------*/

        Core::Variant get (const Core::Variant &referenceObject, Common::IPath *path, Core::Context *ctx) const;
        void set (Core::Variant *referenceObject, Common::IPath *path, const Core::Variant &v, Core::Context *ctx);
        void add (Core::Variant *referenceObject, Common::IPath *path, const Core::Variant &v, Core::Context *ctx);
        Core::Variant iterator (const Core::Variant &referenceObject, Common::IPath *path, Core::Context *ctx) const;

        /**
         *  Koncowe i ostateczne  pobranie wartosci tokens z beana input.
         */
        Core::Variant getObjectUsingPlugins (const Core::Variant &input, Common::IPath *path, Core::Context *ctx, bool iter = false) const;

        /**
         *  Koncowe i ostateczne ustawienie wartosci property object obiektowi input.
         */
        void setObjectUsingPlugins (Core::Variant *bean, Common::IPath *path, const Core::Variant &object, Core::Context *ctx, bool add = false);

/*--------------------------------------------------------------------------*/

private:

        /**
         * Wrapowany bean.
         */
        Core::Variant wrappedObject;

        /**
         *  Strategia do wyciagania obiektow.
         */
        Ptr <BeanWrapperPluginList> pluginList;

        Ptr <Editor::IEditor> editor;

        REFLECTION_END (BeanWrapper)
};

} // namespace

#endif

