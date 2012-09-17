/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STRINGCONSTRUCTOREDITOR_H_
#define STRINGCONSTRUCTOREDITOR_H_

#include "editor/IEditor.h"
#include "core/ApiMacro.h"
#include "core/allocator/IAllocator.h"

namespace Editor {

/**
 * Coś jak factory editor z podpiętym na stałem ReflectionFactrory, ale oczekuje
 * konstruktora przyjmującego std::string.
 */
class TILIAE_API StringConstructorEditor : public IEditor {
public:

        StringConstructorEditor (Core::IAllocator *a = NULL) : allocator (a) {}
        virtual ~StringConstructorEditor () {}
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

protected:

        Core::IAllocator *allocator;
};

}

#	endif /* STRINGCONSTRUCTOREDITOR_H_ */
