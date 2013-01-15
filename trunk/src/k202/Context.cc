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
#include "core/variant/Cast.h"
#include "beanWrapper/IBeanWrapper.h"
#include "beanWrapper/plugins/MethodPlugin.h"

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
        Core::DebugContext bwContext;
        bool err;
        Core::Variant ret;

        if (domain && !domain->isNone ()) {
                ret = bwrap->get (domain, path, &err, &bwContext);

                if (!err) {
                        return ret;
                }
        }

        if (ret.isNone () && argsMap && !argsMap->empty ()) {
                ret = bwrap->get (&mapAsVariant, path, &err, &bwContext);

                if (!err) {
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
                e.addContext (bwContext);
                throw e;
        }
}

/****************************************************************************/

void Context::setArg (const std::string &path, const Core::Variant &obj)
{
        Core::DebugContext bwContext;

        if (domain && !domain->isNone ()) {
                if (bwrap->set (domain, path, obj, &bwContext)) {
                        return;
                }
        }

        if (argsMap) {
                if (bwrap->set (&mapAsVariant, path, obj, &bwContext)) {
                        return;
                }
        }

        if ((!domain || domain->isNone ()) && (!argsMap || argsMap->empty ())) {
                RuntimeException e ("RuntimeException : [" + path + "] property requested, but both domain and argsMap are NULL.");
                e.addContext (bwContext);
                throw e;
        }

        RuntimeException e ("RuntimeException : [" + path + "] property setter requested, but none found.");
        e.addContext (bwContext);
        throw e;
}

/****************************************************************************/

Core::Variant Context::callFunction (const std::string &path, Core::VariantVector &args)
{
        Core::Variant vh = getArg (path);
        Ptr <Wrapper::Handler> handler = vcast <Ptr <Wrapper::Handler> > (vh);
        return handler->invoke (&args);
}

}
