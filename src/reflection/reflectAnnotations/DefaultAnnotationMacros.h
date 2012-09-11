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
#undef gn_
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

#define b_      REFLECTION_BASE_CLASS
#define b__     REFLECTION_BASE_CLASS_
#define d__     REFLECTION_CLASS
#define g_      REFLECTION_COLLECTION
#define gn_     REFLECTION_COLLECTION_NAME
#define c_      REFLECTION_CONSTRUCTOR
#define c__     REFLECTION_CONSTRUCTOR_
#define fn_     REFLECTION_FACTORY_NAME
#define f_      REFLECTION_FACTORY
#define m_      REFLECTION_METHOD
#define m__     REFLECTION_METHOD_
#define M_      REFLECTION_OVERLOADED_METHOD
#define M__     REFLECTION_OVERLOADED_METHOD_
#define Mc_     REFLECTION_OVERLOADED_CONST_METHOD
#define Mc__    REFLECTION_OVERLOADED_CONST_METHOD_
#define s_      REFLECTION_SETTER
#define s__     REFLECTION_SETTER_
#define e_      REFLECTION_END
#define e__     REFLECTION_END_
#define tb_     REFLECTION_TEMPLATE_BEGIN
#define t_      REFLECTION_TEMPLATE
#define te_     REFLECTION_TEMPLATE_END

#	endif /* DEFAULTANNOTATIONMACROS_H_ */
