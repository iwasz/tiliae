/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "core/variant/Cast.h"
#include "reflection/annotations/AnnotationManager.h"
#include <vector>
#include "reflection/reflectAnnotations/CollectionAnnotation.h"

BOOST_AUTO_TEST_SUITE (AnnotationTest);

using namespace boost;
using namespace Core;

/**
 * Klasa testujaca mechanizmy okolo klasy Class.
 */
BOOST_AUTO_TEST_CASE (testNumberOfAnnotations)
{
        int noOfAnnotations = Annotations::AnnotationManager::instance ().getAnnotationList ().size ();
        BOOST_REQUIRE (noOfAnnotations > 0);
}

BOOST_AUTO_TEST_SUITE_END ();
