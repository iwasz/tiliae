/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PTRDELETER_H_
#define PTRDELETER_H_

#include "Cast.h"

namespace Core {

template <typename T>
class PtrDeleter : public IDeleter {
        virtual ~PtrDeleter () {}
        virtual void free (Variant &v);
};

template <typename T>
void PtrDeleter<T>::free (Variant &v)
{
        delete vcast <T *> (v);
}

} /* namespace Core */
#endif /* PTRDELETER_H_ */
