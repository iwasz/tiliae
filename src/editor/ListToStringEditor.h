/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LISTTOSTRINGEDITOR_H_
#define LISTTOSTRINGEDITOR_H_

#include "reflection/Reflection.h"
#include <iosfwd>
#include "editor/JEditor.h"
#include "core/ApiMacro.h"
#include "ReflectionParserAnnotation.h"

namespace Editor {

/**
 * Konwertuje liste StringList na String.
 */
class TILIAE_API __tiliae_reflect__ ListToStringEditor : public JEditor {
public:

        ListToStringEditor () : delimiter (","), quotation ("\"") {}
        ListToStringEditor (const std::string &d, const std::string &q) : delimiter (d), quotation (q) {}

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

        std::string getDelimiter () const { return delimiter; }
        void setDelimiter (const std::string &delimiter) { this->delimiter = delimiter; }

        std::string getQuotation () const { return quotation; }
        void setQuotation (const std::string &quotation) { this->quotation = quotation; }

private:

        std::string delimiter;
        std::string quotation;
};

}

#endif /* LISTTOSTRINGEDITOR_H_ */
