/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STRINGFACTORYMETHODEDITOR_H_
#define STRINGFACTORYMETHODEDITOR_H_
#include "editor/IEditor.h"
#include "core/ApiMacro.h"

namespace Editor {

/**
 * Edytor konwerujący stringi na różne obiekty. Działanie jest podobne do StringConstructorEditor.
 */
class TILIAE_API StringFactoryMethodEditor  : public IEditor {
public:

        typedef Core::Variant (*ConversionFunctionPtr) (std::string const &);

        virtual ~StringFactoryMethodEditor () {}
        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

        void addConversion (std::type_info const &type, ConversionFunctionPtr function) { container[&type] = function; }

private:

        typedef std::map <std::type_info const *, ConversionFunctionPtr> Container;
        Container container;

};

} /* namespace Editor */
#endif /* STRINGFACTORYMETHODEDITOR_H_ */
