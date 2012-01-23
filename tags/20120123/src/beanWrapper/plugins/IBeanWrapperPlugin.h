/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IBEANWRAPPERPLUGIN_481011_H
#define IBEANWRAPPERPLUGIN_481011_H

#include <list>
#include "path/IPath.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"
#include "../../common/Context.h"
#include "../../editor/IEditor.h"
#include "Reflection.h"
#include "../../core/Object.h"

/****************************************************************************/

namespace Wrapper {

/**
 *  Ten interfejs reprezentuje kawalek funkcjonalnosci operujacej
 *  na BeanWrapperze.
 *
 *  BeanWrapper trzyma liste takich pluginow i dla kazdego tokena
 *  wykonuje cala liste pluginow, do momentu az tokenow zabraknie.
 *  Obowiazkiem kazdego plugina, procz ywkonania rzadania set/get
 *  jest wiec takze skracanie listy tokenow, ktora bedzie wykorzystana
 *  Wiecej info jak to dziala w BeanWrapper.
 *
 *  Jest to implementacja wzorca projektowego chain of responsibility.
 *  Pluginy mozna bowiem laczyc w lancuch, i przekazujac zadanie
 *  set lub get do pierwszego z nich, uruchomic caly lancuch.
 *  Lancuch dziala tak, ze jesli pierwszemu pluginowi nie uda sie
 *  soelnic zadania, to przekazuje je do nastepnego plugina.
 */
class TILIAE_API IBeanWrapperPlugin : public Core::Object {
public:

        virtual ~IBeanWrapperPlugin () {}

        /**
         *  Pobiera wartość pola o ściżce path z beana bean.
         *  \param bean Obiekt z ktorego ta metoda wyciaga dane.
         *  \param path Ścieżka do pola w obiekcie bean do pobrania.
         *  \param ctx Wskaźnik do kontekstu. Kontekst jest to obiekt,
         *  który zawiera pola we/wy, które mogą być ustawiane przez pluginy.
         *  Pośredniczy między pluginami i kodem, który ich używa (czyli
         *  BeanWrapperem). Zawiera status (czy wszystko się powiodło) oraz
         *  message z ewentualnym błędem.
         *  Jeżeli ctx nie jest null, to plugin powinien ustawić status ERROR
         *  lub OK, w zależności od tego czy operacja się powiodła, czy nie.
         */
        virtual Core::Variant get (const Core::Variant &bean,
                                 Common::IPath *path,
                                 Common::Context *ctx,
                                 Editor::IEditor *editor = NULL) const = 0;

        /**
         * Gets iterator.
         */
        virtual Core::Variant iterator (const Core::Variant &bean,
                                        Common::IPath *path,
                                        Common::Context *ctx) const = 0;

        /**
         *  Ustawia.
         *  \returns true Kiedy udalo sie ustawic.
         *  TODO kiedy refleksja bedzie juz poprawiona, to interfejs tej
         *  metody powinien byc inny. Bean powinien byc const Variant &,
         *  tak jak w get. Zmieniamy obiekt *w* wariancie, a nie sam wariant!
         *  \param ctx Wskaźnik do kontekstu. Kontekst jest to obiekt,
         *  który zawiera pola we/wy, które mogą być ustawiane przez pluginy.
         *  Pośredniczy między pluginami i kodem, który ich używa (czyli
         *  BeanWrapperem). Zawiera status (czy wszystko się powiodło) oraz
         *  message z ewentualnym błędem.
         *  Jeżeli ctx nie jest null, to plugin powinien ustawić status ERROR
         *  lub OK, w zależności od tego czy operacja się powiodła, czy nie.
         */
        virtual bool set (Core::Variant *bean,
        		Common::IPath *path,
        		const Core::Variant &objectToSet,
        		Common::Context *ctx,
        		Editor::IEditor *editor = NULL) = 0;

        /**
         * Do kolekcji sekwencyjnych takich jak lista, czy wektor. Dodaje element na koniec.
         */
        virtual bool add (Core::Variant *bean,
                          Common::IPath *path,
                          const Core::Variant &objectToSet,
                          Common::Context *ctx,
                          Editor::IEditor *editor = NULL) = 0;
};

/****************************************************************************/

typedef std::list <Ptr <Wrapper::IBeanWrapperPlugin> > BeanWrapperPluginList;
REFLECTION_COLLECTION (BeanWrapperPluginList)

} // namespace

#endif

