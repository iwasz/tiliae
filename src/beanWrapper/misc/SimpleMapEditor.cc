/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SimpleMapEditor.h"
#include "../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../core/Typedefs.h"
#include "../core/variant/Cast.h"
#include "../common/collection/OrderedVariantMap.h"

namespace Editor {
using namespace Core;

IEditor *SimpleMapEditor::getEditor (const std::string& name) const
{
        EditorMap::const_iterator i = editors.find (name);
        return (i == editors.end ()) ? (NULL) : (i->second);
}

/****************************************************************************/

bool SimpleMapEditor::edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        assert (beanWrapper);

        const Common::OrderedVariantMap *inputMap = vcast <const Common::OrderedVariantMap *> (input);

        for (Common::OrderedVariantMap::const_iterator i = inputMap->begin (); i != inputMap->end (); ++i) {

                IEditor *editor = NULL;

# if 0
               std::cerr << vcast <std::string> (p.first) << std::endl;
#endif

               EditorMap::iterator ed = editors.find (i->first);

               if (ed != editors.end ()) {
                       editor = ed->second;
               }
               else if (defaultEditor) {
                       editor = defaultEditor;
               }
                else {
                        continue;
                }

                Variant outputV;
                assert (editor);

                if (!editor->convert (i->second, &outputV, context)) {
                        dcError (context, "SimpleMapEditor : editor failed [" + i->first + "].")
                        return false;
                }

                Variant v = *output;
                if (!beanWrapper->set (&v, i->first, outputV, context)) {
                        dcError (context, "SimpleMapEditor : beanWrapper set failed [" + i->first + "].")
                        return false;
                }
        }

        return true;
}

}
