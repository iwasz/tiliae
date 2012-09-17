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
#include "editor/IEditor.h"
#include "core/variant/Variant.h"
#include "core/variant/Cast.h"

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
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);
};

template <typename From, typename To>
bool LexicalEditor <From, To>::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        assert (output);

        try {
                *output = Core::Variant (boost::lexical_cast <To> (vcast <From> (input)));
        }
        catch (std::exception const &e) {
                dcError (context, std::string ("LexicalEditor <") + typeid (From).name () +
                                std::string (", ") + typeid (To).name () + ">::convert. Exception : " +
                                e.what () + std::string (". Input variant : ") + input.toString () +
                                ", output variant : " + output->toString ());
                return false;
        }

        return true;
}

/*##########################################################################*/

template <>
class TILIAE_API LexicalEditor <std::string, bool> : public IEditor {
public:

        virtual ~LexicalEditor () {}
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

};

template <>
class TILIAE_API LexicalEditor <Core::String, bool> : public IEditor {
public:

        virtual ~LexicalEditor () {}
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

};

}

#endif /* STRINGTOINTEDITOR_H_ */
