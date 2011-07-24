/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#include <boost/lexical_cast.hpp>
#include "Context.h"
#include "Exceptions.h"
#include "../core/variant/Cast.h"
#include "../beanWrapper/IBeanWrapper.h"
#include "../beanWrapper/plugins/MethodPlugin.h"

namespace k202 {

void Context::setArgsMap (Core::VariantMap *argsMap)
{
        this->argsMap = argsMap;
        mapAsVariant = Core::Variant (argsMap);
}

/****************************************************************************/

Core::Variant Context::getParam (unsigned int idx) const
{
        if (!paramVector) {
                throw RuntimeException ("RuntimeException : Context::paramList is null but Context::getParam invoked.");
        }

        if (paramVector->size () <= idx || idx < 0) {
                throw RuntimeException (std::string ("RuntimeException : Context::paramList has ") +
                                boost::lexical_cast <std::string> (paramVector->size ()) +
                                " elements, but [" + boost::lexical_cast <std::string> (idx) +
                                "] requested.");
        }

        return paramVector->operator [] (idx);
}

/****************************************************************************/

Core::Variant Context::getArg (const std::string &path, bool conditional) const
{
        using Common::Context;

        Context bwContext;
        Core::Variant ret;

        if (domain && !domain->isNone ()) {
                ret = bwrap.get ()->get (domain, path, &bwContext);

                if (!bwContext.isError ()) {
                        return ret;
                }
        }

        bwContext.clear ();
        if (ret.isNone () && argsMap && !argsMap->empty ()) {
                ret = bwrap->get (&mapAsVariant, path, &bwContext);

                if (!bwContext.isError ()) {
                        return ret;
                }
        }

        if ((!domain || domain->isNone ()) && (!argsMap || argsMap->empty ())) {
                // Jeśli conditional, to nie wyjątek, a false
                if (conditional) {
                        //return Core::Variant (false);
                        return Core::Variant ();
                }
                else {
                        RuntimeException e ("RuntimeException : [" + path + "] property requested, but both domain and argsMap are NULL.");
                        e.addMessage (bwContext.getMessage ());
                        throw e;
                }
        }

        // Jeśli conditional, to nie wyjątek, a false
        if (conditional) {
                // return Core::Variant (false);
                return Core::Variant ();
        }
        else {
                RuntimeException e ("RuntimeException : [" + path + "] property getter requested, but none found.");
                e.addMessage (bwContext.getMessage ());
                throw e;
        }
}

/****************************************************************************/

void Context::setArg (const std::string &path, const Core::Variant &obj)
{
        using Common::Context;
        Context bwContext;

        if (domain && !domain->isNone ()) {
                bwrap->set (domain, path, obj, &bwContext);

                if (!bwContext.isError ()) {
                        return;
                }
        }

        if (argsMap) {
                bwrap->set (&mapAsVariant, path, obj, &bwContext);

                if (!bwContext.isError ()) {
                        return;
                }
        }

        if ((!domain || domain->isNone ()) && (!argsMap || argsMap->empty ())) {
                throw RuntimeException ("RuntimeException : [" + path + "] property requested, but both domain and argsMap are NULL.");
        }

        throw RuntimeException ("RuntimeException : [" + path + "] property setter requested, but none found.");
}

/****************************************************************************/

Core::Variant Context::callFunction (const std::string &path, Core::VariantVector &args)
{
        Core::Variant vh = getArg (path);
        Ptr <Wrapper::Handler> handler = vcast <Ptr <Wrapper::Handler> > (vh);
        return handler->invoke (&args);
}

}
