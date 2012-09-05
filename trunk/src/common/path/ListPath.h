/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LISTPATH_906907_H
#define LISTPATH_906907_H

#include <list>
#include <string>

#include "IPath.h"

namespace Common {

/**
 * Rozbija podany string an listę. Uwaga
 */
class TILIAE_API ListPath : public IPath {
public:

        ListPath (const char *path = NULL, char separator = '.');
        ListPath (const std::string &path, char separator = '.');
        ListPath (const ListPath &p);

        virtual ~ListPath () {}

        std::string toString () const;

        bool validate () const;
        int countSegments () const;
        void clear ();

        void cutSegment (unsigned int index);
        void cutSegment (const std::string &segmentName);
        void cutAllSegments (const std::string &segmentName);
        void cutLastSegment ();
        void cutFirstSegment ();
        void cutAllButLastSegment ();
        void cutAllButFirstSegment ();

        int findSegmentIndex (const std::string &segmentName) const;
        bool containsSegment (const std::string &segmentName) const;

        std::string getSegment (unsigned int number) const;
        std::string getLastSegment () const;
        std::string getFirstSegment () const;
        std::string getAllButLastSegment () const;
        std::string getAllButFirstSegment () const;
        Core::StringVector splitSegments () const;

        bool isRelative () const { return !absolute; }
        bool isAbsolute () const { return absolute; }

private:
        
        void init (const char *buf, char sep);

private:

        typedef std::list <std::string> List;
        typedef List::iterator Iterator;
        typedef List::const_iterator ConstIterator;

        List body;
        char separator;
        bool absolute;

};

} // namespace

#endif

