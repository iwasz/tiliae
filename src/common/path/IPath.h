/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IPATH_461984_H
#define IPATH_461984_H

#include "core/string/String.h"
#include "core/Typedefs.h"
#include "core/IToStringEnabled.h"
#include "core/Exception.h"
#include "core/ApiMacro.h"

namespace Common {

/**
 * Ścieżki, czyli napisy rozdzielone separatorami. Ścieżki są to napisy, które
 * skłądają się z segmentów. W Tiliae najczęściej używane są kropki jako separatory
 * na przykłąd w BeanWrapper.
 */
class TILIAE_API IPath : public Core::IToStringEnabled {
public:

        virtual ~IPath () {}

        virtual bool validate () const = 0;
        virtual int countSegments () const = 0;
        virtual void clear () = 0;

        virtual void cutSegment (unsigned int index) = 0;
        virtual void cutSegment (const std::string &segmentName) = 0;
        virtual void cutAllSegments (const std::string &segmentName) = 0;
        virtual void cutLastSegment () = 0;
        virtual void cutFirstSegment () = 0;
        virtual void cutAllButLastSegment () = 0;
        virtual void cutAllButFirstSegment () = 0;

        /// Zwraca index segmentu (kolejnosć)
        virtual int findSegmentIndex (const std::string &segmentName) const = 0;
        virtual bool containsSegment (const std::string &segmentName) const = 0;

        virtual std::string getSegment (unsigned int number) const = 0;
        virtual std::string getLastSegment () const = 0;
        virtual std::string getFirstSegment () const = 0;
        virtual std::string getAllButLastSegment () const = 0;
        virtual std::string getAllButFirstSegment () const = 0;
        virtual Core::StringVector splitSegments () const = 0;

        virtual bool isRelative () const = 0;
        virtual bool isAbsolute () const = 0;
};

/**
 * Wyjątek dla ścieżek. Zrzucany w różnych przypadkach, zawiera informację
 * co poszło nie tak.
 */
class TILIAE_API PathException : public Core::Exception {
public:

        PathException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~PathException () throw () {}
};

} // namespace

#endif

