/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEFAULTANNOTATIONMACROS_H_
#define DEFAULTANNOTATIONMACROS_H_

#undef b_
#undef b__
#undef d__
#undef g_
#undef c_
#undef c__
#undef fn_
#undef f_
#undef m_
#undef m__
#undef M_
#undef M__
#undef Mc_
#undef M__
#undef s_
#undef s__
#undef e_
#undef e__
#undef tb_
#undef t_
#undef te_

#define b_      REFLECTION_BASE_CLASS_ANNOTATION_BODY_PUBLIC
#define b__     REFLECTION_BASE_CLASS_ANNOTATION_BODY_PUBLIC_COMBO
#define d__     REFLECTION_CLASS_ANNOTATION_BODY_PUBLIC_COMBO
#define g_      REFLECTION_COLLECTION_ANNOTATION_BODY_PUBLIC
#define c_      REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PUBLIC
#define c__     REFLECTION_CONSTRUCTOR_ANNOTATION_BODY_PUBLIC_COMBO
#define fn_     REFLECTION_FACTORY_ANNOTATION_BODY_PUBLIC_WNAME
#define f_      REFLECTION_FACTORY_ANNOTATION_BODY_PUBLIC
#define m_      REFLECTION_METHOD_ANNOTATION_BODY_PUBLIC
#define m__     REFLECTION_METHOD_ANNOTATION_BODY_PUBLIC_COMBO
#define M_      REFLECTION_OVERLOADED_METHOD_ANNOTATION_BODY_PUBLIC
#define M__     REFLECTION_OVERLOADED_METHOD_ANNOTATION_BODY_PUBLIC_COMBO
#define Mc_     REFLECTION_OVERLOADED_CONST_METHOD_ANNOTATION_BODY_PUBLIC
#define Mc__    REFLECTION_OVERLOADED_CONST_METHOD_ANNOTATION_BODY_PUBLIC_COMBO
#define s_      REFLECTION_SETTER_ANNOTATION_BODY_PUBLIC
#define s__     REFLECTION_SETTER_ANNOTATION_BODY_PUBLIC_COMBO
#define e_      REFLECTION_END_ANNOTATION_BODY_PUBLIC
#define e__     REFLECTION_END_ANNOTATION_BODY_PUBLIC_COMBO
#define tb_     REFLECTION_TEMPLATE_BEGIN_ANNOTATION_BODY_PUBLIC
#define t_      REFLECTION_TEMPLATE_ANNOTATION_BODY_PUBLIC
#define te_     REFLECTION_TEMPLATE_END_ANNOTATION_BODY_PUBLIC

#	endif /* DEFAULTANNOTATIONMACROS_H_ */
