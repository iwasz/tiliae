/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FACTORYEDITOR_H_
#define FACTORYEDITOR_H_

#include <boost/make_shared.hpp>
#include <cassert>
#include "IEditor.h"
#include "../factory/IFactory.h"
#include "../core/variant/Variant.h"
#include "../core/Pointer.h"
#include "../core/Typedefs.h"
#include "../core/ApiMacro.h"

namespace Editor {

/**
 * Taka moze byc druga wersja interfejsów adaptera (czy jak on tam ma sie nazywac)
 * Taki konwerter zawszeby tworzył to co skonwertuje (w przeciwieństwie do zwykłego
 * adaptera, ktory output musi mieć stworzony).
 *
 * Nie keszujemy outputu! Nie trzymamy juz stworzonego,
 * tylko za kazdym razem tworzymy nowy. Dla czego? Bo jesli
 * chcemy keszowac, to robimy to w fabryce. Nalezy uzyc wtedy
 * SingletonFactory.
 */
class TILIAE_API FactoryEditor : public IEditor {
public:

        FactoryEditor (bool d = false) : deleteContents (d) {}
        FactoryEditor (IEditor *e, Factory::IFactory *f, bool d = false) : editor (e), factory (f), deleteContents (d) {}
        virtual ~FactoryEditor ();

        /**
         * Jesli parametr output jest wariantem, ktory:
         * - Jest pusty,
         * - Jest typu value
         * - Jest typu handle, ale zawiera pusty wskaznk (NULL),
         * To ten edytor uzyje swojej wewnetrznej fabryki.
         * Natomiast w przeciwnym wypadku, to ten edytor zachowa
         * sie jak zwykly edytor, czyli jedynie wywola wewnetrzny
         * edytor..
         */
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

        Factory::IFactory *getFactory () const { return factory; }
        void setFactory (Factory::IFactory *factory) { this->factory = factory; }

        Editor::IEditor *getEditor () const { return editor; }
        void setEditor (Editor::IEditor *editor) { this->editor = editor; }

        Core::VariantMap getFactoryParams () const { return factoryParams; }
        void setFactoryParams (Core::VariantMap factoryParams) { this->factoryParams = factoryParams; }

private:

        Editor::IEditor *editor;
        Factory::IFactory *factory;
        Core::VariantMap factoryParams; // Dubluje funkcjonalność ProxyFactory.
        bool deleteContents;
};

}

#endif /* FACTORYEDITOR_H_ */
