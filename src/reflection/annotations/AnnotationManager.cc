/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "AnnotationManager.h"
#include "../wrapper/ICallableWrapper.h"
#include "../wrapper/FieldWrapper.h"
#include "../reflectAnnotations/MethodAnnotation.h"
#include "../reflectAnnotations/FieldAnnotation.h"

namespace Annotations {

AnnotationManager &AnnotationManager::instance ()
{
        static AnnotationManager *neverDelete = new AnnotationManager ();
        return *neverDelete;
}

/****************************************************************************/

std::string AnnotationManager::toString () const
{
        std::string ret = std::string ("AnnotationManager (noOfAnnotations:") +
                        boost::lexical_cast <std::string> (annotationList.size ()) +
                        ", annotations:";

        AnnotationList::const_iterator i = annotationList.begin ();

        while (i != annotationList.end ()) {

                IAnnotation *a = *i;
                ret += a->toString ();

                if (++i != annotationList.end ()) {
                        ret += ", ";
                }
        }

        return ret + ")";
}

/****************************************************************************/

void AnnotationManager::addMethodAnnotation (std::string const &clsName, std::string const &methName, Reflection::ICallableWrapper *wrapper)
{
        instance ().annotationList.insert (new Reflection::MethodAnnotation (clsName, methName, wrapper));
}

/****************************************************************************/

void AnnotationManager::addFieldAnnotation (std::string const &clsName, std::string const &fieldName, Reflection::IFieldWrapper *wrapper)
{
        instance ().annotationList.insert (new Reflection::FieldAnnotation (clsName, fieldName, wrapper));
}

}
