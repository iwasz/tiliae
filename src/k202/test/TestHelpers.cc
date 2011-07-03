/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TestHelpers.h"
#include "../compiler/Compiler.h"
#include "ByteCode.h"

using namespace k202;

void TestHelpers::testParser (Ptr <Compiler> compiler, const std::string &src, const std::string &expected)
{
        Ptr <ByteCode> script = compiler->compile (src, NULL);
        std::string result = script->toString ();
        std::string cut = result;
        cut = ((result.size () > 100) ? (cut.resize (100), cut + "...") : (result));

        if (result != expected || expected.empty ()) {
                std::cerr << "ERR " << src << " -> " << result << std::endl;
        }

        if (!expected.empty ()) {
                assert (result == expected);
                std::cerr << "OK " << src << " -> " << cut << std::endl;
        }
}
