/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NOTE_181772_H
#define NOTE_181772_H

#include "reflection/Reflection.h"
#include <string>
#include "core/ApiMacro.h"

/****************************************************************************/

class TILIAE_API __tiliae_reflect__ Note {
public:

        REFLECTION_CONSTRUCTOR_ (void);

        REFLECTION_METHOD (getTitle) std::string getTitle () const { return title; }
        REFLECTION_METHOD (setTitle) void setTitle (const std::string &title) { this->title = title; }

        REFLECTION_METHOD (getBody) std::string getBody () const { return body; }
        REFLECTION_METHOD (setBody) void setBody (const std::string &body) { this->body = body; }

private:

        std::string title;
        std::string body;

        REFLECTION_END (Note)

};

#endif

