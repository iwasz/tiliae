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

                Element element;
                ElementMap::iterator ed = elements.find (i->first);

                if (ed != elements.end ()) {
                       element = ed->second;
                }

                Variant outputV;
                if (!useElement (&element, i->second, &outputV, context)) {
                        dcError (context, "BFMapEditor : element failed [" + i->first + "].")
                        return false;
                }

                if (!beanWrapper->set (output, i->first, outputV, context)) {
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
                break;

        case Element::EDITOR_FROM_BF:
        {
                Core::Variant vEd = element->factory->create (Core::VariantMap (), context);

                if (!occast <IEditor *> (vEd)) {
                        dcError (context, "LazyEditor::convert !occast <Ptr <IEditor> > (vEd). vEd : " + vEd.toString ());
                        return false;
                }

                IEditor *ed = ocast <IEditor *> (vEd);
                return ed->convert (input, output, context);
        }
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

Element *BFMapEditor::getElement (const std::string& name)
{
        ElementMap::iterator i = elements.find (name);
        return (i == elements.end () ? (NULL) : (&i->second));
}


}
