/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NOOPEDITOR_H_
#define NOOPEDITOR_H_

#include <cassert>
#include "IEditor.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Editor {

/**
 * Po prostu nie moze zabraknac takiego cudenka. Należy
 * pamiętać, że wariant wejściowy jest kopiowany na wyjściowy.
 * Jeżeli więc wejściowy zawiera wskaźnik, to kopiowanie
 * będzie tanie. Jesli jednak ciężką wartość, to kopiowanie
 * może być kosztowne.
 */
struct TILIAE_API NoopEditor : public IEditor {

        NoopEditor (bool c = true) : copy (c) {}
        virtual ~NoopEditor () {}

        static Ptr <NoopEditor> create (bool c = true) { return Ptr <NoopEditor> (new NoopEditor (c)); }

        virtual void convert (const Core::Variant &input, Core::Variant *output, Common::Context *context = NULL)
        {
                if (copy) {
                        assert (output);
                        *output = input;
                }
        }

        /**
         * Copy jest domyślnie na true. Powoduje, że input jest kopiowany na
         * output. Jeżeli copy ustawimy na false, to nawet ta operacja nie
         * będzie wykonana (czyli convert nie zrobi absolutnie nic).
         */
        bool getCopy () const { return copy; }
        void setCopy (bool copy) { this->copy = copy; }

private:

        bool copy;

};

}

#endif /* NOOPEDITOR_H_ */
