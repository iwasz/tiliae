/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORYINITSERVICE_H_
#define BEANFACTORYINITSERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Container {

class IMeta;

/**
 * Creates BeanFactory object upon information from meta-structure.
 */
class BeanFactoryInitService : public BeanFactoryService {
public:

        BeanFactoryInitService () : defaultBeanWrapper (NULL) {}
        virtual ~BeanFactoryInitService () {}

/*--------------------------------------------------------------------------*/

        virtual bool onMetaBegin (IMeta *meta);
        virtual bool onMetaEnd (IMeta *meta);

/*------Setters-and-getters-------------------------------------------------*/

        void setDefaultBeanWrapper (Wrapper::BeanWrapper *bw) { defaultBeanWrapper = bw; }

private:

        Wrapper::BeanWrapper *defaultBeanWrapper;

};

}

#	endif /* BEANFACTORYINITSERVICE_H_ */
