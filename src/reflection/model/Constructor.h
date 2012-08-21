/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef REFLECT_CONSTRUCTOR_H
#define REFLECT_CONSTRUCTOR_H

#include <list>

#include "../wrapper/ConstructorPointer.h"
#include "../../core/IToStringEnabled.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"
#include <wctype.h>

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
        Core::Variant newInstance (Core::VariantVector *ol = NULL, bool createDeleter = false);
        Core::Variant newInstance (Core::Variant const &c, bool createDeleter = false);

        /**
         *  Returns string representing this Constructor. For debugging purposes.
         */
        std::string toString () const;

private:

        IConstructorPointer *constructorPointer;
};

/*##########################################################################*/

// TODO vector
typedef std::list <Constructor *> ConstructorList;


} // namespace

#endif

