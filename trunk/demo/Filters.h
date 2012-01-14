/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PRINTERS_H_
#define PRINTERS_H_

#include <string>
#include "Reflection.h"

/**
 * Unfortunately Core::Object is required to vcast work properly.
 */
struct IFilter : public Core::Object {
        virtual ~IFilter () {}
        virtual std::string filter (std::string const &) = 0;
};

/**
 *
 */
struct BracketFilter : public IFilter {
        virtual ~BracketFilter () {}
        virtual std::string filter (std::string const &s) { return "(" + s + ")"; }

        e__ (BracketFilter)
};

/**
 *
 */
struct StupidFilter : public IFilter {
        virtual ~StupidFilter () {}
        virtual std::string filter (std::string const &s) { return "[[[" + s + "]]]"; }

        e__ (StupidFilter)
};

#	endif /* PRINTERS_H_ */
