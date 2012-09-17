/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTEXT_K202_H_
#define CONTEXT_K202_H_

#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/Pointer.h"

namespace Wrapper {
class IBeanWrapper;
}

namespace k202 {

/**
 * Klasa pomocniczego obieku (DTO), który implementuje operacje
 * wykonywane przez wyrażenia (pozwala pobrać wartość beana,
 * pobrać wskaźnik do metody (Reflection::Method etc).
 */
class TILIAE_API Context {
public:

        Context () : paramVector (NULL), argsMap (NULL), domain (NULL) {}
        virtual ~Context () {}

        Ptr <Wrapper::IBeanWrapper> getBeanWrapper () const { return bwrap; }
        void setBeanWrapper (Ptr <Wrapper::IBeanWrapper> b) { bwrap = b; }

        Core::Variant *getDomain () const { return domain; }
        void setDomain (Core::Variant *domain) { this->domain = domain; }

        Core::VariantVector *getParamVector () const { return paramVector; }
        void setParamVector (Core::VariantVector *paramVector) { this->paramVector = paramVector; }

        Core::VariantMap *getArgsMap () const { return argsMap; }
        void setArgsMap (Core::VariantMap *argsMap);

        Core::Variant getParam (unsigned int idx) const;

        /**
         * @param conditional Whether absence of property in beanWrapper should
         * throw exception or not.
         */
        Core::Variant getArg (const std::string &path, bool conditional = false) const;
        void setArg (const std::string &path, const Core::Variant &obj);
        Core::Variant callFunction (const std::string &path, Core::VariantVector &args);

private:

        Core::VariantVector *paramVector;
        Core::VariantMap *argsMap;
        Core::Variant *domain;
        Ptr <Wrapper::IBeanWrapper> bwrap;
        Core::Variant mapAsVariant;

};

}

#endif /* CONTEXT_H_ */
