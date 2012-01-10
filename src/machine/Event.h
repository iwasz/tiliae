/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STM_EVENT_H_
#define STM_EVENT_H_

#include <string>
#include "../core/Typedefs.h"

namespace Machine {

class Event {
public:

        Event () {}
        Event (std::string const &n) : name (n) {}
        Event (std::string const &n, Core::VariantMap const &p) : name (n), params (p) {}

        std::string const &getName () const { return name; }
        void setName (std::string const &name) { this->name = name; }

        Core::VariantMap const &getParams () const { return params; }
        void setParams (Core::VariantMap const &params) { this->params = params; }

private:

        std::string name;
        Core::VariantMap params;

};

}

#	endif /* EVENT_H_ */
