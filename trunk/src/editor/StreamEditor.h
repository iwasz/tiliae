/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_INTEGEREDITOR_H_
#define TILIAE_INTEGEREDITOR_H_

#include <sstream>
#include <boost/algorithm/string/trim.hpp>

namespace Editor {

/**
 * Analogoczny do LexicalCast, ale zaimplementowany na sstream, dzięki czem
 */
template <typename From, typename To>
class StreamEditor : public IEditor {
public:

        virtual ~StreamEditor () {}

        /**
         * @param input Konwertowalny na Core::String.
         * @param output Wskaźnik do dowolnego wariantu (może być isNone ()).
         */
        virtual void convert (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL);
};

template <typename From, typename To>
void StreamEditor <From, To>::convert (const Core::Variant &input, Core::Variant *output, Core::Context *context)
{
        assert (output);

        try {
                // Jakiś rodzaj stringa.
                From inputStr = vcast <From> (input);
                boost::algorithm::trim (inputStr);
                To x;
                std::stringstream ss;

                if (inputStr.size () > 2 && inputStr[0] == '0' && inputStr[1] == 'x') {
                        ss << std::hex << inputStr;
                }
                else {
                        ss << inputStr;
                }

                ss >> x;
                *output = Core::Variant (x);
        }
        catch (std::exception const &e) {
                error (context, EditorException, Common::UNDEFINED_ERROR, std::string ("StreamEditor <") + typeid (From).name () +
                                std::string (", ") + typeid (To).name () + ">::convert. Exception : " +
                                e.what () + std::string (". Input variant : ") + input.toString () +
                                ", output variant : " + output->toString ());
        }
}

}

#	endif /* INTEGEREDITOR_H_ */
