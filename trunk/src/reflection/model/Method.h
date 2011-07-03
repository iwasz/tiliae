/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_METHOD_H_
#define TILIAE_METHOD_H_

#include <list>

#include "../wrapper/ICallableWrapper.h"
#include "../../core/IToStringEnabled.h"
#include "../../core/Typedefs.h"
#include "../../core/string/String.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"

namespace Reflection {

/**
 *  Represents a method in a class. Method can be invoked or simply
 *  queried for particular property value.
 */
class TILIAE_API Method : public Core::IToStringEnabled {
public:

        Method (const std::string &n,
                const Ptr <ICallableWrapper> &c) : name (n), callableWrapper (c) {}

        virtual ~Method () {}

        std::string getName () const { return this->name; }
        void setName (const std::string &name) { this->name = name; }

        Ptr<ICallableWrapper> getCallableWrapper () const { return this->callableWrapper; }
        void setCallableWrapper (Ptr<ICallableWrapper> callableWrapper) { this->callableWrapper = callableWrapper; }

        std::type_info const &getType () const { return callableWrapper->getType (); }
        int getArity () const { return callableWrapper->getArity (); }

/*--------------------------------------------------------------------------*/

        /// Szczególny przypadek : 1 arg.
        Core::Variant invoke (Core::Variant const &o, Core::Variant const &arg);
        Core::Variant invoke (Core::Variant const &o, Core::VariantVector *list = NULL);

/*--------------------------------------------------------------------------*/

        std::string toString () const;

private:

        std::string name;
        Ptr <ICallableWrapper> callableWrapper;

};

typedef std::list <Ptr <Method> > MethodList;

}

#endif

