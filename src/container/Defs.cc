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
const char *DEFAULT_OBJECT_FACTORY_NAME = "&newObjectFactory";
const char *DEFAULT_VALUE_FACTORY_NAME = "&newValueFactory";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *DEFAULT_INDEXED_EDITOR_NAME = "@indexed";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *DEFAULT_MAPPED_EDITOR_NAME = "@mapped";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *NOOP_EDITOR_NAME = "@noop";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *NOOP_NO_COPY_EDITOR_NAME = "@noopNoCopy";

/**
 * ID obiektu systemowego.
 * \ingroup Container
 */
const char *BEAN_WRAPPER_W_CONVERSION = "beanWrapperConversion";

const char *BEAN_WRAPPER_SIMPLE = "beanWrapperSimple";

/**
 * Kiedy nie podamy value, to jaki ma być typ.
 */
const char *DEFAULT_VALUE_TYPE = "text";


}

#endif /* ICONTAINER_H_ */
