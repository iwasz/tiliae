/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IRULE_H_
#define IRULE_H_

#include <String.h>
#include <StringList.h>

#include "PathPair.h"
#include "IEditor.h"

namespace Editor {


class IRule {
public:

        virtual ~IRule () {}

        virtual Core::String getOutputPath (const Core::String &inputPath) const = 0;

        virtual IEditor *getEditor (const Core::String &inputPath) const = 0;

        virtual bool supports (const Core::String &inputPath) const = 0;

        virtual PathPair splitPath (const Core::String &inputPath) const = 0;

        virtual Core::StringList getInputs () const = 0;

};

}

#endif /* IRULE_H_ */
