/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BFIndexedEditor.h"
#include <cassert>
#include "core/Typedefs.h"
#include "core/variant/Cast.h"
#include "container/common/Exceptions.h"
#include "reflection/Manager.h"
#include "reflection/model/Method.h"
#include "reflection/model/Class.h"
#include "beanWrapper/beanWrapper/BeanWrapper.h"

namespace Container {
using namespace Core;
using namespace Reflection;

/****************************************************************************/

bool BFIndexedEditor::edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context)
{
        assert (getBeanWrapper ());

        VariantList const *inputCollection = vcast <VariantList const *> (input);
        VariantList::const_iterator in = inputCollection->begin ();

        int cnt = 0;
        for (; in != inputCollection->end (); in++, cnt++) {

                Element element;
                ElementMap::iterator ed = elements.find (cnt);

                if (ed != elements.end ()) {
                       element = ed->second;
                }

                Variant outputV;
                if (!useElement (&element, *in, &outputV, context)) {
                        dcError (context, std::string ("BFIndexedEditor failed. cnt = ") + boost::lexical_cast <std::string> (cnt));
                        return false;
                }

                if (!getBeanWrapper ()->add (output, "", outputV, context)) {
                        dcError (context, std::string ("BFIndexedEditor failed (beanWrapper->add failed). cnt = ") + boost::lexical_cast <std::string> (cnt));
                        return false;
                }
        }

        return true;
}

}
