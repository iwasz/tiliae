/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIMPLERULE_H_
#define SIMPLERULE_H_

#include "IRule.h"
#include "IEditor.h"

namespace Editor {

class SimpleRule : public Editor::IRule {
public:

        SimpleRule (const Core::String &sIn = Core::String (),
                        const Core::String &sOut = Core::String (),
                        IEditor *e = NULL) :
                inputPath (sIn),
                outputPath (sOut),
                editor (e) {}

        virtual ~SimpleRule () {}

/*------IRule---------------------------------------------------------------*/

        virtual Core::String getOutputPath (const Core::String &inputPath) const;
        virtual IEditor *getEditor (const Core::String &inputPath) const { return editor; }
        virtual bool supports (const Core::String &inputPath) const;
        virtual PathPair splitPath (const Core::String &inputPath) const;
        virtual Core::StringList getInputs () const;

/*--------------------------------------------------------------------------*/

        Core::String getInputPath () const { return inputPath; }
        void setInputPath (const Core::String &inputPath) { this->inputPath = inputPath; }

        Core::String getOutputPath () const { return outputPath; }
        void setOutputPath (const Core::String &outputPath) { this->outputPath = outputPath; }

        void setEditor(IEditor *editor) { this->editor = editor; }

private:

        Core::String inputPath;
        Core::String outputPath;
        IEditor *editor;

};

}

#endif /* SIMPLERULE_H_ */
