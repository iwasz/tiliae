/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE ReflectionTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <iostream>
#include "core/Exception.h"

using namespace ::boost::unit_test;

void translate_mfc_exception (std::exception* pMfcEx)
{
        BOOST_ERROR ("Core::Exception here");
}

// Hmm to nie działa... http://stackoverflow.com/questions/2358282/boost-test-register-exception-translator
test_suite* init_unit_test_suite (int argc, char* argv[])
{
        std::cerr << "init_unit_test_suite" << std:: endl;
        // Initialize global Handlers:
        unit_test_monitor.register_exception_translator<std::exception *> (&translate_mfc_exception);

        // Return dummy suite to make framework happy:
        test_suite* test = BOOST_TEST_SUITE( "Empty Test Suite" );
        return test;
}
