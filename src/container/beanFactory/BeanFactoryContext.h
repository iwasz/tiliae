/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANFACTORYCONTEXT_H_
#define BEANFACTORYCONTEXT_H_

#include "../../core/Context.h"

namespace Container {

/**
 * Kontekst z dodatkowymi ficzerami dla BeanFactory.
 */
class BeanFactoryContext : public Core::Context {
public:

        BeanFactoryContext () : nested (0) {}
        virtual ~BeanFactoryContext () {}

        unsigned int getNested () const { return nested; }
        void setNested (unsigned int nested) { this->nested = nested; }
        void incNested () { ++nested; }
        void decNested () { --nested; }

private:

        unsigned int nested;
};

}

#	endif /* BEANFACTORYCONTEXT_H_ */
