/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAPPEDEDITOR_H_
#define MAPPEDEDITOR_H_

#include "Mapping.h"
#include "IRule.h"
#include "SimpleRule.h"
#include "IndexRule.h"
#include "JEditor.h"

namespace Wrapper {
class BeanWrapper;
}

namespace Editor {

/**
 * To jest klasa edytorów, które swój parametr wejściowy (podlegający
 * konwersji) traktują jako coś co jest podzielone na pary klucz-wartość.
 *
 * Taki edytor może działać na dwa sposoby. Może a) konwertować cały swój
 * obiekt wejściowy, albo b) tylko jakiś jego podobiekt (wtedy podajemy
 * ścieżkę do tego podobiektu).
 *
 * b)
 * Podenej ścieżce wejściowej towarzyszy (w Mapper) ścieżka (1 lub więcej)
 * wyjściowa oraz kolejny edytor.
 *
 * Za pomocą BeanWrapperów wyciągamy podobiekt wejściowy i podobiekt wyjścowy
 * i konwertujemy je za pomocą wspomnianego edytora.
 *
 * a)
 * Iterujemy po wszystkich pozycjach Mapper'a (musi się jakoś dać) wykonując
 * podpunkt b).
 *
 * TODO ad. do punktu a). Jesli podamy jakieś dziwne mapowanie do mappera -
 * mapowanie, ktorego nie da sie wyciagnac z BeanWrappera, to co ma sie stac?
 * Chyba nic, czyli nie zglaszamy bledu.
 * TODO To powinien byc JEditor.
 */
struct MappedEditor : public JEditor {

        MappedEditor () : mapping (NULL), in (NULL), out (NULL) {}
        virtual ~MappedEditor () {}

        /**
         * Ta metoda sila rzeczy musi konwertowac caly obiekt (wszystkie sciezki).
         */
        virtual void edit (const Core::Variant &input, Core::Variant *output, Core::Context *context = NULL);

        /**
         * To jest wariant metody konvert, ktorej podajemy sciezke in i sciezke
         * out. Ścieżka out jest opcjonalna.
         */
        virtual void convert (const Core::Variant &input,
                                       const Core::String &inputPath,
                                       Core::Variant *output,
                                       const Core::String &outputPath);

        Mapping *getMapping() const { return mapping; }
        void setMapping(Mapping *mapping) { this->mapping = mapping; }

        Wrapper::BeanWrapper *getIn() const { return in; }
        void setIn(Wrapper::BeanWrapper *in) { this->in = in; }

        Wrapper::BeanWrapper *getOut() const { return out; }
        void setOut(Wrapper::BeanWrapper *out) { this->out = out; }

private:

        Mapping *mapping;
        Wrapper::BeanWrapper *in;
        Wrapper::BeanWrapper *out;

};

}

#endif /* MAPPEDEDITOR_H_ */
