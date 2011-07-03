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

bool PrintMetaService::onMappedMetaBegin (MappedMeta *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "MappedMeta ("
                                << "id=[" << data->getId ()
                                << "], class=[" << data->getClass ()
                                << "], parent=[" << data->getParent ()
                                << "])" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "MappedMeta (" + data->getId () + ")\n";
        }

        return true;
}

bool PrintMetaService::onIndexedMetaBegin (IndexedMeta *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "IndexedMeta ("
                                << "id=[" << data->getId ()
                                << "], class=[" << data->getClass ()
                                << "], parent=[" << data->getParent ()
                                << "])" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "IndexedMeta (" + data->getId () + ")\n";
        }

        return true;
}

void PrintMetaService::onListElem (ListElem *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "ListElem" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "ListElem\n";
        }
}

void PrintMetaService::onMapElem (MapElem *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "MapElem" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "MapElem\n";
        }
}

void PrintMetaService::onValueData (ValueData *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "ValueData (" << data->getData() << ")" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "ValueData (" + data->getData() + ")\n";
        }
}

void PrintMetaService::onNullData (NullData *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "NullData" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "NullData\n";
        }
}

void PrintMetaService::onRefData (RefData *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "RefData (" << data->getData() << ")" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "RefData (" + data->getData() + ")\n";
        }
}

void PrintMetaService::onIdRefData (IdRefData *data)
{
        if (!buffer) {
                std::cerr << getContext ()->getDepth() << "IdRefData (" << data->getData() << ")" <<std::endl;
        }
        else {
                *buffer += getContext ()->getDepth() + "IdRefData (" + data->getData() + ")\n";
        }
}

}
