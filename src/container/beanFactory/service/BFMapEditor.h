/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BF_MAP_MAPEDITOR_H_
#define BF_MAP_MAPEDITOR_H_

#include <string>
#include <map>
#include "JEditor.h"
#include "IFactory.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Container {

/**
 * Odpowiednik edytora, ale nie polimorficzny.
 */
struct Element {
        enum Type { EMPTY, EXTERNAL_SINGLETON, BEAN_FACTORY, EDITOR_FROM_BF };

        Element () : type (EMPTY), factory (NULL), editor (NULL) {}

        Type type;
        Factory::IFactory *factory;
        Editor::IEditor *editor;
        Core::Variant singleton;
};

/**
 * Klucze map muszą być typu std::string.
 */
class BFMapEditor : public Editor::JEditor {
public:

        typedef std::map <std::string, Element> ElementMap;

        BFMapEditor () : /*defaultEditor (NULL),*/ beanWrapper (NULL) {}
        virtual ~BFMapEditor () {}

        virtual bool edit (const Core::Variant &input, Core::Variant *output, Core::DebugContext *context = NULL);

/*--------------------------------------------------------------------------*/

        Wrapper::BeanWrapper *getBeanWrapper () const { return beanWrapper; }
        void setBeanWrapper (Wrapper::BeanWrapper *beanWrapper) { this->beanWrapper = beanWrapper; }

        void setElement (const std::string &name, Element &e) { elements[name] = e; }
        Element *getElement (const std::string & name);

protected:

        bool useElement (Element *element, const Core::Variant &input, Core::Variant *output, Core::DebugContext *context);

private:

        ElementMap elements;
        Wrapper::BeanWrapper *beanWrapper;

};

}

#endif /* SIMPLEMAPEDITOR_H_ */
