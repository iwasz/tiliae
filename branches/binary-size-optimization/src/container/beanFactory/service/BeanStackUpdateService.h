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

class IMeta;

/**
 * Updates beanStack in context.
 */
class BeanStackUpdateService : public BeanFactoryService {
public:

        virtual ~BeanStackUpdateService () {}
        static Ptr <BeanStackUpdateService> create () { return Ptr <BeanStackUpdateService> (new BeanStackUpdateService); }

/*--------------------------------------------------------------------------*/

        virtual bool onMetaBegin (IMeta *data);
        virtual bool onMetaEnd (IMeta *data);

};

}

#	endif /* BEANSTACKUPDATESERVICE_H_ */
