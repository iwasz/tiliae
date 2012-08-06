/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <Tools.h>

#include "PrintService.h"
#include "metaStructure/model/MetaStructure.h"

namespace Container {

using namespace Core;

void PrintMetaService::onContainer (MetaContainer *data)
{
        if (!buffer) {
                std::cerr << "MetaContainer" <<std::endl;
        }
        else {
                *buffer += "MetaContainer\n";
        }
}

bool PrintMetaService::onMappedMetaBegin (MetaObject *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "MappedMeta ("
                                << "id=[" << data->getId ()
                                << "], class=[" << data->getClass ()
                                << "], parent=[" << data->getParent ()
                                << "])" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "MappedMeta (" + std::string (data->getId ()) + ")\n";
        }

        return true;
}

bool PrintMetaService::onIndexedMetaBegin (MetaObject *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "IndexedMeta ("
                                << "id=[" << data->getId ()
                                << "], class=[" << data->getClass ()
                                << "], parent=[" << data->getParent ()
                                << "])" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "IndexedMeta (" + std::string (data->getId ()) + ")\n";
        }

        return true;
}

void PrintMetaService::onValueData (std::string const &key, ValueData *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "ValueData (" << data->getData() << ")" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "ValueData (" + std::string (data->getData()) + ")\n";
        }
}

void PrintMetaService::onNullData (std::string const &key, NullData *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "NullData" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "NullData\n";
        }
}

void PrintMetaService::onRefData (std::string const &key, RefData *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "RefData (" << data->getData() << ")" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "RefData (" + std::string (data->getData()) + ")\n";
        }
}

}
