/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GETPUTMETHODRWBEANWRAPPERPLUGIN_498_H
#define GETPUTMETHODRWBEANWRAPPERPLUGIN_498_H

#include <Reflection.h>
#include "IBeanWrapperPlugin.h"
#include "../../core/ApiMacro.h"

namespace Wrapper {

/**
 *  To jest plugin, ktory potrafi odczytac zapisac propertu do
 *  obiektow, ktore maja metody get i set. Jest to element analogiczny
 *  do PropertyRWBeanWrapperPlugin, tylko samiast setterow i getterow
 *  uzywa metod get / set.
 */
class TILIAE_API GetPutMethodRWBeanWrapperPlugin : public IBeanWrapperPlugin {
public:
        __c (void)

        GetPutMethodRWBeanWrapperPlugin (bool g = false) : greedy (g) {}
        virtual ~GetPutMethodRWBeanWrapperPlugin () {}

        virtual Core::Variant get (const Core::Variant &bean,
                                   Common::IPath *path,
                                   Common::Context *ctx = NULL,
                                   Editor::IEditor *editor = NULL) const;

        virtual bool set (Core::Variant *bean,
                          Common::IPath *path,
                          const Core::Variant &objectToSet,
                          Common::Context *ctx = NULL,
                          Editor::IEditor *editor = NULL);

        virtual bool add (Core::Variant *bean,
                          Common::IPath *path,
                          const Core::Variant &objectToSet,
                          Common::Context *ctx,
                          Editor::IEditor *editor = NULL);

        /**
         * Tells if plugin should consume all remaining segments of given path (true) or
         * only one segment.
         */
        bool isGreedy () const { return greedy; }
        _m (setGreedy) void setGreedy (bool greedy) { this->greedy = greedy; }

private:

        bool greedy;

        _e (GetPutMethodRWBeanWrapperPlugin)
};


} // namespace

#endif

