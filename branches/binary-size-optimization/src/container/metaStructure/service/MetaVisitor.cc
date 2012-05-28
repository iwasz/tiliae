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
#include "../../metaStructure/model/data/IData.h"

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
                IMeta *meta = p.second;
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

        DataMap fields = data->getFields ();
        for (DataKeyIterator1 iter = fields.get <1> ().begin (); iter != fields.get <1> ().end (); ++iter) {
                iter->data->accept (iter->key, this);
        }

        foreach (Ptr <IMetaService> service, services) {
                service->onConstructorArgsBegin (data);
        }

        DataVector cArgs = data->getConstructorArgs();
        for (DataVector::iterator i = cArgs.begin (); i != cArgs.end (); ++i) {
                (*i)->accept (std::string (), this);
        }

        foreach (Ptr <IMetaService> service, services) {
                service->onConstructorArgsEnd (data);
        }

        visitInnerMeta (data);

        foreach (Ptr <IMetaService> service, services) {
                service->onMetaEnd (data);
                service->onMappedMetaEnd (data);
        }
}

void MetaVisitor::visit (IndexedMeta *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onMetaBegin (data);
                service->onIndexedMetaBegin (data);
        }

        DataVector fields = data->getFields ();
        for (DataVector::iterator i = fields.begin (); i != fields.end (); ++i) {
                (*i)->accept (std::string (), this);
        }

        foreach (Ptr <IMetaService> service, services) {
                service->onConstructorArgsBegin (data);
        }

        DataVector cArgs = data->getConstructorArgs();
        for (DataVector::iterator i = cArgs.begin (); i != cArgs.end (); ++i) {
                (*i)->accept (std::string (), this);
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
                IMeta *meta = p.second;
                meta->accept (this);
        }

        ctx->decDepth ();
}

/****************************************************************************/

//void MetaVisitor::visit (ListElem *data)
//{
//        foreach (Ptr <IMetaService> service, services) {
//                service->onListElem (data);
//        }
//
//        data->getData()->accept (this);
//}
//
//void MetaVisitor::visit (MapElem *data)
//{
//        foreach (Ptr <IMetaService> service, services) {
//                service->onMapElem (data);
//        }
//
//        data->getData()->accept (this);
//}

/****************************************************************************/

void MetaVisitor::visit (std::string const &key, ValueData *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onValueData (key, data);
        }
}

void MetaVisitor::visit (std::string const &key, NullData *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onNullData (key, data);
        }
}

void MetaVisitor::visit (std::string const &key, RefData *data)
{
        foreach (Ptr <IMetaService> service, services) {
                service->onRefData (key, data);
        }
}

//void MetaVisitor::visit (IdRefData *data)
//{
//        foreach (Ptr <IMetaService> service, services) {
//                service->onIdRefData (data);
//        }
//}

/****************************************************************************/

void MetaVisitor::reset ()
{
        services.clear ();
        if (ctx) {
                ctx->reset ();
        }
}

}
