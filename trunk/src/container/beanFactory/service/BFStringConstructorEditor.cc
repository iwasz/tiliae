/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/lexical_cast.hpp>
#include "BFStringConstructorEditor.h"

namespace Container {

int BFStringConstructorEditor::singletonNumber = 0;

/****************************************************************************/

bool BFStringConstructorEditor::convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        bool success = Editor::StringConstructorEditor::convert (input, output, context);

        if (success) {
                singletons->operator[] (generateId ()) = *output;
        }

        return success;
}

/****************************************************************************/

const char *BFStringConstructorEditor::generateId () const
{
        std::string myId = "SCE" + boost::lexical_cast <std::string> (singletonNumber++);
        char *idCopy = (char *)allocator->malloc (myId.length () + 1);
        strcpy (idCopy, myId.c_str ());
        return idCopy;
}

} /* namespace Container */
