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

        LazyEditor () {}
        LazyEditor (Ptr <Factory::IFactory> f) : factory (f) {}
        virtual ~LazyEditor () {}

/*--------------------------------------------------------------------------*/

        virtual void convert (const Core::Variant &input, Core::Variant *output, bool *error = NULL, Core::DebugContext *context = NULL)
        {
                assert (factory);
                Core::Variant vEd = factory->create (Core::VariantMap (), context);

                if (!occast <Ptr <IEditor> > (vEd)) {
                        dcError (context, "LazyEditor::convert !occast <Ptr <IEditor> > (vEd). vEd : " + vEd.toString ());
                        setError (error);
                        return;
                }

                Ptr <IEditor> ed = ocast <Ptr <IEditor> > (vEd);
                ed->convert (input, output, error, context);
        }

        Ptr <Factory::IFactory> getFactory () const { return factory; }
        void setFactory (Ptr <Factory::IFactory> factory) { this->factory = factory; }

private:

        Ptr <Factory::IFactory> factory;
};

}

#endif
