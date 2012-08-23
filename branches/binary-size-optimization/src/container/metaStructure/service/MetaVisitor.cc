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

        for (MetaMap::const_iterator i = container->getMetaMap ().begin (); i != container->getMetaMap ().end (); ++i) {
                i->second->accept (this);
        }
}

/****************************************************************************/

void MetaVisitor::visit (MetaDeque *sorted)
{
        assert (ctx);
        ctx->resetDepth ();

        for (MetaDeque::const_iterator i = sorted->begin (); i != sorted->end (); ++i) {
                (*i)->accept (this);
        }
}

/****************************************************************************/

void MetaVisitor::visit (MetaObject const *data)
{
        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                IMetaService *service = *i;

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

        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                IMetaService *service = *i;
                service->onConstructorArgsBegin (data);
        }

        DataVector cArgs = data->getConstructorArgs();
        for (DataVector::iterator i = cArgs.begin (); i != cArgs.end (); ++i) {
                (*i)->accept (std::string (), this);
        }

        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                IMetaService *service = *i;
                service->onConstructorArgsEnd (data);
        }

        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                IMetaService *service = *i;
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

void MetaVisitor::visit (std::string const &key, ValueData *data)
{
        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                IMetaService *service = *i;
                service->onValueData (key, data);
        }
}

/****************************************************************************/

void MetaVisitor::visit (std::string const &key, NullData *data)
{
        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                IMetaService *service = *i;
                service->onNullData (key, data);
        }
}

/****************************************************************************/

void MetaVisitor::visit (std::string const &key, RefData *data)
{
        for (MetaServiceVector::iterator i = services.begin (); i != services.end (); ++i) {
                IMetaService *service = *i;
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
