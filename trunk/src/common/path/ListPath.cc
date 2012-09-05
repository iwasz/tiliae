/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <ctype.h>
#include <algorithm>
#include <cassert>

#include "ListPath.h"
#include "../StringUtils.h"

namespace Common {

void ListPath::init (const char *buf, char sep)
{
        enum State { BEG, SEP, SEGM, ADD, END };
        State state = BEG;
        separator = sep;
        absolute = false;

        char c;
        std::string segment;

        if (!buf) {
                return;
        }

        for (int i = 0; (c = *(buf + i));) {

                switch (state) {
                case BEG:
                        if (isspace(c)) {
                                i++;
                                continue;
                        }
                        if (c == separator) {
                                absolute = true;
                                state = SEP;
                                continue;
                        }

                        state = SEGM;
                        break;

                case SEP:
                        i++;
                        segment.clear ();
                        state = SEGM;
                        break;

                case SEGM:
                        if (c != separator) {
                                i++;
                                segment.push_back (c);
                                continue;
                        }

                        state = ADD;
                        break;

                case ADD:
                        if (segment.empty ()) {
                                throw PathException ("Segment is emty.");
                        }
                        body.push_back (segment);
                        state = SEP;
                        break;

                default:
                        break;
                }

        }

        // Dodaj ostatni segment;
        if (!segment.empty ()) {
                body.push_back (segment);
        }
}

/****************************************************************************/

ListPath::ListPath (const char *path, char separator)
{
        init (path, separator);
}

/****************************************************************************/

ListPath::ListPath (const std::string &path,char separator)
{
        init (path.c_str (), separator);
}

/****************************************************************************/

ListPath::ListPath (const ListPath &p)
{
        body = p.body;
        separator = p.separator;
}

/****************************************************************************/

bool ListPath::validate () const
{
        return true;
}

/****************************************************************************/

std::string ListPath::toString () const
{
        return StringUtils::join (body, std::string (1, separator));
}

/****************************************************************************/

int ListPath::countSegments () const
{
        return body.size ();
}

/****************************************************************************/

void ListPath::clear ()
{
        body.clear ();
}

/****************************************************************************/

void ListPath::cutSegment (unsigned int index)
{
        if (index  >= body.size ()) {
                return;
        }

        Iterator i = body.begin ();
        std::advance (i, index);
        body.erase (i);
}

/****************************************************************************/

void ListPath::cutSegment (const std::string &segmentName)
{
        Iterator i = std::find (body.begin (), body.end (), segmentName.c_str());

        if (i == body.end ()) {
                return;
        }

        body.erase (i);
}

/****************************************************************************/

void ListPath::cutAllSegments (const std::string &segmentName)
{
        Iterator next;
        for (Iterator i = body.begin (); i != body.end (); ) {
                next = i;
                next++;

                if (*i == segmentName) {
                        body.erase (i);
                }
                i = next;
        }
}

/****************************************************************************/

void ListPath::cutLastSegment ()
{
        int count = countSegments ();

        if (!count) {
                return;
        }

        cutSegment (count - 1);
}

/****************************************************************************/

void ListPath::cutFirstSegment ()
{
        cutSegment (0);
}

/****************************************************************************/

void ListPath::cutAllButLastSegment ()
{
        if (body.empty ()) {
                return;
        }

        body.front () = body.back ();
        body.resize (1);
}

/****************************************************************************/

void ListPath::cutAllButFirstSegment ()
{
        body.resize (1);
}

/****************************************************************************/

int ListPath::findSegmentIndex (const std::string &segmentName) const
{
        ConstIterator i = std::find (body.begin (), body.end (), segmentName.c_str());

        if (i == body.end ()) {
                return -1;
        }

        return std::distance(body.begin (), i);
}

/****************************************************************************/

bool ListPath::containsSegment (const std::string &segmentName) const
{
        ConstIterator i = std::find (body.begin(), body.end(), segmentName);
        return i != body.end ();
}

/****************************************************************************/

std::string ListPath::getSegment (unsigned int index) const
{
        if (index  >= body.size ()) {
                return "";
        }

        ConstIterator i = body.begin ();
        std::advance (i, index);
        return *i;
}

/****************************************************************************/

std::string ListPath::getLastSegment () const
{
        if (body.empty ()) {
                return "";
        }

        return body.back ();
}

/****************************************************************************/

std::string ListPath::getFirstSegment () const
{
        if (body.empty ()) {
                return "";
        }

        return body.front ();
}

/****************************************************************************/

std::string ListPath::getAllButLastSegment () const
{
        if (body.empty ()) {
                return "";
        }

        List tmp = body;
        tmp.resize (body.size () - 1);
        return StringUtils::join (tmp, std::string ("") + separator);
}

/****************************************************************************/

std::string ListPath::getAllButFirstSegment () const
{
        if (body.empty ()) {
                return "";
        }

        List tmp = body;
        tmp.erase (tmp.begin ());
        return StringUtils::join (tmp, std::string ("") + separator);
}

/****************************************************************************/

Core::StringVector ListPath::splitSegments () const
{
        Core::StringVector ret;
        ret.resize (body.size ());
        std::copy (body.begin (), body.end (), ret.begin ());
        return ret;
}

} // namespace

