/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BFMapEditor.h"
#include "beanWrapper/beanWrapper/BeanWrapper.h"
#include "core/Typedefs.h"
#include "core/variant/Cast.h"
#include "common/collection/OrderedVariantMap.h"

namespace Container {
using namespace Core;

bool BFMapEditor::edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        assert (beanWrapper);

        const Common::OrderedVariantMap *inputMap = vcast <const Common::OrderedVariantMap *> (input);
        bool success;

        assert (elements.size () == inputMap->size ());

        int cnt = 0;
        for (Common::OrderedVariantMap::const_iterator i = inputMap->begin (); i != inputMap->end (); ++i, ++cnt) {

                // Każdemu DataKey odpowiada jeden element.
                Element &element = elements[cnt];

                Variant outputV;
                if (!useElement (&element, i->second, &outputV, context)) {
                        dcError (context, "BFMapEditor : element failed [" + i->first + "].")
                        return false;
                }

                if (element.add) {
                        success = beanWrapper->add (output, i->first, outputV, context);
                }
                else {
                        success = beanWrapper->set (output, i->first, outputV, context);
                }

                if (!success) {
                        dcError (context, "BFMapEditor : beanWrapper set failed [" + i->first + "].")
                        return false;
                }
        }

        return true;
}

/****************************************************************************/

bool BFMapEditor::useElement (Element *element, const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        switch (element->type) {
        case Element::BEAN_FACTORY:
                *output = element->factory->create (Core::VariantMap (), context);

                if (output->isNone ()) {
                        return false;
                }

                break;

        case Element::EDITOR_FROM_BF:
                return element->editor->convert (input, output, context);

        case Element::EXTERNAL_SINGLETON:
                *output = element->singleton;
                break;

        case Element::EMPTY:
        default:
                *output = input;
                break;

        }

        return true;
}

/****************************************************************************/

//Element *BFMapEditor::getElement (const std::string& name)
//{
//        ElementMap::iterator i = elements.find (name);
//        return (i == elements.end () ? (NULL) : (&i->second));
//}


}
