/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REFLECT_CONSTRUCTOR_H
#define REFLECT_CONSTRUCTOR_H

#include <vector>
#include <wctype.h>
#include "reflection/wrapper/ConstructorPointer.h"
#include "core/IToStringEnabled.h"
#include "core/Pointer.h"
#include "core/ApiMacro.h"
#include "core/allocator/IAllocator.h"

namespace Reflection {

/**
 *
 */
class TILIAE_API Constructor : public Core::IToStringEnabled {
public:

        Constructor (IConstructorPointer *cp) : constructorPointer (cp) {}
        virtual ~Constructor () { delete constructorPointer; }

        std::type_info const &getType () const { return constructorPointer->getType (); }
        unsigned int getArity () const { return constructorPointer->getArity (); }

        /**
         *  Instantiates a class this constructor is member of.
         */
        Core::Variant newInstance (Core::VariantVector *ol = NULL, Core::IAllocator *allocator = NULL);
        Core::Variant newInstance (Core::Variant const &c, Core::IAllocator *allocator = NULL);

        /**
         *  Returns string representing this Constructor. For debugging purposes.
         */
        std::string toString () const;

private:

        IConstructorPointer *constructorPointer;
};

/*##########################################################################*/

typedef std::vector <Constructor *> ConstructorList;


} // namespace

#endif

