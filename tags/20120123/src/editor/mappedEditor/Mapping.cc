/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Mapping.h"

using namespace Core;

namespace Editor {

/**
 * TODO ta implementacja ulegnie zmianie, bo
 * nie chce, zeby sie osobno ustawialo sciezki
 * jako osobne listy i do tego soobna lista
 * edytorow - to musi byc jakas mapa, a init
 * przerobi ta mape na kilka innych.
 */
//void Mapping::init ()
//{
//        ASSERT (outputPaths, "");
//        ASSERT (editors, "");
//        ASSERT (outputPaths->size () == editors->size (), "");
//
//        StringList::const_iterator outputIter = outputPaths->begin ();
//        List <IEditor *>::const_iterator editorIter = editors->begin ();
//
//        for (; outputIter != outputPaths->end (); editorIter++, outputIter++) {
//
//                String outputPath = *outputIter;
//                IEditor *editor = *editorIter;
//                ASSERT (editor, "");
//
//                editorMap[outputPath] = editor;
//        }
//}

/****************************************************************************/


PathPair Mapping::getOutputPath (const Core::String &input) const
{
        ASSERT (ruleList, "");

        /*
         * EXACT MATCH
         *
         * 1. Najpierw sprawdzamy, czy podana sicezka pasuje do jakiegos
         * rule. Jesli pasuje, zwracamy outputPath z rule.
         */
        for (RuleList::const_iterator i = ruleList->begin (); i != ruleList->end (); i++) {

                IRule *rule = *i;
                ASSERT (rule, "");

                if (!rule->supports (input)) {
                        PathPair ret;
                        ret.first = rule->getOutputPath (input);
                        return ret;
                }
        }

        /*
         * MATCH
         *
         * Zadne rule nie zrobilo exactMatch. Probujemy teraz podzielic
         * inputPath na dwie czesci za pomoca IRule::split. Pierwszy path
         * to bedzie sciezka dla glownego MappedEditor, a druga dla child.
         */
        for (RuleList::const_iterator i = ruleList->begin (); i != ruleList->end (); i++) {

                IRule *rule = *i;

                PathPair pp = rule->splitPath (input);

                if (!pp.first.empty () && rule->supports (pp.first)) {
                        return pp;
                }
        }

        return PathPair ();
}

/****************************************************************************/

IEditor *Mapping::getEditor (const Core::String &inputPath) const
{
        ASSERT (ruleList, "");
        for (RuleList::const_iterator i = ruleList->begin (); i != ruleList->end (); i++) {
                IRule *rule = *i;

                ASSERT (rule, "");

                IEditor *ed = rule->getEditor (inputPath);

                if (ed && rule->supports (inputPath)) {
                        return ed;
                }
        }

        return NULL;
}

/****************************************************************************/

Mapping::ListPair Mapping::getInputOutputPaths () const
{
        ASSERT (ruleList, "");
        Mapping::ListPair ret;

        for (RuleList::const_iterator i = ruleList->begin (); i != ruleList->end (); i++) {
                IRule *rule = *i;
                ASSERT (rule, "");
                StringList inputs = rule->getInputs ();
                ret.first.addAll (inputs);

                for (StringList::const_iterator j = inputs.begin (); j != inputs.end (); j++) {
                        String outPath = rule->getOutputPath (*j);
                        ret.second.add (outPath);
                }
        }

        ASSERT (ret.first.size () == ret.second.size (), String ("Rozmiar list nie zgadza sie. ret.first.size = ") +
                ret.first.size () + String (", a ret.second.size = ") + ret.second.size () + ".");
        return ret;
}

}
