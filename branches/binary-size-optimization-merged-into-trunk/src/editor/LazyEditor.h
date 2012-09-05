/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LAZY_EDITOR_H_
#define LAZY_EDITOR_H_

#include "IEditor.h"
#include "../core/variant/Cast.h"
#include "../core/Pointer.h"
#include "../factory/IFactory.h"
#include "../core/ApiMacro.h"

namespace Editor {

/**
 * To działa w prosty sposób:
 * 1. Uruchomienie convert powoduje uruchomienie fabryki factory, która tworzy obiekt.
 * 2. Obiekt jest kastowany na IEditor.
 * 3. Konwersja jest delegowana do tego nowego edytora.
 * TODO Test.
 */
class TILIAE_API LazyEditor : public IEditor {
public:

        LazyEditor (Factory::IFactory *f, bool d = false) : factory (f), deleteContents (d) {}
        virtual ~LazyEditor ()
        {
                if (deleteContents) {
                        delete factory;
                }
        }

/*--------------------------------------------------------------------------*/

        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL)
        {
                assert (factory);
                Core::Variant vEd = factory->create (Core::VariantMap (), context);

                if (!occast <IEditor *> (vEd)) {
                        dcError (context, "LazyEditor::convert !occast <Ptr <IEditor> > (vEd). vEd : " + vEd.toString ());
                        return false;
                }

                IEditor *ed = ocast <IEditor *> (vEd);
                return ed->convert (input, output, context);
        }

        Factory::IFactory *getFactory () const { return factory; }
        void setFactory (Factory::IFactory *factory) { this->factory = factory; }

private:

        Factory::IFactory *factory;
        bool deleteContents;
};

}

#endif
