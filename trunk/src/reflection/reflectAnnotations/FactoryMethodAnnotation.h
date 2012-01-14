/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FACTORY_METHODANNOTATION_H_
#define FACTORY_METHODANNOTATION_H_

#include "Manager.h"
#include "../annotations/Macros.h"

/**
 * Wymaga, aby klasa miała metodę:
 * <pre>
 * static void addAnnotations (const Core::String &className)
 * </pre>
 */
#define REFLECTION_FACTORY_ANNOTATION_BODY_PUBLIC_WNAME(name,type)                                            \
                                                                                                              \
        ANNOTATION_RUN_ONCE_AT_STARTUP(type::addAnnotations(name);)

#define REFLECTION_FACTORY_ANNOTATION_BODY_PUBLIC(type)                                                       \
                                                                                                              \
        ANNOTATION_RUN_ONCE_AT_STARTUP(type::addAnnotations(#type);)

#endif /* METHODANNOTATION_H_ */
