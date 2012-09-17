/*
 * WrapperCommons.h
 *
 *  Created on: Dec 1, 2010
 *      Author: iwasz
 */

#ifndef WRAPPERCOMMONS_H_
#define WRAPPERCOMMONS_H_

#include <string>
#include "core/ApiMacro.h"
#include "core/Exception.h"
#include "core/Typedefs.h"

namespace Reflection {

/**
 * Ogólna klasa wyjątków zrzucanych z wrapperów.
 */
struct TILIAE_API WrapperException : public Core::Exception {
        WrapperException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~WrapperException () throw () {}
};

/**
 * Porównuje liczbę argumentów.
 */
extern TILIAE_API void checkArgList (Core::VariantVector const *list, unsigned int size);

/**
 * Boundary check.
 */
extern TILIAE_API void checkCollectionSize (unsigned int requestedIdx, unsigned int size);

} //  nam

#endif /* WRAPPERCOMMONS_H_ */
