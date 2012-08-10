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

        BeanFactoryVisitorContext () : beanFactoryMap (NULL), container (NULL) {}
        virtual ~BeanFactoryVisitorContext () {}

        /**
         * Mapa wynikowa zawierająca fabryki, które będą fizycznie tworzyć
         * beany.
         */
        BeanFactoryMap *getBeanFactoryMap () const { return beanFactoryMap; };
        void setBeanFactoryMap (BeanFactoryMap *b) { beanFactoryMap = b; };

        const BeanFactoryStack &getStack () const { return stack; }
        BeanFactoryStack &getStack () { return stack; }
        void setStack (const BeanFactoryStack &s) { stack = s; }

        BeanFactory *getCurrentBF () const;

        BeanFactoryContainer *getBeanFactoryContainer () const { return container; }
        void setBeanFactoryContainer (BeanFactoryContainer *c) { container = c; }

private:

        BeanFactoryMap *beanFactoryMap;
        BeanFactoryContainer *container;
        BeanFactoryStack stack;

};

} // nam

#	endif /* BEANFACTORYVISITORCONTEXT_H_ */
