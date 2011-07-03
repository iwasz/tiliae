/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_CLASSVISITOR_H_
#define TILIAE_CLASSVISITOR_H_

#include "IReflectionVisitor.h"
#include "../Manager.h"
#include "../../core/string/String.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"
#include "../../core/Typedefs.h"

namespace Reflection {

class Class;

/**
 * Zwraca klase z managera, lub tworzy i dodaje, jeśli w mamagerze
 * jej nie ma.
 */
class ClassVisitor : public IReflectionVisitor {
public:

        virtual ~ClassVisitor () {}

        virtual Core::Variant visit (BaseClassAnnotation *a, const Core::Variant &arg);
        virtual Core::Variant visit (MethodAnnotation *a, const Core::Variant &arg);
        virtual Core::Variant visit (ConstructorAnnotation *a, const Core::Variant &arg);
        virtual Core::Variant visit (ClassAnnotation *a, const Core::Variant &arg);

private:

        Ptr <Class> findClass (const std::string &className) const;
        Ptr <Class> createClass (const std::string &className, std::type_info const &classType);

private:

        Ptr <Class> cache;
};

}

#endif /* CLASSVISITOR_H_ */
