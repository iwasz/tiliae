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

        c__ (void);

        m_ (getTitle) Core::String getTitle () const { return title; }
        m_ (setTitle) void setTitle (const Core::String &title) { this->title = title; }

        m_ (getBody) Core::String getBody () const { return body; }
        m_ (setBody) void setBody (const Core::String &body) { this->body = body; }

private:

        Core::String title;
        Core::String body;

        e_ (Note)

};

#endif

