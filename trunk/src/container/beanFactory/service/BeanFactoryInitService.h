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

        virtual ~BeanFactoryInitService () {}
        static Ptr <BeanFactoryInitService> create () { return Ptr <BeanFactoryInitService> (new BeanFactoryInitService); }

/*--------------------------------------------------------------------------*/

        virtual bool onMetaBegin (IMeta *meta);
        virtual bool onMetaEnd (IMeta *meta);

/*------Setters-and-getters-------------------------------------------------*/

        Ptr <Wrapper::BeanWrapper> getDefaultBeanWrapper () const { return defaultBeanWrapper; }
        void setDefaultBeanWrapper (Ptr <Wrapper::BeanWrapper> bw) { defaultBeanWrapper = bw; }

private:

        Ptr <Wrapper::BeanWrapper> defaultBeanWrapper;

};

}

#	endif /* BEANFACTORYINITSERVICE_H_ */
