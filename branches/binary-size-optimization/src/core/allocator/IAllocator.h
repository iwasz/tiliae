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
#include "Exception.h"
#include "../../core/ApiMacro.h"

namespace Core {

/**
 * Interfejs klas, które służą do pozyskiwania pamięci.
 */
class TILIAE_API IAllocator {
public:
        virtual ~IAllocator () {}
        virtual void *malloc (size_t size) = 0;
        virtual void free (void *p) = 0;
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
