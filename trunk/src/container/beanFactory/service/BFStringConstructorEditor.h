/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BFSTRINGCONSTRUCTOREDITOR_H_
#define BFSTRINGCONSTRUCTOREDITOR_H_

#include "editor/StringConstructorEditor.h"
#include "container/common/SparseVariantMap.h"

namespace Container {

class BFStringConstructorEditor : public Editor::StringConstructorEditor {
public:

        BFStringConstructorEditor (SparseVariantMap *s, Core::IAllocator *a = NULL) : Editor::StringConstructorEditor (a), singletons (s) {}
        virtual ~BFStringConstructorEditor() {}

        virtual bool convert (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

private:

        const char *generateId () const;

private:

        SparseVariantMap *singletons;

        /// Do automatycznego generowania ID.
        static int singletonNumber;

};

} /* namespace Container */
#endif /* BFSTRINGCONSTRUCTOREDITOR_H_ */
