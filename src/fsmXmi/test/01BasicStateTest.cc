/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE FsmXmiTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "XmlTextReader.h"
#include "XmlException.h"
#include "../XmiParser.h"

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (XMI01);
using namespace Xml;
using namespace Core;
using namespace FsmXmi;

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testBasic)
{
        XmiParser parser;
        parser.parse ("../src/fsmXmi/test/testXmlFiles/001-simplest.uml");
}

BOOST_AUTO_TEST_SUITE_END ();
