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

extern const char *DEFAULT_OBJECT_FACTORY_NAME;
extern const char *DEFAULT_VALUE_FACTORY_NAME;
extern const char *DEFAULT_INDEXED_EDITOR_NAME;
extern const char *DEFAULT_MAPPED_EDITOR_NAME;
extern const char *NOOP_EDITOR_NAME;
extern const char *NOOP_NO_COPY_EDITOR_NAME;
extern const char *BEAN_WRAPPER_W_CONVERSION;
extern const char *BEAN_WRAPPER_SIMPLE;
extern const char *DEFAULT_VALUE_TYPE;
const unsigned int MAX_BEAN_NESTING = 1000;
extern const char *REFERENCE_TO_CONTAINER_ITSELF;
extern const char *MAIN_TYPE_EDITOR;
extern const char *MAIN_METHOD_CONVERSION_EDITOR;

}

#endif /* ICONTAINER_H_ */
