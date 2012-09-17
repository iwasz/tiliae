/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TESTHELPERS_H_
#define TESTHELPERS_H_

#include <cassert>
#include <iostream>
#include "K202.h"
#include "core/Pointer.h"
#include "core/string/String.h"
#include "core/variant/Variant.h"
#include "core/variant/Cast.h"
#include "core/Typedefs.h"

namespace k202 {
class Compiler;
}

struct TestHelpers {

        /**
         * Testuje kompilacje kodu źródłowego do kodu wynikowego ByteCode.
         */
        static void testParser (Ptr <k202::Compiler> compiler, const std::string &src, const std::string &expected = std::string ());

};

template <typename T>
struct TestRuntime {

        static void test (Ptr <k202::K202> k202,
                          const std::string &src,
                          const T &expected,
                          const Core::Variant &domain = Core::Variant (),
                          const Core::VariantVector &paramList = Core::VariantVector (),
                          const Core::VariantMap &argsMap = Core::VariantMap ());

};

template <typename T>
void TestRuntime<T>::test (Ptr <k202::K202> k202,
                const std::string &src,
                const T &expected,
                const Core::Variant &domain,
                const Core::VariantVector &paramList,
                const Core::VariantMap &argsMap)
{
        Core::Variant ret;
        ret = k202->run (src, domain, paramList, argsMap);
        assert (ccast <T> (ret));
        assert (vcast <T> (ret) == expected);
        std::cerr << "OK " << src << std::endl;
}

#endif /* TESTHELPERS_H_ */
