/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_ANNOTATIONS
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "AnnotationManager.h"
#include "reflection/wrapper/ICallableWrapper.h"
#include "reflection/wrapper/FieldWrapper.h"
#include "reflection/reflectAnnotations/MethodAnnotation.h"
#include "reflection/reflectAnnotations/FieldAnnotation.h"

namespace Annotations {

AnnotationManager &AnnotationManager::instance ()
{
//        static AnnotationManager *neverDelete = new AnnotationManager ();
//        return *neverDelete;
        static AnnotationManager annotationMmanager;
        return annotationMmanager;

}

/****************************************************************************/

AnnotationManager::~AnnotationManager ()
{
        for (AnnotationList::iterator i = annotationList.begin (); i != annotationList.end (); ++i) {
                delete *i;
        }
}

/****************************************************************************/

bool AnnotationManager::addAnnotation (IAnnotation *a)
{
        AnnotationList::const_iterator i = annotationList.find (a->getHash ());

        if (i != annotationList.end ()) {
                a->deleteDuplicate ();
                delete a;
                return false;
        }

        annotationList.insert (a);
        return true;
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
#endif
