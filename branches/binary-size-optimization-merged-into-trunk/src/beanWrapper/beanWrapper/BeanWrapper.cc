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
#include "../../core/DebugContext.h"

/****************************************************************************/

namespace Wrapper {
using Core::Variant;
using Core::VariantList;
using Core::StringList;
using Core::DebugContext;
using namespace Common;

BeanWrapper *BeanWrapper::create (const Core::Variant &bean)
{
        BeanWrapper *beanWrapper = new BeanWrapper (bean, true);
        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::METHOD));
        return beanWrapper;
}

/****************************************************************************/

BeanWrapper::~BeanWrapper ()
{
        if (deleteContents) {
                for (BeanWrapperPluginVector::iterator i = pluginList.begin (); i != pluginList.end (); ++i) {
                        delete *i;
                }

                delete editor;
        }
}

/*##########################################################################*/

bool BeanWrapper::set (Core::Variant *bean, const std::string &path, const Core::Variant &object, DebugContext *ctx)
{
        ListPath pth (path);

        if (!set (bean, &pth, object, ctx)) {
                dcError (ctx, std::string ("In BeanWrapper::set. Path : [") + path + "], value : [" + object.toString () + "].");
                return false;
        }

        return true;
}

/****************************************************************************/

bool BeanWrapper::add (Core::Variant *bean, const std::string &path, const Core::Variant &object, DebugContext *ctx)
{
        ListPath pth (path);

        if (!add (bean, &pth, object, ctx)) {
                dcError (ctx, std::string ("In BeanWrapper::add. Path : [") + path + "], value : [" + object.toString () + "].");
                return false;
        }

        return true;
}

/****************************************************************************/

Core::Variant BeanWrapper::get (const Core::Variant *bean, const std::string &path, bool *error, DebugContext *ctx) const
{
        ListPath pth (path);
        bool err;
        Variant ret = get (*bean, &pth, &err, ctx);

        if (err) {
                dcError (ctx, std::string ("In BeanWrapper::get. Path : [") + path + "].");
                setError (error);
                return Core::Variant ();
        }

        clearError (error);
        return ret;
}

/****************************************************************************/

Ptr <Core::IIterator> BeanWrapper::iterator (const Core::Variant *bean, const std::string &path, bool *error, Core::DebugContext *ctx) const
{
        ListPath pth (path);
        bool err;
        Ptr <Core::IIterator> ret = ocast <Ptr <Core::IIterator> > (iterator (*bean, &pth, &err, ctx));

        if (err) {
                dcError (ctx, std::string ("In BeanWrapper::iterator. Path : [") + path + "].");
                setError (error);
                return Ptr <Core::IIterator> ();
        }

        clearError (error);
        return ret;
}

/*##########################################################################*/

bool BeanWrapper::set (const std::string &path, const Core::Variant &object, DebugContext *ctx)
{
        return set (&wrappedObject, path, object, ctx);
}

/****************************************************************************/

Core::Variant BeanWrapper::get (const std::string &k, bool *error, DebugContext *ctx) const
{
        return get (&wrappedObject, k, error, ctx);
}

/****************************************************************************/

Ptr <Core::IIterator> BeanWrapper::iterator (const std::string &path, bool *error, Core::DebugContext *ctx) const
{
        return iterator (&wrappedObject, path, error, ctx);
}

/****************************************************************************/

bool BeanWrapper::add (const std::string &path, const Core::Variant &object, DebugContext *ctx)
{
        return add (&wrappedObject, path, object, ctx);
}

/*##########################################################################*/

Core::Variant BeanWrapper::get (const Core::Variant &referenceObject, IPath *path, bool *error, DebugContext *ctx) const
{
        assert (path);

        if (referenceObject.isNone () || referenceObject.isNull ()) {
                dcError (ctx, "BeanWrapper::get : referenceObject->isNone () || referenceObject->isNull ().");
                setError (error);
                return Core::Variant ();
        }

        if (path->countSegments () == 1 && path->getFirstSegment() == "this") {
                clearError (error);
                return referenceObject;
        }

        bool err;
        Core::Variant ret = getObjectUsingPlugins (referenceObject, path, &err, ctx);

        if (err) {
                setError (error);
                dcError (ctx, "BeanWrapper::get : error in getObjectUsingPlugins.")
                return Core::Variant ();
        }

        if (path->countSegments ()) {
                if (!ret.isNone ()) {
                        return get (ret, path, error, ctx);
                }
                else {
                        dcError (ctx, "BeanWrapper::get path->countSegments "
                                        "() != 0 and previous segment returned NONE. referenceObject : [" + referenceObject.toString () +
                                        "], path : [" + path->toString () + "].");
                        setError (error);
                        return Variant ();
                }
        }

        clearError (error);
        return ret;
}

/****************************************************************************/

Core::Variant BeanWrapper::iterator (const Core::Variant &referenceObject, Common::IPath *path, bool *error, Core::DebugContext *ctx) const
{
        assert (path);

        if (referenceObject.isNone () || referenceObject.isNull ()) {
                dcError (ctx, "BeanWrapper::iterator : referenceObject->isNone () || referenceObject->isNull ().");
                setError(error);
                return Core::Variant ();
        }

        bool err;
        if (!path->countSegments () || (path->countSegments() == 1 && path->getFirstSegment () == "this")) {
                path->clear ();
                Core::Variant ret = getObjectUsingPlugins (referenceObject, path, &err, ctx, true);

                if (err) {
                        dcError (ctx, "Cannot get iterator '" + path->toString () + "'.");
                        setError (error);
                        return Core::Variant ();
                }

                clearError (error);
                return ret;
        }
        else  {
                Core::Variant ret = get (referenceObject, path, &err, ctx);

                if (err) {
                        dcError (ctx, "Cannot get iterator '" + path->toString () + "'.");
                        setError (error);
                        return Core::Variant ();
                }

                return iterator (ret, path, error, ctx);
        }
}

