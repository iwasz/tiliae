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
#include "../../metaStructure/model/MetaObject.h"

namespace Container {

void MetaVisitor::visit (MetaContainer *container)
{
        assert (ctx);
        ctx->resetDepth ();
        ctx->setMetaContainer (container);

        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                (*i)->onContainer (container);
        }

        for (MetaVector::const_iterator i = container->getMetaVector ().begin (); i != container->getMetaVector ().end (); ++i) {
                (*i)->accept (this);
        }
}

/****************************************************************************/

void MetaVisitor::visit (MetaObject *data)
{
        foreach (IMetaService *service, services) {
                service->onMetaBegin (data);

                if (data->getType () == MetaObject::INDEXED) {
                        service->onIndexedMetaBegin (data);
                }
                else {
                        service->onMappedMetaBegin (data);
                }
        }

        DataKeyVector fields = data->getFields ();
        for (DataKeyVector::iterator i = fields.begin (); i != fields.end (); ++i) {
                (*i)->data->accept (((*i)->key) ? (std::string ((*i)->key)) : (std::string ()), this);
        }

        foreach (IMetaService *service, services) {
                service->onConstructorArgsBegin (data);
        }

        DataVector cArgs = data->getConstructorArgs();
        for (DataVector::iterator i = cArgs.begin (); i != cArgs.end (); ++i) {
                (*i)->accept (std::string (), this);
        }

        foreach (IMetaService *service, services) {
                service->onConstructorArgsEnd (data);
        }

        visitInnerMeta (data);

        foreach (IMetaService *service, services) {
                service->onMetaEnd (data);

                if (data->getType () == MetaObject::INDEXED) {
                        service->onIndexedMetaEnd (data);
                }
                else {
                        service->onMappedMetaEnd (data);
                }
        }
}

/****************************************************************************/

void MetaVisitor::visitInnerMeta (MetaObject *data)
{
        ctx->incDepth ();

        foreach (MetaMap::value_type p, data->getInnerMetas ()) {
                MetaObject *meta = p.second;
                meta->accept (this);
        }

        ctx->decDepth ();
}

/****************************************************************************/

void MetaVisitor::visit (std::string const &key, ValueData *data)
{
        foreach (IMetaService *service, services) {
                service->onValueData (key, data);
        }
}

/****************************************************************************/

void MetaVisitor::visit (std::string const &key, NullData *data)
{
        foreach (IMetaService *service, services) {
                service->onNullData (key, data);
        }
}

/****************************************************************************/

void MetaVisitor::visit (std::string const &key, RefData *data)
{
        foreach (IMetaService *service, services) {
                service->onRefData (key, data);
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
