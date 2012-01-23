/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LEXICAL_EDITOR_H_
#define LEXICAL_EDITOR_H_

#include <cassert>
#include <boost/lexical_cast.hpp>
#include "IEditor.h"
#include "../core/variant/Variant.h"
#include "../core/variant/Cast.h"

namespace Editor {

/**
 * Klasa konwertująca string na różne typy.
 */
template <typename From, typename To>
class LexicalEditor : public IEditor {
public:

        virtual ~LexicalEditor () {}

        /**
         * @param input Konwertowalny na Core::String.
         * @param output Wskaźnik do dowolnego wariantu (może być isNone ()).
         */
        virtual void convert (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL);
};

template <typename From, typename To>
void LexicalEditor <From, To>::convert (const Core::Variant &input, Core::Variant *output, Core::Context *context)
{
        assert (output);

        try {
                *output = Core::Variant (boost::lexical_cast <To> (vcast <From> (input)));
        }
        catch (std::exception const &e) {
                error (context, EditorException, Common::UNDEFINED_ERROR, std::string ("LexicalEditor <") + typeid (From).name () +
                                std::string (", ") + typeid (To).name () + ">::convert. Exception : " +
                                e.what () + std::string (". Input variant : ") + input.toString () +
                                ", output variant : " + output->toString ());
        }
}

/*##########################################################################*/

template <>
class TILIAE_API LexicalEditor <std::string, bool> : public IEditor {
public:

        virtual ~LexicalEditor () {}
        virtual void convert (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL);

};

template <>
class TILIAE_API LexicalEditor <Core::String, bool> : public IEditor {
public:

        virtual ~LexicalEditor () {}
        virtual void convert (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL);

};

}

#endif /* STRINGTOINTEDITOR_H_ */
