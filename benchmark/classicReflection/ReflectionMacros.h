/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SPECIFIC_ANNOTATIONMACROS_H_
#define SPECIFIC_ANNOTATIONMACROS_H_

#include <reflection/Reflection.h>

#define bse_      REFLECTION_BASE_CLASS
#define bse__     REFLECTION_BASE_CLASS_
#define abt__     REFLECTION_CLASS
#define col_      REFLECTION_COLLECTION
#define ctr_      REFLECTION_CONSTRUCTOR
#define ctr__     REFLECTION_CONSTRUCTOR_
#define fcn_      REFLECTION_FACTORY_NAME
#define fct_      REFLECTION_FACTORY
#define mth_      REFLECTION_METHOD
#define mth__     REFLECTION_METHOD_
#define mto_      REFLECTION_OVERLOADED_METHOD
#define mto__     REFLECTION_OVERLOADED_METHOD_
#define mtc_      REFLECTION_OVERLOADED_CONST_METHOD
#define mtc__     REFLECTION_OVERLOADED_CONST_METHOD_
#define stt_      REFLECTION_SETTER
#define stt__     REFLECTION_SETTER_
#define end_      REFLECTION_END
#define end__     REFLECTION_END_
#define endt_     REFLECTION_END_TOKEN
#define endt__    REFLECTION_END_TOKEN_
#define tbg_      REFLECTION_TEMPLATE_BEGIN
#define tpl__     REFLECTION_TEMPLATE
#define ten_      REFLECTION_TEMPLATE_END
#define prp_      REFLECTION_FIELD_VALUE_INPLACE
#define pre_      REFLECTION_FIELD_ENUM_INPLACE
#define prr_      REFLECTION_FIELD_REFERENCE_INPLACE

#	endif /* DEFAULTANNOTATIONMACROS_H_ */
