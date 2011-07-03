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

Ptr<IEditor> SimpleMapEditor::getEditor (const std::string& name) const
{
        EditorMap::const_iterator i = editors->find (name);
        return (i == editors->end ()) ? (Ptr<IEditor> ()) : (i->second);
}

/****************************************************************************/

void SimpleMapEditor::edit (const Core::Variant &input, Core::Variant *output, Common::Context *context)
{
        assert (editors);
        assert (beanWrapper);

        const Common::OrderedVariantMap *inputMap = vcast <const Common::OrderedVariantMap *> (input);

        for (Common::OrderedVariantMap::const_iterator i = inputMap->begin (); i != inputMap->end (); ++i) {

                Ptr <IEditor> editor;

# if 0
               std::cerr << vcast <std::string> (p.first) << std::endl;
#endif

               EditorMap::iterator ed = editors->find (i->first);

               if (ed != editors->end ()) {
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
                editor->convert (i->second, &outputV, context);

//                        TODO Działa tylko jeśli się poda kopię outputu lub ustawi setWrappedObject (co też robi kopię). CZEMU?!
//                        beanWrapper->setWrappedObject (*output);
                Variant v = *output;
                beanWrapper->set (&v, i->first, outputV);
        }

}

}
