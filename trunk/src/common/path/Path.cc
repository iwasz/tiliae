/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <StringUtils.h>
#include <cassert>
#include <boost/algorithm/string/trim.hpp>
#include "Path.h"

namespace Common {

Path::Path (const std::string &path, char sep) :
                separator (sep)
{
        original = body = path;
        separatorStr += sep;

        if (!body.empty () && static_cast <char> (body[0]) == sep) {
                body.erase (0, 1);
        }

        if (!body.empty () && static_cast <char> (body[body.length () - 1]) == sep) {
                body.resize (body.length () - 1);
        }

        updateFirstSegmentCache ();
        if (!validate ()) {
                throw PathException ("Probowano utworzyc obiekt Path (sziezke), ale nie przeszla ona wewnetrznej walidacji. Sciezka : (" + body + ")");
        }
}

Path::Path (const Path &p)
{
        body = p.body;
        separator = p.separator;
        separatorStr = p.separatorStr;
        updateFirstSegmentCache ();
}

/****************************************************************************/

std::string Path::toString () const
{
        return body;
}

/****************************************************************************/

bool Path::validate () const
{
        // Wyjatek od reguly. Dopuszczamy puste.
        if (body.empty ()) {
                return true;
        }

        // Wlasciwie, to sprawdzamy tylko, czy sciezka nie zawiera pustych segmentow.
        std::string::size_type posBegin = 0;
        std::string::size_type prevPos = 0;

        //std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "--" << std::endl;

        while (posBegin != std::string::npos) {

                prevPos = posBegin;
                // Pozycja i-tej kropki (od 0)
                posBegin = body.find (separatorStr, (!posBegin) ? (0) : (posBegin + 1));

                //std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << posBegin << " " << prevPos << std::endl;

                if (!posBegin ||
                                ((prevPos) && ((posBegin - prevPos) == 1)) ||
                                ((!prevPos) && ((posBegin - prevPos) == 0)) ||
                                posBegin == body.size () - 1)
                        return false;

        }

        return true;
}

/****************************************************************************/

int Path::countSegments () const
{
        if (/*!validate () || */body.empty ())
                return 0;

        // Warning lecial bez kastowania na unsigned char
        return std::count (body.begin (), body.end (), (unsigned char)separator) + 1;
}

/****************************************************************************/

void Path::cutSegment (unsigned int index)
{
        if (/*!validate () || */body.empty ())
                return;

        int cutBeginInt = segmentStringPosition (index);
        std::string::size_type cutBegin = cutBeginInt;

        if (cutBeginInt < 0)
                return;

        std::string::size_type cutEnd = body.find (separatorStr, cutBegin + 1);

        // Wytnij takze wiodaca krope
        if (cutBegin != 0)
                cutBegin--;

        // Wytnij krope po.
        if (cutEnd != std::string::npos)
                cutEnd++;

        body = body.substr (0, cutBegin) +
                ((cutBegin && cutEnd != std::string::npos) ? separatorStr : "") +
                ((cutEnd != std::string::npos) ? body.substr (cutEnd) : "");

        updateFirstSegmentCache ();
}

/****************************************************************************/

void Path::cutSegment (const std::string &segmentName)
{
        if (/*!validate () || */body.empty ())
                return;

        int cutBegin = segmentStringPosition (segmentName);

        if (cutBegin < 0)
                return;

        std::string::size_type cutEnd = cutBegin + segmentName.size ();

        // Wytnij takze wiodaca krope
        if (cutBegin != 0)
                cutBegin--;

        if (cutEnd >= body.size ()) {
                cutEnd = body.size ();
        }
        else {
                cutEnd++;
        }

        body = body.substr (0, cutBegin) +
                ((cutBegin && cutEnd < body.size ()) ? separatorStr : "") +
                ((cutEnd != std::string::npos) ? body.substr (cutEnd) : "");

        updateFirstSegmentCache ();
}

/****************************************************************************/

void Path::cutAllSegments (const std::string &segmentName)
{
        if (/*!validate () || */body.empty ())
                return;

        while (segmentStringPosition (segmentName) != -1) {
                cutSegment (segmentName);
        }
}

/****************************************************************************/

void Path::cutLastSegment ()
{
        int count = countSegments ();

        if (!count)
                return;

        cutSegment (count - 1);
}

/****************************************************************************/

void Path::cutFirstSegment ()
{
        return cutSegment (0);
}

/****************************************************************************/

void Path::cutAllButLastSegment ()
{
        body = getLastSegment ();
        updateFirstSegmentCache ();
}

/****************************************************************************/

void Path::cutAllButFirstSegment ()
{
        body = getFirstSegment ();
        updateFirstSegmentCache ();
}

/****************************************************************************/

int Path::segmentStringPosition (const std::string &segmentName) const
{
        std::string::size_type i = body.find (segmentName);
        std::string::size_type sDot = segmentName.find (separatorStr);
        std::string::size_type sSize = segmentName.size ();

        if (/*!validate () || */body.empty ())
                return -1;

        // Szukany segment nie moze zawierac kropki! Bo wtedy to bylyby 2 segmenty!
        if (sDot != std::string::npos)
                return -1;

        if (i == std::string::npos)
                return -1;

        if (i != 0 && static_cast <char> (body[i - 1]) != separator)
                return -1;

        // Nie dopuszczamy pustych segmentow. Jezli dopuszczamy, to trzeba usunac w 1 kolejnosci.
        if (!sSize)
                return -1;

        if (i + sSize < body.size () && static_cast <char> (body[i + sSize]) != separator)
                return -1;

        return i;
}

/****************************************************************************/

int Path::segmentStringPosition (int number) const
{
        if (/*!validate () || */body.empty ())
                return -1;

        if (!number)
                return 0;

        if (number < 0)
                return -1;

        std::string::size_type posBegin = 0;

        for (int i = 0; i < number; i++) {

                // Pozycja i-tej kropki (od 1)
                posBegin = body.find (separatorStr, posBegin + 1);

                // Jesli nie przerwiemy, to find zacznie szukac od poczatku!
                if (posBegin == std::string::npos)
                        break;

        }

        if (posBegin == std::string::npos || posBegin >= body.size ())
                return -1;

        return posBegin + 1;
}

/****************************************************************************/

int Path::findSegmentIndex (const std::string &segmentName) const
{
        if (/*!validate () || */body.empty ())
                return -1;

        int position = segmentStringPosition (segmentName);

        if (position == -1)
                return -1;

        int count = 0;
        for (int i = position; i > 0; i--) {
                if (static_cast <char> (body[i]) == separator)
                        count++;
        }

        return count;
}

/****************************************************************************/

std::string Path::getSegment (unsigned int number) const
{
        if (/*!validate () || */body.empty ())
                return std::string ();

        int cutBegin = segmentStringPosition (number);

        if (cutBegin < 0)
                return std::string ();;

        std::string::size_type cutEnd = body.find (separatorStr, cutBegin);

        if (cutEnd >= body.size () || cutEnd == std::string::npos) {
                cutEnd = body.size ();
        }

        return body.substr (cutBegin, cutEnd - cutBegin);
}

/****************************************************************************/

std::string Path::getLastSegment () const
{
        int count = countSegments ();

        if (count <= 0)
                return std::string ();

        return getSegment (count - 1);
}

/****************************************************************************/

//std::string Path::getFirstSegment () const
void Path::updateFirstSegmentCache () const
{
        int count = countSegments ();

        if (count <= 0) {
                firstSegmentCache = "";
        }

        firstSegmentCache = getSegment (0);
}

/****************************************************************************/

std::string Path::getAllButLastSegment () const
{
        Path tmp = *this;
        tmp.cutLastSegment ();
        return tmp;
}

/****************************************************************************/

std::string Path::getAllButFirstSegment () const
{
        Path tmp = *this;
        tmp.cutFirstSegment ();
        return tmp;
}

/****************************************************************************/

Core::StringVector Path::splitSegments () const
{
        if (/*!validate () || */body.empty ())
                return Core::StringVector ();

        return StringUtils::split (body, separatorStr);
}

/****************************************************************************/

bool Path::containsSegment (const std::string &segmentName) const
{
        if (/*!validate () || */body.empty ())
                return false;

        return segmentStringPosition (segmentName) != -1;
}

/****************************************************************************/

bool Path::isRelative () const
{
        std::string tmp = boost::algorithm::trim_copy (original);

        if (tmp.empty ()) {
                return false;
        }

        // TODO Te static_cast nie będą potrzebne jeśli zamienimy wszytsko na std::string!
        return static_cast <char> (tmp[0]) != separator;
}

/****************************************************************************/

bool Path::isAbsolute () const
{
        std::string tmp = boost::algorithm::trim_copy (original);

        if (tmp.empty ()) {
                return false;
        }

        return static_cast <char> (tmp[0]) == separator;
}

} // namespace

