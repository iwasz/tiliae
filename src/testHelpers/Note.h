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

        __c (void);

        _m (getTitle) Core::String getTitle () const { return title; }
        _m (setTitle) void setTitle (const Core::String &title) { this->title = title; }

        _m (getBody) Core::String getBody () const { return body; }
        _m (setBody) void setBody (const Core::String &body) { this->body = body; }

private:

        Core::String title;
        Core::String body;

        _e (Note)

};

#endif

