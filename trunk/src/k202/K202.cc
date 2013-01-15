/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <beanWrapper/beanWrapper/BeanWrapper.h>
#include <beanWrapper/plugins/IBeanWrapperPlugin.h>
#include <beanWrapper/plugins/PropertyRWBeanWrapperPlugin.h>
#include <beanWrapper/plugins/GetPutMethodRWBeanWrapperPlugin.h>
#include <beanWrapper/plugins/ListPlugin.h>
#include <beanWrapper/plugins/MapPlugin.h>
#include <beanWrapper/plugins/MethodPlugin.h>

#include "K202.h"
#include "Script.h"
#include "compiler/Compiler.h"

namespace k202 {

using namespace Wrapper;

Ptr <K202> K202::create (Ptr <Wrapper::IBeanWrapper> b, Ptr <IExtension> ext)
{
        // Nie można użyć make_shared
        Ptr <K202> k = Ptr <K202> (new K202);
        k->ctx.setBeanWrapper (BeanWrapper::create ());
        k->compiler = Compiler::create ();
        k->compiler->setExtension (ext);
        return k;
}

/****************************************************************************/

template <typename T>
T K202::createHelper (Ptr <IExtension> ext)
{
        T k (new K202);
        k->ctx.setBeanWrapper (BeanWrapper::create ());
        k->compiler = Compiler::create ();
        k->compiler->setExtension (ext);
        return k;
}

K202 *K202::instance ()
{
        static K202 *neverDelete = createHelper <K202 *> (Ptr <IExtension> ());
        return neverDelete;
}

/****************************************************************************/

Core::Variant K202::run (const std::string &sourceCode,
        const Core::Variant &domain,
        const Core::VariantVector &paramVector,
        const Core::VariantMap &argsMap)
{
        return run (prepare (sourceCode, domain, paramVector, argsMap));
}

/****************************************************************************/

Core::Variant K202::run (Ptr <Script> script,
                         Core::Variant *domain,
                         const Core::VariantVector &paramVector,
                         const Core::VariantMap &argsMap)
{
        /*
         * Tu w script następuje merge paramVector i argsMap z tym co już jest
         * w script.
         */
        return script->run (&ctx, domain, paramVector, argsMap);
}

/****************************************************************************/

Ptr <Script> K202::prepare (const std::string &sourceCode,
                            const Core::Variant &domain,
                            const Core::VariantVector &paramVector,
                            const Core::VariantMap &argsMap)
{
        Ptr <Script> script (new Script (sourceCode, compiler->compile (sourceCode, &ctx), domain));
        script->setParamVector (paramVector);
        script->setArgsMap (argsMap);
        return script;
}

}
