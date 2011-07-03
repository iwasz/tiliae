/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MetaVisitor.h"
#include "VisitorContext.h"
#include "../../../core/Typedefs.h"

namespace Container {

void MetaVisitor::visit (MetaContainer *container)
{
        assert (ctx);
        ctx->resetDepth ();
        ctx->setMetaContainer (container);

        foreach (Ptr <IMetaService> service, services) {
                /*if (!*/service->onContainer (container)/*) {
                        return;
                }*/
                                ;
        }

        foreach (MetaMap::value_type p, container->getMetaMap ()) {
                Ptr <IMeta> meta = p.second;
                meta->accept (this);
        }
}

/****************************************************************************/

void MetaVisitor::visit (MappedMeta *data)
{
        foreach (Ptr <IMetaService> service, services) {
                /*if (!*/service->onMetaBegin (data);/*) { return; }*/
                /*if (!*/service->onMappedMetaBegin (data);/*) { return; }*/
        }

        foreach (Ptr <MapElem> elem, data->getFieldsAsList ()) {
                elem->accept (this);
        }

        foreach (Ptr <IMetaService> service, services) {
                service->onConstructorArgsBegin (data);
        }

        foreach (Ptr <ListElem> elem, data->getConstructorArgs()) {
                elem->accept (this);
        }

        foreach (Ptr <IMetaService> service, services) {
                service->onConstructorArgsEnd (data);
        }

        visitInnerMeta (data);

        foreach (Ptr <IMetaService> service, services) {
                /*if (!*/service->onMetaEnd (data);/*) { return; }*/
                /*if (!*/service->onMappedMetaEnd (data);/*) { return; }*/
        }
}

void MetaVisitor::visit (IndexedMeta *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onMetaBegin (data);
                service->onIndexedMetaBegin (data);
        }

        foreach (Ptr <ListElem> elem, data->getFields ()) {
                elem->accept (this);
        }

        foreach (Ptr <IMetaService> service, services) {
                service->onConstructorArgsBegin (data);
        }

        foreach (Ptr <ListElem> elem, data->getConstructorArgs()) {
                elem->accept (this);
        }

        foreach (Ptr <IMetaService> service, services) {
                service->onConstructorArgsEnd (data);
        }

        visitInnerMeta (data);

        foreach (Ptr <IMetaService> service, services) {
                service->onMetaEnd (data);
                service->onIndexedMetaEnd (data);
        }
}

void MetaVisitor::visitInnerMeta (AbstractMeta *data)
{
        ctx->incDepth ();

        foreach (MetaMap::value_type p, data->getInnerMetas ()) {
                Ptr <IMeta> meta = p.second;
                meta->accept (this);
        }

        ctx->decDepth ();
}

/****************************************************************************/

void MetaVisitor::visit (ListElem *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onListElem (data);
        }

        data->getData()->accept (this);
}

void MetaVisitor::visit (MapElem *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onMapElem (data);
        }

        data->getData()->accept (this);
}

/****************************************************************************/

void MetaVisitor::visit (ValueData *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onValueData (data);
        }
}

void MetaVisitor::visit (NullData *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onNullData (data);
        }
}

void MetaVisitor::visit (RefData *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onRefData (data);
        }
}

void MetaVisitor::visit (IdRefData *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onIdRefData (data);
        }
}

/****************************************************************************/

void MetaVisitor::reset ()
{
        services.clear ();
        if (ctx) {
                ctx->reset ();
        }
}

}
