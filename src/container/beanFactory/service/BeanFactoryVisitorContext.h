/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORYVISITORCONTEXT_H_
#define BEANFACTORYVISITORCONTEXT_H_

#include "metaStructure/service/VisitorContext.h"
#include "beanFactory/BeanFactory.h"

namespace Container {

/**
 *
 */
class BeanFactoryVisitorContext : public VisitorContext {
public:

        virtual ~BeanFactoryVisitorContext () {}

        /**
         * Mapa wynikowa zawierająca fabryki, które będą fizycznie tworzyć
         * beany.
         */
        Ptr <BeanFactoryMap> getBeanFactoryMap () const { return beanFactoryMap; };
        void setBeanFactoryMap (Ptr <BeanFactoryMap> b) { beanFactoryMap = b; };

        const BeanFactoryStack &getStack () const { return stack; }
        BeanFactoryStack &getStack () { return stack; }
        void setStack (const BeanFactoryStack &s) { stack = s; }

        Ptr <BeanFactory> getCurrentBF () const;

        Ptr <BeanFactoryContainer> getBeanFactoryContainer () const { return container; }
        void setBeanFactoryContainer (Ptr <BeanFactoryContainer> c) { container = c; }

private:

        Ptr <BeanFactoryMap> beanFactoryMap;
        Ptr <BeanFactoryContainer> container;
        BeanFactoryStack stack;

};

} // nam

#	endif /* BEANFACTORYVISITORCONTEXT_H_ */
