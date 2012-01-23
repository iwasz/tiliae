/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STRINGCONSTRUCTOREDITOR_H_
#define STRINGCONSTRUCTOREDITOR_H_

#include "IEditor.h"
#include "../core/ApiMacro.h"

namespace Editor {

/**
 * Coś jak factory editor z podpiętym na stałem ReflectionFactrory, ale oczekuje
 * konstruktora przyjmującego std::string.
 */
class TILIAE_API StringConstructorEditor : public IEditor {
public:

        virtual ~StringConstructorEditor () {}
        virtual void convert (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL);

};

}

#	endif /* STRINGCONSTRUCTOREDITOR_H_ */
