/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MetaFactory.h"

namespace Container {

MetaObject *MetaFactory::newMetaObject ()
{
        return new (memoryAllocator->malloc (sizeof (MetaObject))) MetaObject ();
}

DataKey *MetaFactory::newDataKey ()
{
        return new (memoryAllocator->malloc (sizeof (DataKey))) DataKey ();
}

DataKey *MetaFactory::newDataKey (IData *d)
{
        return new (memoryAllocator->malloc (sizeof (DataKey))) DataKey (d);
}

DataKey *MetaFactory::newDataKey (const char *k, IData *d)
{
        return new (memoryAllocator->malloc (sizeof (DataKey))) DataKey (k, d);
}

ValueData *MetaFactory::newValueData ()
{
        return new (memoryAllocator->malloc (sizeof (ValueData))) ValueData ();
}

ValueData *MetaFactory::newValueData (const char *d)
{
        return new (memoryAllocator->malloc (sizeof (ValueData))) ValueData (d);
}

ValueData *MetaFactory::newValueData (const char *d, const char *t)
{
        return new (memoryAllocator->malloc (sizeof (ValueData))) ValueData (d, t);
}

RefData *MetaFactory::newRefData ()
{
        return new (memoryAllocator->malloc (sizeof (RefData))) RefData ();
}

RefData *MetaFactory::newRefData (const char *d)
{
        return new (memoryAllocator->malloc (sizeof (RefData))) RefData (d);
}

NullData *MetaFactory::newNullData ()
{
        return new (memoryAllocator->malloc (sizeof (NullData))) NullData ();
}

const char *MetaFactory::newString (std::string const &orig)
{
        char *ret = memoryAllocator->malloc (orig.size () + 1);
        strcpy (ret, orig.c_str ());
        return ret;
}

const char *MetaFactory::newString (const char *orig)
{
        char *ret = memoryAllocator->malloc (strlen (orig) + 1);
        strcpy (ret, orig);
        return ret;
}

} /* namespace Container */
