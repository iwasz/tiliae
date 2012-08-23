/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "InternalSingletons.h"
#include "IFactory.h"
#include "IEditor.h"
#include "BeanWrapper.h"
#include "Defs.h"

namespace Container {

InternalSingletons::~InternalSingletons()
{
        delete noop;
        delete noopNoCopy;
        delete defaultSingletonFactory;
        delete beanWrapperSimple;
        delete beanWrapperConversion;
}

Core::Variant InternalSingletons::get (std::string const &key) const
{
        if (key == DEFAULT_MAPPED_EDITOR_NAME) {
                return Core::Variant (noop);
        }
        else if (key == DEFAULT_INDEXED_EDITOR_NAME) {
                return Core::Variant (noop);
        }
        else if (key == NOOP_EDITOR_NAME) {
                return Core::Variant (noop);
        }
        else if (key == NOOP_NO_COPY_EDITOR_NAME) {
                return Core::Variant (noopNoCopy);
        }
        else if (key == DEFAULT_SINGLETON_FACTORY_NAME) {
                return Core::Variant (defaultSingletonFactory);
        }
        else if (key == DEFAULT_VALUE_FACTORY_NAME) {
                return Core::Variant (defaultValueFactory);
        }
        else if (key == BEAN_WRAPPER_SIMPLE) {
                return Core::Variant (beanWrapperSimple);
        }
        else if (key == BEAN_WRAPPER_W_CONVERSION) {
                return Core::Variant (beanWrapperConversion);
        }
        else if (key == MAIN_TYPE_EDITOR) {
                return Core::Variant (mainTypeEditor);
        }
        else if (key == MAIN_METHOD_CONVERSION_EDITOR) {
                return Core::Variant (mainMethodConversionEditor);
        }

        return Core::Variant ();
}

} /* namespace Container */
