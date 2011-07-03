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

        Constructor (Ptr <IConstructorPointer> cp) : constructorPointer (cp) {}
        virtual ~Constructor () {}

        Ptr<IConstructorPointer> getConstructorPointer() const { return constructorPointer; }
        void setConstructorPointer(Ptr<IConstructorPointer> constructorPointer) { this->constructorPointer = constructorPointer; }

        std::type_info const &getType () const { return constructorPointer->getType (); }
        unsigned int getArity () const { return constructorPointer->getArity (); }


        /**
         *  Instantiates a class this constructor is member of.
         */
        Core::Variant newInstance (Core::VariantVector *ol = NULL);
        Core::Variant newInstance (Core::Variant const &c);

        /**
         *  Returns string representing this Constructor. For debugging purposes.
         */
        std::string toString () const;

private:

        Ptr <IConstructorPointer> constructorPointer;
};

/*##########################################################################*/

typedef std::list <Ptr <Constructor> > ConstructorList;


} // namespace

#endif

