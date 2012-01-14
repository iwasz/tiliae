/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEFAULTANNOTATIONMACROS_H_
#define DEFAULTANNOTATIONMACROS_H_

#undef _b
#undef __b
#undef __d
#undef _g
#undef _c
#undef __c
#undef _fn
#undef _f
#undef _m
#undef __m
#undef _M
#undef __M
#undef _Mc
#undef __M
#undef _s
#undef __s
#undef _e
#undef __e
#undef _tb
#undef _t
#undef _te

#define _b      REFLECTION_BASE_CLASS_ANNOTATION_BODY_PUBLIC
#define __b     REFLECTION_BASE_CLASS_ANNOTATION_BODY_PUBLIC_COMBO
#define __d     REFLECTION_CLASS_ANNOTATION_BODY_PUBLIC_COMBO
#define _g      REFLECTION_COLLECTION_ANNOTATION_BODY_PUBLIC
#define _c      REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PUBLIC
#define __c     REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PUBLIC_COMBO
#define _fn     REFLECTION_FACTORY_ANNOTATION_BODY_PUBLIC_WNAME
#define _f      REFLECTION_FACTORY_ANNOTATION_BODY_PUBLIC
#define _m      REFLECTION_METHOD_ANNOTATION_BODY_PUBLIC
#define __m     REFLECTION_METHOD_ANNOTATION_BODY_PUBLIC_COMBO
#define _M      REFLECTION_OVERLOADED_METHOD_ANNOTATION_BODY_PUBLIC
#define __M     REFLECTION_OVERLOADED_METHOD_ANNOTATION_BODY_PUBLIC_COMBO
#define _Mc     REFLECTION_OVERLOADED_CONST_METHOD_ANNOTATION_BODY_PUBLIC
#define __Mc    REFLECTION_OVERLOADED_CONST_METHOD_ANNOTATION_BODY_PUBLIC_COMBO
#define _s      REFLECTION_SETTER_ANNOTATION_BODY_PUBLIC
#define __s     REFLECTION_SETTER_ANNOTATION_BODY_PUBLIC_COMBO
#define _e      REFLECTION_END_ANNOTATION_BODY_PUBLIC
#define __e     REFLECTION_END_ANNOTATION_BODY_PUBLIC_COMBO
#define _tb     REFLECTION_TEMPLATE_BEGIN_ANNOTATION_BODY_PUBLIC
#define _t      REFLECTION_TEMPLATE_ANNOTATION_BODY_PUBLIC
#define _te     REFLECTION_TEMPLATE_END_ANNOTATION_BODY_PUBLIC

#	endif /* DEFAULTANNOTATIONMACROS_H_ */
