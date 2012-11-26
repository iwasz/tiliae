/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#include "DataSource.h"
#include <cstdio>

namespace Common {

struct DataSource::Impl {
        Impl () : fp (NULL) {}
        FILE *fp;
};

/****************************************************************************/

DataSource::DataSource (void *userData) : impl (new Impl) {}

/****************************************************************************/

DataSource::~DataSource ()
{
        close ();
        delete impl;
}

/****************************************************************************/

void DataSource::open (const char *filename, OpenMode)
{
        impl->fp = fopen (filename, "rb");

        if (!impl->fp) {
                throw DataSourceException (std::string ("DataSource::open() : open failed. Path : ") + filename);
        }
}

/****************************************************************************/

void DataSource::close ()
{
        if (impl->fp) {
                if (fclose (impl->fp) != 0) {
                        throw DataSourceException ("DataSource::close() : error closing datasource.");
                }

                impl->fp = NULL;
        }
}

/****************************************************************************/

int DataSource::read (void* buf, size_t count)
{
        return fread (buf, 1, count, impl->fp);
}

/****************************************************************************/

size_t DataSource::seek (off_t offset, int whence)
{
        if (fseek (impl->fp, offset, whence) != 0) {
                throw DataSourceException ("DataSource::seek () : error during seeking.");
        }

        return ftell (impl->fp);
}

/****************************************************************************/

size_t DataSource::tell ()
{
        return ftell (impl->fp);
}

/****************************************************************************/

void DataSource::rewind ()
{
        ::rewind (impl->fp);
}

/****************************************************************************/

size_t DataSource::getLength ()
{
        size_t current = ftell (impl->fp);
        fseek (impl->fp, 0, SEEK_END);
        size_t size = ftell (impl->fp);
        fseek (impl->fp, current, SEEK_SET);
        return size;
}

} /* namespace Common */

#endif
