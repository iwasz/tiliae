/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONTAINER_DEFS_H_
#define ICONTAINER_DEFS_H_

namespace Container {

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *DEFAULT_SINGLETON_FACTORY_NAME = "#defaultSingletonFactory";
const char *DEFAULT_PROTOTYPE_FACTORY_NAME = "#defaultPrototypeFactory";
const char *DEFAULT_VALUE_FACTORY_NAME = "#defaultValueFactory";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *DEFAULT_INDEXED_EDITOR_NAME = "#indexed";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *DEFAULT_MAPPED_EDITOR_NAME = "#mapped";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *NOOP_EDITOR_NAME = "#noop";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *NOOP_NO_COPY_EDITOR_NAME = "#noopNoCopy";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *BEAN_WRAPPER_W_CONVERSION_FOR_SINGLETONS = "#beanWrapperConversionForSingletons";
const char *BEAN_WRAPPER_W_CONVERSION_FOR_PROTOTYPES = "#beanWrapperConversionForPrototypes";

const char *BEAN_WRAPPER_SIMPLE = "#beanWrapperSimple";
const char *BEAN_WRAPPER_FOR_METHODS = "#beanWrapperForMethods";

/**
 * Kiedy nie podamy value, to jaki ma być typ.
 */
const char *DEFAULT_VALUE_TYPE = "text";


const char *REFERENCE_TO_CONTAINER_ITSELF = "#container";

const char *MAIN_TYPE_EDITOR = "#mainTypeEditor";
const char *MAIN_METHOD_CONVERSION_EDITOR = "#mainMethodConversionEditor";

}

#endif /* ICONTAINER_H_ */
