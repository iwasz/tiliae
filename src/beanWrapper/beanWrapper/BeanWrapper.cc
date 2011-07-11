/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <boost/make_shared.hpp>
#include "path/ListPath.h"
#include "BeanWrapper.h"
#include "plugins/IBeanWrapperPlugin.h"
#include "plugins/PropertyRWBeanWrapperPlugin.h"
#include "plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include "plugins/MethodPlugin.h"
#include "../../core/Exception.h"
#include "../../common/Context.h"

/****************************************************************************/

namespace Wrapper {
using Core::Variant;
using Core::VariantList;
using Core::StringList;
using namespace Common;

Ptr<BeanWrapper> BeanWrapper::create (const Core::Variant &bean)
{
        Ptr <BeanWrapper> beanWrapper = boost::make_shared <BeanWrapper> (bean);
        Ptr <BeanWrapperPluginList> pluginList = boost::make_shared <BeanWrapperPluginList> ();

        Ptr <IBeanWrapperPlugin> plugin = boost::make_shared <PropertyRWBeanWrapperPlugin> ();
        pluginList->push_back (plugin);

        plugin = boost::make_shared <GetPutMethodRWBeanWrapperPlugin> ();
        pluginList->push_back (plugin);

        plugin = boost::make_shared <MethodPlugin> (MethodPlugin::METHOD);
        pluginList->push_back (plugin);

        beanWrapper->setPluginList (pluginList);
        return beanWrapper;
}

/*##########################################################################*/

void BeanWrapper::set (Core::Variant *bean, const std::string &path, const Core::Variant &object, Context *ctx)
{
        Context *tmpCtx = ctx;

        if (!ctx) {
                tmpCtx = new Context;
        }

        ListPath pth (path);
        set (bean, &pth, object, tmpCtx);

        if (!tmpCtx->isEmpty ()) {
                tmpCtx->addError (std::string ("In BeanWrapper::set. Path : [") + path + "], value : [" + object.toString () + "]");
        }

        if (!ctx && tmpCtx->isFatal ()) {
                std::string msg = tmpCtx->getMessage ();
                delete tmpCtx;
                throw PropertyNotSettableException (msg);
        }
}

/****************************************************************************/

void BeanWrapper::add (Core::Variant *bean, const std::string &path, const Core::Variant &object, Context *ctx)
{
        Context *tmpCtx = ctx;

        if (!ctx) {
                tmpCtx = new Context;
        }

        ListPath pth (path);
        add (bean, &pth, object, tmpCtx);

        if (!tmpCtx->isEmpty ()) {
                tmpCtx->addError (std::string ("In BeanWrapper::add. Path : [") + path + "], value : [" + object.toString () + "]");
        }

        if (!ctx && tmpCtx->isFatal ()) {
                std::string msg = tmpCtx->getMessage ();
                delete tmpCtx;
                throw PropertyNotSettableException (msg);
        }
}

/****************************************************************************/

Core::Variant BeanWrapper::get (const Core::Variant *bean, const std::string &path, Context *ctx) const
{
        Context *tmpCtx = ctx;

        if (!ctx) {
                tmpCtx = new Context;
        }

        ListPath pth (path);
        Variant ret = get (*bean, &pth, tmpCtx);

        if (!tmpCtx->isEmpty ()) {
                tmpCtx->addError (std::string ("In BeanWrapper::get. Path : [") + path + "]");
        }

        if (!ctx && tmpCtx->isFatal ()) {
                std::string msg = tmpCtx->getMessage ();
                delete tmpCtx;
                throw PropertyNotGettableException (msg);
        }

        return ret;
}


/*##########################################################################*/

void BeanWrapper::set (const std::string &path, const Core::Variant &object, Context *ctx)
{
        set (&wrappedObject, path, object, ctx);
}

/****************************************************************************/

Core::Variant BeanWrapper::get (const std::string &k, Context *ctx) const
{
        return get (&wrappedObject, k, ctx);
}

/****************************************************************************/

void BeanWrapper::add (const std::string &path, const Core::Variant &object, Context *ctx)
{
        add (&wrappedObject, path, object, ctx);
}

/*##########################################################################*/

Core::Variant BeanWrapper::get (const Core::Variant &referenceObject, IPath *path, Context *ctx) const
{
        assert (path);

        if (!path->countSegments ()) {
                return referenceObject;
        }

        if (referenceObject.isNone () || referenceObject.isNull ()) {
                fatal (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "BeanWrapper::set : referenceObject->isNone () || referenceObject->isNull ()");
                return Core::Variant ();
        }

        Core::Variant ret = getObjectUsingPlugins (referenceObject, path, ctx);

        if (path->countSegments () && !ret.isNone ()) {
                return get (ret, path, ctx);
        }
        else {
                return ret;
        }
}

/****************************************************************************/

void BeanWrapper::set (Core::Variant *referenceObject, IPath *path, const Core::Variant &v, Context *ctx)
{
        assert (path);
        assert (referenceObject);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << referenceObject->getTypeInfo ()->name () << ", " << path->toString () << std::endl;
#endif

        if (!path->countSegments ()) {
                *referenceObject = v;
        }

        if (referenceObject->isNone () || referenceObject->isNull ()) {
                fatal (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "BeanWrapper::set : referenceObject->isNone () || referenceObject->isNull ()");
                return;
        }

        if (path->countSegments () == 1) {
                setObjectUsingPlugins (referenceObject, path, v, ctx);
                return;
        }

        if (path->countSegments () > 1) {
                ListPath left = path->getAllButLastSegment ();
                ListPath right = path->getLastSegment ();
                Core::Variant ret;

                ret = get (*referenceObject, &left, ctx);

                if (!ctx->isEmpty ()) {
                        ctx->addError ("Cannot set property '" + path->toString () + "'.");
                }

                set (&ret, &right, v, ctx);
                return;
        }
}

/****************************************************************************/

void BeanWrapper::add (Core::Variant *referenceObject, IPath *path, const Core::Variant &v, Context *ctx)
{
        assert (path);
        assert (referenceObject);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << referenceObject->getTypeInfo ()->name () << ", " << path->toString () << std::endl;
#endif

        if (referenceObject->isNone () || referenceObject->isNull ()) {
                fatal (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "BeanWrapper::add : referenceObject->isNone () || referenceObject->isNull ()");
                return;
        }

        if (path->countSegments () == 0) {
                setObjectUsingPlugins (referenceObject, path, v, ctx, true);
                return;
        }

        if (path->countSegments () > 0) {
                ListPath left = path->getAllButLastSegment ();
                ListPath right = path->getLastSegment ();
                Core::Variant ret;

                ret = get (*referenceObject, &left, ctx);

                if (!ctx->isEmpty ()) {
                        ctx->addError ("Cannot add property '" + path->toString () + "'.");
                }

                add (&ret, &right, v, ctx);
                return;
        }
}

/*##########################################################################*/

Core::Variant BeanWrapper::getObjectUsingPlugins (const Core::Variant &input, IPath *path, Context *ctx) const
{
        assert (path);
        assert (getPluginList ());

        // Sprobuj uzyc ktoregos pluginu aby wyciagnac obiekt
        for (BeanWrapperPluginList::const_iterator i = getPluginList ()->begin (); i != getPluginList ()->end (); i++) {

                Variant bean = (*i)->get (input, path, ctx, editor.get ());

                if (!bean.isNone ()) {
                        return bean;
                }
        }

        fatal (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "PropertyNotGettableException for path '" + path->toString () + "'. Input : " + input.toString () + ". Context mesage : " + ctx->getMessage ());
        return Core::Variant ();
}

/****************************************************************************/

void BeanWrapper::setObjectUsingPlugins (Core::Variant *bean, IPath *path, const Core::Variant &object, Context *ctx, bool add)
{
        assert (getPluginList ());
        assert (bean);
        assert (path);
        std::string pathStr = path->toString ();

        Context tmpCtx;
        bool shouldThrow = false;
        if (!ctx) {
                ctx = &tmpCtx;
                shouldThrow = true;
        }

        // Sprobuj uzyc ktoregos pluginu aby wyciagnac obiekt
        for (BeanWrapperPluginList::const_iterator i = getPluginList ()->begin (); i != getPluginList ()->end (); ++i) {

                std::string p = path->toString ();

                if (add) {
                        if ((*i)->add (bean, path, object, ctx, editor.get ())) {
                                return;
                        }
                }
                else {
                        if ((*i)->set (bean, path, object, ctx, editor.get ())) {
                                return;
                        }
                }
        }

        fatal (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "PropertyNotSettableException for path '" + pathStr + ".");
}

/****************************************************************************/

std::string BeanWrapper::toString () const
{
        return "(not implemented!)";
}

} // namespace

