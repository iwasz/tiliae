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

Ptr <IEditor> IndexedEditor::getEditor (int index) const
{
		EditorMap::const_iterator i = editors->find (index);
		return (i == editors->end ()) ? (Ptr <IEditor> ()) : (i->second);
}

/****************************************************************************/

void IndexedEditor::edit (const Core::Variant &input, Core::Variant *output, Core::Context *context)
{
        assert (editors);
        assert (beanWrapper);

        VariantList const *inputCollection = vcast <VariantList const *> (input);
        VariantList::const_iterator in = inputCollection->begin ();

        int cnt = 0;
        for (; in != inputCollection->end (); in++, cnt++) {

                Variant v;
                Ptr <IEditor> editor;

                EditorMap::const_iterator i;
                if ((i = editors->find (cnt)) != editors->end ()) {
                        editor = i->second;
                }
                else if (defaultEditor) {
                        editor = defaultEditor;
                }
                else {
                        continue;
                }

                editor->convert (*in, &v, context);
                beanWrapper->add (output, "", v, context);
        }
}

/****************************************************************************/

void IndexedEditor::setEditors (Ptr <EditorVector> editors)
{
        assert (editors);
        assert (this->editors);
        int cnt = 0;

        for (EditorVector::iterator i = editors->begin(); i != editors->end (); ++i, ++cnt) {
                this->editors->operator [](cnt) = *i;
        }
}

}
