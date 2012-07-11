/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BFMapEditor.h"
#include "../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../core/Typedefs.h"
#include "../core/variant/Cast.h"
#include "../common/collection/OrderedVariantMap.h"

namespace Container {
using namespace Core;

bool BFMapEditor::edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        assert (beanWrapper);

        const Common::OrderedVariantMap *inputMap = vcast <const Common::OrderedVariantMap *> (input);

        for (Common::OrderedVariantMap::const_iterator i = inputMap->begin (); i != inputMap->end (); ++i) {

                Element *element = NULL;

# if 0
               std::cerr << vcast <std::string> (p.first) << std::endl;
#endif

               ElementMap::iterator ed = elements.find (i->first);

               if (ed != elements.end ()) {
                       element = ed->second;
               }
               else if (defaultEditor) {
                       element = defaultEditor;
               }
                else {
                        continue;
                }

                Variant outputV;
                assert (element);

                if (!element->convert (i->second, &outputV, context)) {
                        dcError (context, "BFMapEditor : element failed [" + i->first + "].")
                        return false;
                }

                Variant v = *output;
                if (!beanWrapper->set (&v, i->first, outputV, context)) {
                        dcError (context, "BFMapEditor : beanWrapper set failed [" + i->first + "].")
                        return false;
                }
        }

        return true;
}

/****************************************************************************/

Element *BFMapEditor::getEditor (const std::string& name)
{
        ElementMap::const_iterator i = elements.find (name);
        return (i == elements.end ()) ? (NULL) : (i->second);
}


}
