/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "IndexedEditor.h"
#include <cassert>
#include "../core/Typedefs.h"
#include "../core/variant/Cast.h"
#include "../container/common/Exceptions.h"
#include "../reflection/Manager.h"
#include "../reflection/model/Method.h"
#include "../reflection/model/Class.h"
#include "../beanWrapper/beanWrapper/BeanWrapper.h"

using Container::ContainerException;

namespace Editor {
using namespace Core;
using namespace Reflection;

IEditor *IndexedEditor::getEditor (int index)
{
		EditorMap::const_iterator i = editors.find (index);
		return (i == editors.end ()) ? (NULL) : (i->second);
}

/****************************************************************************/

bool IndexedEditor::edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        assert (beanWrapper);

        VariantList const *inputCollection = vcast <VariantList const *> (input);
        VariantList::const_iterator in = inputCollection->begin ();

        int cnt = 0;
        for (; in != inputCollection->end (); in++, cnt++) {

                Variant v;
                IEditor *editor = NULL;

                EditorMap::const_iterator i;
                if ((i = editors.find (cnt)) != editors.end ()) {
                        editor = i->second;
                }
                else if (defaultEditor) {
                        editor = defaultEditor;
                }
                else {
                        continue;
                }

                if (!editor->convert (*in, &v, context)) {
                        dcError (context, std::string ("IndexedEditor failed. cnt = ") + boost::lexical_cast <std::string> (cnt));
                        return false;
                }

                if (!beanWrapper->add (output, "", v, context)) {
                        dcError (context, std::string ("IndexedEditor failed (beanWrapper->add failed). cnt = ") + boost::lexical_cast <std::string> (cnt));
                        return false;
                }
        }

        return true;
}

/****************************************************************************/

void IndexedEditor::setEditors (EditorVector const &editors)
{
        int cnt = 0;

        for (EditorVector::const_iterator i = editors.begin(); i != editors.end (); ++i, ++cnt) {
                this->editors[cnt] = *i;
        }
}

}
