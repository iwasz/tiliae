/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INDEX_RULE_H_
#define INDEX_RULE_H_

#include "IRule.h"
#include "IEditor.h"

namespace Editor {

/**
 * Akceptuje tylko sciezki bedace liczbami calkowitymi,
 * kazdej takiej liczbie odpowiada taka sama na wyjściu.
 */
class IndexRule : public Editor::IRule {
public:

        IndexRule (IEditor *e = NULL) : editor (e) {}
        virtual ~IndexRule () {}

/*------IRule---------------------------------------------------------------*/

        virtual Core::String getOutputPath (const Core::String &inputPath) const { return inputPath; }
        virtual IEditor *getEditor (const Core::String &inputPath) const { return editor; }
        // TODO
        virtual bool supports (const Core::String &inputPath) const { return true; }
        // TODO
        virtual PathPair splitPath (const Core::String &inputPath) const { return PathPair (); }
        virtual Core::StringList getInputs () const { return Core::StringList ();}

/*--------------------------------------------------------------------------*/

        void setEditor(IEditor *editor) { this->editor = editor; }

private:

        IEditor *editor;

};

}

#endif /* SIMPLERULE_H_ */
