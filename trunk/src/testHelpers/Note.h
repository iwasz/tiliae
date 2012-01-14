/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NOTE_181772_H
#define NOTE_181772_H

#include "Reflection.h"
#include "../core/string/String.h"
#include "../core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API Note {
public:

        REFLECTION_CONSTRUCTOR_ (void);

        REFLECTION_METHOD (getTitle) Core::String getTitle () const { return title; }
        REFLECTION_METHOD (setTitle) void setTitle (const Core::String &title) { this->title = title; }

        REFLECTION_METHOD (getBody) Core::String getBody () const { return body; }
        REFLECTION_METHOD (setBody) void setBody (const Core::String &body) { this->body = body; }

private:

        Core::String title;
        Core::String body;

        REFLECTION_END (Note)

};

#endif

