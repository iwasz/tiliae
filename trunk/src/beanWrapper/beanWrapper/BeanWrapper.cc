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
        Context tmpCtx;
        ListPath pth (path);
        set (bean, &pth, object, &tmpCtx);

        if (tmpCtx.isError ()) {
                error (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, std::string ("In BeanWrapper::set. Path : [") + path + "], value : [" + object.toString () + "]\n" + tmpCtx.getMessage ());
        }
}

/****************************************************************************/

void BeanWrapper::add (Core::Variant *bean, const std::string &path, const Core::Variant &object, Context *ctx)
{
        Context tmpCtx;
        ListPath pth (path);
        add (bean, &pth, object, &tmpCtx);

        if (tmpCtx.isError ()) {
                error (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, std::string ("In BeanWrapper::add. Path : [") + path + "], value : [" + object.toString () + "]\n" + tmpCtx.getMessage ());
        }
}

/****************************************************************************/

Core::Variant BeanWrapper::get (const Core::Variant *bean, const std::string &path, Context *ctx) const
{
        Context tmpCtx;
        ListPath pth (path);
        Variant ret = get (*bean, &pth, &tmpCtx);

        if (tmpCtx.isError ()) {
                error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, std::string ("In BeanWrapper::get. Path : [") + path + "]\n" + tmpCtx.getMessage ());
        }

        return ret;
}

/****************************************************************************/

Ptr <Core::IIterator> BeanWrapper::iterator (const Core::Variant *bean, const std::string &path, Common::Context *ctx) const
{
        Context tmpCtx;
        ListPath pth (path);
        Ptr <Core::IIterator> ret = ocast <Ptr <Core::IIterator> > (iterator (*bean, &pth, &tmpCtx));

        if (tmpCtx.isError ()) {
                error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, std::string ("In BeanWrapper::iterator. Path : [") + path + "]\n" + tmpCtx.getMessage ());
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

Ptr <Core::IIterator> BeanWrapper::iterator (const std::string &path, Common::Context *ctx) const
{
        return iterator (&wrappedObject, path, ctx);
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

        if (referenceObject.isNone () || referenceObject.isNull ()) {
                error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "BeanWrapper::get : referenceObject->isNone () || referenceObject->isNull ()");
                return Core::Variant ();
        }

        if (!path->countSegments ()) {
                return referenceObject;
        }

        Core::Variant ret = getObjectUsingPlugins (referenceObject, path, ctx);

        if (path->countSegments ()) {
                if (!ret.isNone ()) {
                        return get (ret, path, ctx);
                }
                else {
                        error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "BeanWrapper::get path->countSegments "
                                        "() != 0 and previous segment returned NONE. referenceObject : [" + referenceObject.toString () +
                                        "], path : [" + path->toString () + "].");
                        return Variant ();
                }
        }

        return ret;
}

/****************************************************************************/

Core::Variant BeanWrapper::iterator (const Core::Variant &referenceObject, Common::IPath *path, Common::Context *ctx) const
{
        assert (path);

        if (referenceObject.isNone () || referenceObject.isNull ()) {
                error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "BeanWrapper::iterator : referenceObject->isNone () || referenceObject->isNull ()");
                return Core::Variant ();
        }

        if (!path->countSegments ()) {
                Core::Variant ret = getObjectUsingPlugins (referenceObject, path, ctx, true);

                if (ctx->isError ()) {
                        error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "Cannot get iterator '" + path->toString () + "'.");
                }

                return ret;
        }
        else  {
                Core::Variant ret = get (referenceObject, path, ctx);

                if (ctx->isError ()) {
                        error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "Cannot get iterator '" + path->toString () + "'.");
                }

                return iterator (ret, path, ctx);
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
                error (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "BeanWrapper::set : referenceObject->isNone () || referenceObject->isNull ()");
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

                if (ctx->isError ()) {
                        error (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "Cannot set property '" + path->toString () + "'.");
                }

                set (&ret, &right, v, ctx);
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
                error (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "BeanWrapper::add : referenceObject->isNone () || referenceObject->isNull ()");
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

                if (ctx->isError ()) {
                        error (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "Cannot add property '" + path->toString () + "'.");
                }

                add (&ret, &right, v, ctx);
                return;
        }
}

/*##########################################################################*/

Core::Variant BeanWrapper::getObjectUsingPlugins (const Core::Variant &input, IPath *path, Context *ctx, bool iter) const
{
        assert (path);
        unsigned int errCnt = 0;

        // Sprobuj uzyc ktoregos pluginu aby wyciagnac obiekt
        for (BeanWrapperPluginList::const_iterator i = getPluginList ()->begin (); i != getPluginList ()->end (); i++) {

                Common::Context tmpCtx;
                int actualSegments = path->countSegments ();
                Variant bean;

                if (iter) {
                        bean = (*i)->iterator (input, path, &tmpCtx);
                }
                else {
                        bean = (*i)->get (input, path, &tmpCtx, editor.get ());
                }

                if ((!iter && !tmpCtx.isError () && path->countSegments () < actualSegments) || // Kiedy zwykły get
                    (iter && !bean.isNone ())                                                   // Kiedy pobieranie iteratora
                                ) {
                        return bean;
                }
                else {
                        ++errCnt;
                }
        }

        if (errCnt >= getPluginList ()->size ()) {
                error (ctx, PropertyNotGettableException, Common::UNDEFINED_ERROR, "Can't get property for path '" + path->toString () + "'. Input : " + input.toString ());
        }

        return Core::Variant ();
}

/****************************************************************************/

void BeanWrapper::setObjectUsingPlugins (Core::Variant *bean, IPath *path, const Core::Variant &object, Context *ctx, bool add)
{
        assert (bean);
        assert (path);
        std::string pathStr = path->toString ();
        unsigned int errCnt = 0;

        // Sprobuj uzyc ktoregos pluginu aby wyciagnac obiekt
        for (BeanWrapperPluginList::const_iterator i = getPluginList ()->begin (); i != getPluginList ()->end (); ++i) {

                std::string p = path->toString ();
                Context tmpCtx;

                if (add) {
                        if ((*i)->add (bean, path, object, &tmpCtx, editor.get ())) {
                                return;
                        }
                }
                else {
                        if ((*i)->set (bean, path, object, &tmpCtx, editor.get ())) {
                                return;
                        }
                }

                if (tmpCtx.isError ()) {
                        ++errCnt;
                }
        }

        if (errCnt >= getPluginList ()->size ()) {
                error (ctx, PropertyNotSettableException, Common::UNDEFINED_ERROR, "PropertyNotSettableException for path '" + pathStr + ".");
        }
}

/****************************************************************************/

std::string BeanWrapper::toString () const
{
        return "(not implemented!)";
}

} // namespace

