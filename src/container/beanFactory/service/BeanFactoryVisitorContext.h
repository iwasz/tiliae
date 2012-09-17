/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORYVISITORCONTEXT_H_
#define BEANFACTORYVISITORCONTEXT_H_

#include "container/metaStructure/service/VisitorContext.h"
#include "container/beanFactory/BeanFactory.h"
#include "container/beanFactory/BeanFactoryContainer.h"

namespace Container {

/**
 *
 */
class BeanFactoryVisitorContext : public VisitorContext {
public:

        BeanFactoryVisitorContext () : beanFactoryMap (NULL), container (NULL), currentBF (NULL) {}
        virtual ~BeanFactoryVisitorContext () { delete currentBF; }

        /**
         * Mapa wynikowa zawierająca fabryki, które będą fizycznie tworzyć
         * beany.
         */
        BeanFactoryMap *getBeanFactoryMap () const { return beanFactoryMap; };
        void setBeanFactoryMap (BeanFactoryMap *b) { beanFactoryMap = b; };

        BeanFactory *getCurrentBF () const { return currentBF; }
        void setCurrentBF (BeanFactory *c) { currentBF = c; }

        BeanFactoryContainer *getBeanFactoryContainer () const { return container; }
        void setBeanFactoryContainer (BeanFactoryContainer *c) { container = c; }

private:

        BeanFactoryMap *beanFactoryMap;
        BeanFactoryContainer *container;
        BeanFactory *currentBF;

};

} // nam

#	endif /* BEANFACTORYVISITORCONTEXT_H_ */
