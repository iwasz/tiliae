/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <Pointer.h>
#include <TestHelpers.h>

#include "ContainerFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"

/****************************************************************************/

using namespace Container;
using namespace Core;
using namespace Editor;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (ContainerTest04);

/**
 * Test parametrw do konstruktora.
 */
BOOST_AUTO_TEST_CASE (testCreateOneSimpleWithCArgs)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure15 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 1);

/****************************************************************************/

        BeanFactory *bf = cont->getBeanFactory ("mojBean");
        BOOST_CHECK (bf);

        Core::VariantList const *vl = bf->getCArgs ();

        BOOST_CHECK (!vl->empty ());
        BOOST_CHECK (vl->size () == 7);

        VariantList::const_iterator i = vl->begin ();
        BOOST_CHECK (vcast <String> (*i++) == "value2");
        BOOST_CHECK (vcast <std::string> (*i++) == "value3");
        BOOST_CHECK (vcast <int> (*i++) == 6667);
        BOOST_CHECK (vcast <double> (*i++) == 123.45);
        BOOST_CHECK (vcast <char> (*i++) == 'f');
        BOOST_CHECK (vcast <bool> (*i++) == true);
        BOOST_CHECK ((*i++).isNull ());

        IEditor *cargsEditor = bf->getCArgsEditor ();
        BOOST_CHECK (cargsEditor);

/****************************************************************************/

        Variant v;

        try {
                v = cont->getBean ("mojBean");
        }
        catch (Core::Exception const &e) {
                std::cerr << e.getMessage () << std::endl;
        }

        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK_EQUAL (foo->getField0 (), "value2");
        BOOST_CHECK_EQUAL (foo->getField1 (), "value3");
        BOOST_CHECK_EQUAL (foo->getField2 (), 6667);
        BOOST_CHECK_EQUAL (foo->getField3 (), 123.45);
        BOOST_CHECK_EQUAL (foo->getField4 (), 'f');
        BOOST_CHECK_EQUAL (foo->getField5 (), true);
        BOOST_CHECK (!foo->getField6 ());
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateOneSimpleWithCArgsAndRef)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure16 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        BOOST_CHECK (cont->getBeanFactoryMap ().size () == 2);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Bar *> (v));

        Bar *foo = vcast <Bar *> (v);

        BOOST_CHECK (foo->getField0 () == "value2");
        BOOST_CHECK (foo->getField1 () == "value3");

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Warszawa");
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testCreateBeanWithReferenceDoubleIter)
{
       Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure17 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        Variant v = cont->getBean ("mojBean");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <Foo *> (v));

        Foo *foo = vcast <Foo *> (v);

        BOOST_CHECK (foo->getField0 () == "value0");
        BOOST_CHECK (foo->getField1 () == "value1");
        BOOST_CHECK (foo->getField2 () == 6667);
        BOOST_CHECK (foo->getField3 () == 123.45);
        BOOST_CHECK (foo->getField4 () == 'f');
        BOOST_CHECK (foo->getField5 () == true);
        BOOST_CHECK (!foo->getField6 ());

/****************************************************************************/

        BOOST_CHECK (foo->getCity ());
        BOOST_CHECK (foo->getCity ()->getName () == "Warszawa");
}

/**
 * Tworzymy mape, ktora zawera referencje do 3 beanow typu Conuntry,
 * przy czym testujemy podwójną iterację, bo beany do których jest
 * referencja występują po beanie z mapą, więc referencje będą uzupełnione
 * dopiero przy drugiej referencji.
 */
BOOST_AUTO_TEST_CASE (testCreateMapWithReferenceDoubleIter)
{
        Ptr <MetaContainer> metaCont = ContainerTestFactory::createMetaStructure18 ();
        Ptr <BeanFactoryContainer> cont = ContainerFactory::createAndInit (metaCont);

/****************************************************************************/

        City cit;
        City *cit0 = &cit;
        Variant v1 = Core::Variant (cit0);
        BOOST_CHECK (!v1.isNone ());
        BOOST_CHECK (ccast <City *> (v1));
        BOOST_CHECK (ccast <City const *> (v1));


        Variant v = cont->getBean ("ncity1");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <City *> (v));
        BOOST_CHECK (ccast <City const *> (v));

        v = cont->getBean ("mojaMapka");
        BOOST_CHECK (!v.isNone ());
        BOOST_CHECK (ccast <CityMap *> (v));

        CityMap *map = vcast <CityMap *> (v);

        BOOST_CHECK (map->size () == 3);
        BOOST_CHECK (map->find ("field0") != map->end ());
        BOOST_CHECK (map->find ("field1") != map->end ());
        BOOST_CHECK (map->find ("field2") != map->end ());

        BOOST_CHECK (map->operator[] ("field0")->getName () == "Warszawa");
        BOOST_CHECK (map->operator[] ("field1")->getName () == "Krakow");
        BOOST_CHECK (map->operator[] ("field2")->getName () == "Piaseczno");
}

BOOST_AUTO_TEST_SUITE_END ();
