/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IALLOCATOR_H_
#define IALLOCATOR_H_

#include <cstddef>
#include "ApiMacro.h"
#include "Exception.h"

namespace Core {

struct TILIAE_API IAllocator {

        virtual ~IAllocator () {}
        virtual void *malloc (size_t size) = 0;

};

/**
 * Problem z alokacją pamięci.
 */
class TILIAE_API AllocationException : public Exception {
public:

        AllocationException (std::string const &s = "") : Exception (s) {}
        AllocationException (DebugContext const &db, std::string const &s = "") : Exception (db, s) {}
        virtual ~AllocationException () throw () {}

};

} /* namespace Core */
#endif /* IALLOCATOR_H_ */
