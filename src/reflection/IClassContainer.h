/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICLASSCONTAINER_H_
#define ICLASSCONTAINER_H_

#include "../core/IToStringEnabled.h"
#include "../core/string/String.h"
#include "../core/Pointer.h"

namespace Reflection {

class Class;

struct IClassContainer : public Core::IToStringEnabled {
        virtual ~IClassContainer () {}

        virtual Class *get (const std::string &className) const = 0;
        virtual Class *get (std::type_info const &t) const = 0;

        virtual void add (Class *clazz) = 0;
};

} // nam

#	endif /* ICLASSCONTAINER_H_ */
