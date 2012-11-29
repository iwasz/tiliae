/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#include "DataSource.h"
#include <android/asset_manager.h>
#include <android/log.h>

namespace Common {

struct DataSource::Impl {
        Impl () : asset (NULL), assetManager (NULL) {}
        AAsset *asset;
        AAssetManager *assetManager;
};

/****************************************************************************/

DataSource::DataSource (void *userData) : impl (new Impl)
{
        if (!userData) {
                throw DataSourceException (std::string ("DataSource::DataSource : android datasource implementation requires AAssetManager * as argument."));
        }

        impl->assetManager = static_cast <AAssetManager *> (userData);
}

/****************************************************************************/

DataSource::~DataSource ()
{
        delete impl;
}

/****************************************************************************/

void DataSource::open (const char* filename, OpenMode mode)
{
        if (!filename) {
                throw DataSourceException (std::string ("DataSource::open() : open failed, path is NULL."));
        }

        impl->asset = AAssetManager_open (impl->assetManager, filename, (int)mode);

        if (!impl->asset) {
                throw DataSourceException (std::string ("DataSource::open() : open failed. Path : ") + filename);
        }
}

/****************************************************************************/

void DataSource::close()
{
        AAsset_close (impl->asset);
        impl->asset = NULL;
}

/****************************************************************************/

int DataSource::read (void* buf, size_t count)
{
        int ret = AAsset_read (impl->asset, buf, count);

        if (ret < 0) {
                return 0;
        }

        return ret;
}

/****************************************************************************/

size_t DataSource::seek (off_t offset, int whence)
{
        off_t ret = AAsset_seek (impl->asset, offset, whence);

        if (ret < 0) {
                throw DataSourceException ("DataSource::seek () : error during seeking.");
        }

        return ret;
}

/****************************************************************************/

size_t DataSource::tell ()
{
        off_t ret = AAsset_seek (impl->asset, 0, SEEK_CUR);

        if (ret < 0) {
                throw DataSourceException ("DataSource::tell () : error during seeking.");
        }

        return ret;
}

/****************************************************************************/

void DataSource::rewind ()
{
        if (AAsset_seek (impl->asset, 0, SEEK_SET) < 0) {
                throw DataSourceException ("DataSource::rewind () : error during seeking.");
        }
}

/****************************************************************************/

size_t DataSource::getLength ()
{
        return AAsset_getLength (impl->asset);
}

} /* namespace Common */

#endif

