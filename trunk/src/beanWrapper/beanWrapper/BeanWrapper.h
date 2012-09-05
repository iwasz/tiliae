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
#include "../../core/DebugContext.h"
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

        BeanWrapper (bool d = false) : editor (NULL), deleteContents (d) {}
        BeanWrapper (const Core::Variant &bean, bool d = false) : editor (NULL), deleteContents (d) { setWrappedObject (bean); }
        virtual ~BeanWrapper ();

        /**
         * Pomocnicza, tworzy typową konfigurację BeanWrappera (z typowym zestawem
         * pluginów).
         */
        static BeanWrapper *create (const Core::Variant &bean = Core::Variant ());

/*------IPropertyAccessor---------------------------------------------------------*/

        /**
         * Ustawia pole (property), lub cały obiekt, jeśli ścieżka to "".
         * Zrzuci wyjatek (narazie AssertionException), gdy ustawiamy
         * property, a wrapowany obiektjest none lub nie null. Czyli
         * gdy object.isNone () || object.isNull ().
         */
        virtual bool set (const std::string &path, const Core::Variant &object, Core::DebugContext *ctx = NULL);
        virtual bool set (Core::Variant *bean, const std::string &path, const Core::Variant &object, Core::DebugContext *ctx = NULL);

        /**
         * Zwraca pole (property), lub cały obiekt, jeśli ścieżka to "".
         * Zrzuci wyjatek (narazie AssertionException), gdy ustawiamy
         * property, a wrapowany obiektjest none lub nie null. Czyli
         * gdy object.isNone () || object.isNull ().
         * TODO test, czy faktycznie zrzuca!
         */
        virtual Core::Variant get (const std::string &path, bool *error = NULL, Core::DebugContext *ctx = NULL) const;
        virtual Core::Variant get (const Core::Variant *bean, const std::string &path, bool *error = NULL, Core::DebugContext *ctx = NULL) const;

        virtual bool add (const std::string &path, const Core::Variant &object, Core::DebugContext *ctx = NULL);
        virtual bool add (Core::Variant *bean, const std::string &path, const Core::Variant &object, Core::DebugContext *ctx = NULL);

        virtual Ptr <Core::IIterator> iterator (const std::string &path, bool *error = NULL, Core::DebugContext *ctx = NULL) const;
        virtual Ptr <Core::IIterator> iterator (const Core::Variant *bean, const std::string &path, bool *error = NULL, Core::DebugContext *ctx = NULL) const;

/*------IBeanWrapper--------------------------------------------------------*/

        virtual void setWrappedObject (const Core::Variant &object) { wrappedObject = object; }
        virtual Core::Variant getWrappedObject () const { return wrappedObject; }

/*--------------------------------------------------------------------------*/

        /**
         *  Zamienia na postac stringowa - do debagowania.
         */
        std::string toString () const;

/*------BeanWrapper-setters/getters-------------------------------------*/

        void addPlugin (IBeanWrapperPlugin *plugin) { pluginList.push_back (plugin); }

        /**
         * Opcjonalny edytor do edytowania (narazie tylko) ustawianych obiektów. Jeśli jest ustawiony,
         * to kazdy ustawiany za pomocą set obiekt jest przepuszczany przez ten edytor (przynajmniej w
         * niektórych pluginach).
         */
        Editor::IEditor *getEditor () const { return editor; }
        void setEditor (Editor::IEditor *e) { editor = e; }

protected:

/*------Helper-methods------------------------------------------------------*/

        Core::Variant get (const Core::Variant &referenceObject, Common::IPath *path, bool *error, Core::DebugContext *ctx) const;
        bool set (Core::Variant *referenceObject, Common::IPath *path, const Core::Variant &v, Core::DebugContext *ctx);
        bool add (Core::Variant *referenceObject, Common::IPath *path, const Core::Variant &v, Core::DebugContext *ctx);
        Core::Variant iterator (const Core::Variant &referenceObject, Common::IPath *path, bool *error, Core::DebugContext *ctx) const;

        /**
         *  Koncowe i ostateczne  pobranie wartosci tokens z beana input.
         */
        Core::Variant getObjectUsingPlugins (const Core::Variant &input, Common::IPath *path, bool *error, Core::DebugContext *ctx, bool iter = false) const;

        /**
         *  Koncowe i ostateczne ustawienie wartosci property object obiektowi input.
         */
        bool setObjectUsingPlugins (Core::Variant *bean, Common::IPath *path, const Core::Variant &object, Core::DebugContext *ctx, bool add = false);

/*--------------------------------------------------------------------------*/

private:

        /**
         * Wrapowany bean.
         */
        Core::Variant wrappedObject;

        /**
         *  Strategia do wyciagania obiektow.
         */
        BeanWrapperPluginVector pluginList;
        Editor::IEditor *editor;
        bool deleteContents;
};

/****************************************************************************/

#define setError(error)        \
        if (error) {           \
                *error = true; \
        }

#define clearError(error)        \
        if (error) {             \
                *error = false;  \
        }

} // namespace

#endif

