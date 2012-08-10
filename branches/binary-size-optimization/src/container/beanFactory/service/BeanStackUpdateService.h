/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANSTACKUPDATESERVICE_H_
#define BEANSTACKUPDATESERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Container {

class MetaObject;

/**
 * Updates beanStack in context.
 */
class BeanStackUpdateService : public BeanFactoryService {
public:

        virtual ~BeanStackUpdateService () {}

/*--------------------------------------------------------------------------*/

        virtual bool onMetaBegin (MetaObject *data);
        virtual bool onMetaEnd (MetaObject *data);

};

}

#	endif /* BEANSTACKUPDATESERVICE_H_ */
