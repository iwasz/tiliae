/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INTERNALSINGLETONS_H_
#define INTERNALSINGLETONS_H_

#include "variant/Variant.h"
#include <string>

namespace Editor {
class IEditor;
}

namespace Factory {
class IFactory;
}

namespace Wrapper {
class BeanWrapper;
}

namespace Container {

/**
 * Container for service singletons, which are used by BeanFactoryContainer itself and
 * can be get by the user.
 */
struct InternalSingletons {

        ~InternalSingletons();

        Core::Variant get (std::string const &key) const;

        Editor::IEditor *noop;
        Editor::IEditor *noopNoCopy;
        Editor::IEditor *mainTypeEditor;
        Editor::IEditor *mainMethodConversionEditor;

        Factory::IFactory *defaultSingletonFactory;
        Factory::IFactory *defaultValueFactory;

        Wrapper::BeanWrapper *beanWrapperSimple;
        Wrapper::BeanWrapper *beanWrapperConversion;

};

} /* namespace Container */
#endif /* INTERNALSINGLETONS_H_ */
