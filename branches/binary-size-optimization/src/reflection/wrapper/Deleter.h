/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PTRDELETER_H_
#define PTRDELETER_H_

#include "variant/Variant.h"
#include "variant/Cast.h"

namespace Reflection {

struct IDeleter {

        virtual ~IDeleter () {}
        virtual void free (Core::Variant &v) = 0;
};

template <typename T>
class PtrDeleter : public IDeleter {
        virtual ~PtrDeleter () {}
        virtual void free (Core::Variant &v);
};

template <typename T>
void PtrDeleter<T>::free (Core::Variant &v)
{
        delete vcast <T *> (v);
}

} /* namespace Reflection */
#endif /* PTRDELETER_H_ */
