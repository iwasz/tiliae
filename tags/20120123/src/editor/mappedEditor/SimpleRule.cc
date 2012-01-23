/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <path/Path.h>

#include "SimpleRule.h"
#include "PathPair.h"

using namespace Core;

namespace Editor {

Core::String SimpleRule::getOutputPath (const Core::String &inputPath) const
{
        if (inputPath == this->inputPath) {
                return outputPath;
        }

        return "";
}

/****************************************************************************/

bool SimpleRule::supports (const Core::String &inputPath) const
{
        if (inputPath == this->inputPath) {
                return true;
        }

        return false;
}

/****************************************************************************/

PathPair SimpleRule::splitPath (const Core::String &inputPath) const
{
        Common::Path p1 (inputPath);

        /*
         * TODO ta implementacja jest uproszczona i tak nie bedzie.
         * Trzeba obsluzyc sciezki, ktore maja wiecej niz jeden segment.
         */
        PathPair ret;
        ret.first = this->inputPath;

        if (p1.getFirstSegment () == this->inputPath) {
                ret.second = p1.getAllButFirstSegment ();
        }

        return ret;
}

/****************************************************************************/

Core::StringList SimpleRule::getInputs () const
{
        StringList ret;
        ret.add (inputPath);
        return ret;
}

}
