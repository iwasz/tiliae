/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE StateMachineTest
#define BOOST_TEST_DYN_LINK
 
#include <boost/test/unit_test.hpp>
 
BOOST_AUTO_TEST_SUITE (FirstTest);
 
BOOST_AUTO_TEST_CASE (testBasic)
{
        BOOST_CHECK (true);
}
 
BOOST_AUTO_TEST_SUITE_END ();