/****************************************************************************/

bool BeanWrapper::set (Core::Variant *referenceObject, IPath *path, const Core::Variant &v, DebugContext *ctx)
{
        assert (path);
        assert (referenceObject);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << referenceObject->getTypeInfo ()->name () << ", " << path->toString () << std::endl;
#endif

        if (path->countSegments () == 1 && path->getFirstSegment() == "this") {
                *referenceObject = v;
                return true;
        }

        if (referenceObject->isNone () || referenceObject->isNull ()) {
                dcError (ctx, "BeanWrapper::set : referenceObject->isNone () || referenceObject->isNull ()");
                return false;
        }

        if (path->countSegments () == 1 || path->countSegments () == 0) {
                return setObjectUsingPlugins (referenceObject, path, v, ctx);
        }

        if (path->countSegments () > 1) {
                ListPath left = path->getAllButLastSegment ();
                ListPath right = path->getLastSegment ();
                Core::Variant ret;
                bool err;

                ret = get (*referenceObject, &left, &err, ctx);

                if (err) {
                        dcError (ctx, "Cannot set property (can't get left). '" + path->getAllButLastSegment () + "^" + path->getLastSegment () + "'.");
                        return false;
                }

                return set (&ret, &right, v, ctx);
        }

        return false;
}

/****************************************************************************/

bool BeanWrapper::add (Core::Variant *referenceObject, IPath *path, const Core::Variant &v, DebugContext *ctx)
{
        assert (path);
        assert (referenceObject);

#       if 0
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << referenceObject->getTypeInfo ()->name () << ", " << path->toString () << std::endl;
#endif

        if (referenceObject->isNone () || referenceObject->isNull ()) {
                dcError (ctx, "BeanWrapper::add : referenceObject->isNone () || referenceObject->isNull ()");
                return false;
        }

        if (path->countSegments () == 0 || (path->countSegments () == 1 && path->getFirstSegment () == "this")) {
                path->clear ();
                return setObjectUsingPlugins (referenceObject, path, v, ctx, true);
        }

        ListPath left;
        ListPath right;

        if (path->countSegments () > 1) {
                left = path->getAllButLastSegment ();
                right = path->getLastSegment ();
        }
        else {
                left = path->toString ();
                right.clear ();
        }

        Core::Variant ret;
        bool err;

        ret = get (*referenceObject, &left, &err, ctx);

        if (err) {
                dcError (ctx, "Cannot add property '" + path->toString () + "'.");
                return false;
        }

        return add (&ret, &right, v, ctx);;
}

/*##########################################################################*/

Core::Variant BeanWrapper::getObjectUsingPlugins (const Core::Variant &input, IPath *path, bool *error, DebugContext *ctx, bool iter) const
{
        assert (path);
        dcBegin (ctx);

        if (pluginList.empty ()) {
                dcError (ctx, "BeanWrapper::getObjectUsingPlugins : pluginList is NULL");
                setError (error);
                return Core::Variant ();
        }

        // Sprobuj uzyc ktoregos pluginu aby wyciagnac obiekt
        for (BeanWrapperPluginVector::const_iterator i = pluginList.begin (); i != pluginList.end (); ++i) {

                Variant bean;
                bool err;

                if (iter) {
                        bean = (*i)->iterator (input, path, &err, ctx);
                }
                else {
                        bean = (*i)->get (input, path, &err, ctx, editor);
                }

                if ((!iter && !err) ||                  // Kiedy zwykły get
                    (iter && !bean.isNone ())) {        // Kiedy pobieranie iteratora
                        clearError (error);
                        dcRollback (ctx);
                        return bean;
                }
        }

        dcError (ctx, "Can't get property for path [" + path->toString () + "]. Input : " + input.toString () + ".");
        dcCommit (ctx);
        setError(error);

        return Core::Variant ();
}

/****************************************************************************/

bool BeanWrapper::setObjectUsingPlugins (Core::Variant *bean, IPath *path, const Core::Variant &object, DebugContext *ctx, bool add)
{
        assert (bean);
        assert (path);
        std::string pathStr = path->toString ();

        if (pluginList.empty ()) {
                dcError (ctx, "BeanWrapper::setObjectUsingPlugins : pluginList is NULL");
                return false;
        }

        dcBegin (ctx);

        // Sprobuj uzyc ktoregos pluginu aby wyciagnac obiekt
        for (BeanWrapperPluginVector::const_iterator i = pluginList.begin (); i != pluginList.end (); ++i) {

                if (add) {
                        if ((*i)->add (bean, path, object, ctx, editor)) {
                                dcRollback (ctx);
                                return true;
                        }
                }
                else {
                        if ((*i)->set (bean, path, object, ctx, editor)) {
                                dcRollback (ctx);
                                return true;
                        }
                }
        }

        dcError (ctx, "PropertyNotSettableException for path '" + pathStr + "'.");
        dcCommit (ctx);
        return false;
}

/****************************************************************************/

std::string BeanWrapper::toString () const
{
        return "(not implemented!)";
}

} // namespace

