/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "../core/variant/Variant.h"
#include "../core/Typedefs.h"
#include "../core/string/String.h"
#include "../core/Pointer.h"

namespace k202 {

class ByteCode;
class Context;

/**
 * Encapsulates bytecode, sourceCode and arguments for a k202 script.
 * Once created, script cannot be modified. You must create another
 * Script object instead. Only args, params and domain object are
 * changeable.
 */
class Script {
public:

        virtual ~Script () {}

        /**
         * Run script with args and params. If script is not compiled,
         * exception will be thrown. Warning : this method midifies ctx
         * argument.
         */
        Core::Variant run (Context *ctx,
                           Core::Variant *domain = NULL,
                           const Core::VariantVector &paramVector = Core::VariantVector (),
                           const Core::VariantMap &argsMap = Core::VariantMap ());

        const Core::Variant &getDomain () { return domain; }

        const Core::VariantVector &getParamVector () const { return paramVector; }
        void setParamVector (const Core::VariantVector &paramVector) { this->paramVector = paramVector; }

        const Core::VariantMap &getArgsMap () const { return argsMap; }
        void setArgsMap (const Core::VariantMap &map) { argsMap = map; }

        const std::string &getSourceCode () const { return sourceCode; }

private:

        /**
         * Can be created only by K202::prepare.
         */
        Script (const std::string &srcCde, Ptr <ByteCode> bc, const Core::Variant &dmn) : sourceCode (srcCde), domain (dmn), byteCode (bc) {}
        Script (const Script &) {}
        friend class K202;

private:

        std::string sourceCode;
        Core::Variant domain;
        Core::VariantVector paramVector;
        Core::VariantMap argsMap;
        Ptr <ByteCode> byteCode;

};

}

#endif /* SCRIPT_H_ */
