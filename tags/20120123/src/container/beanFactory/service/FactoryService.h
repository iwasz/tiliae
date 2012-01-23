/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FACTORYSERVICE_H_
#define FACTORYSERVICE_H_

#include "beanFactory/service/BeanFactoryService.h"

namespace Editor {
class IndexedEditor;
}

namespace Container {

class IMeta;

/**
 * Create factory
 */
class FactoryService : public BeanFactoryService {
public:

        virtual ~FactoryService () {}
        static Ptr <FactoryService> create () { return Ptr <FactoryService> (new FactoryService); }
        void init (Core::VariantMap *singletons);

        virtual bool onMetaBegin (IMeta *data);

private:

        Ptr <Editor::IndexedEditor> createIndexedEditor ();

private:

        // Singletons
        Ptr <Factory::IFactory> defaultFactory;
};

} //nam

#	endif /* FACTORYSERVICE_H_ */
