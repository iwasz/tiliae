/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_REFLECT_TOOLS_H
#define TILIAE_REFLECT_TOOLS_H

#include "Exceptions.h"
#include "../core/Typedefs.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

namespace Reflection {

struct TILIAE_API Tools {

        static void checkArgList (Core::VariantVector *list, unsigned int size)
        {
                if (!list) {
                        if (!size) {
                                return; // Wszystko OK
                        }

                        throw WrongNumberOfArgumentsException (-1, size);
                }

                if (list->size () != size) {
                        throw WrongNumberOfArgumentsException (list->size (), size);
                }
        }

};

}

#endif

