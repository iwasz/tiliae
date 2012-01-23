/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#ifndef IREFLECTANNOTATION_H_
#define IREFLECTANNOTATION_H_

#include "../annotations/IAnnotation.h"
#include "../../core/variant/Variant.h"

namespace Reflection {

struct IReflectionVisitor;

/**
 *
 */
struct IReflectionAnnotation : public Annotations::IAnnotation {

        virtual ~IReflectionAnnotation () {}
        /**
         * Will acceptt variuous operations on Annotations.
         * @param vis Visitor (tha means a class that implements some particular algorithm on IAnnotation).
         * @param args Additional args (input).
         * @return Output.
         */
        virtual Core::Variant accept (IReflectionVisitor *vis, const Core::Variant &args = Core::Variant ()) = 0;

};

} // namespace

#endif /* IREFLECTANNOTATION_H_ */
