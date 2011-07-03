/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <beanWrapper/BeanWrapper.h>
#include "MappedEditor.h"

using namespace Core;

namespace Editor {

/**
 *
 */
void MappedEditor::convert (const Core::Variant &input,
                            const Core::String &inputPath,
                            Core::Variant *output,
                            const Core::String &outputPath)
{
        ASSERT (output, "");
        ASSERT (mapping, "mapping not set");
        ASSERT (in, "");
        ASSERT (out, "");

        in->setWrappedObject (input);
        out->setWrappedObject (*output);

        IEditor *editor = mapping->getEditor (inputPath);
        ASSERT (editor, "");

//        PathPair outputPaths = mapping->getOutputPath (inputPath);
//        ASSERT (!outputPaths.first.empty (), "");
//
//        if (outputPaths.second.empty ()) {

                Variant tmp = out->get (outputPath);
                editor->convert (in->get (inputPath), &tmp);

                /*
                 * Tu nie ma narzutu przy ponownym ustawianiu tego warianta
                 * do BeanWrappera, poniewaz tmp zazwyczaj przechowuje handle,
                 * czyli jakis wskaznik, a jesli nawet nie, to i tak trzeba
                 * by bylo go ustawic (chodzi mi o to, ze ta linia ponizej
                 * jest nadmiarowa tylko dla variantow typu handle, ale set
                 * dla takich wariantow jest szybkie, bo nie ma kopiowania).
                 */
                out->set (outputPath, tmp);
//        }
//        else {
//
//        }
}

/**
 * Mamy gwarancje ze input i outpu sa OK. Odpowiednie asercje
 * wykonuje nadklasa.
 */
void MappedEditor::edit (const Core::Variant &input, Core::Variant *output, Common::Context *context)
{
        ASSERT (output, "");
        ASSERT (mapping, "");

        Mapping::ListPair paths = mapping->getInputOutputPaths ();

        StringList::const_iterator inputIter = paths.first.begin ();
        StringList::const_iterator outputIter = paths.second.begin ();

        for (; inputIter != paths.first.end (); inputIter++, outputIter++) {

                String inputPath = *inputIter;
                String outputPath = *outputIter;

                convert (input, inputPath, output, outputPath);
        }
}

}
