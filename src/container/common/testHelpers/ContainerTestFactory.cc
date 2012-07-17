/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ContainerTestFactory.h"
#include "metaStructure/model/MetaStructure.h"
#include "ContainerFactory.h"
#include "beanFactory/BeanFactory.h"
#include <boost/make_shared.hpp>
#include "../../inputFormat/mxml/MXmlMetaService.h"

using namespace Container;
using namespace Core;

/****************************************************************************/

Container::ContainerFactory ContainerTestFactory::cf;
Ptr <Container::BeanFactoryContainer> ContainerTestFactory::container;

/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerTestFactory::getContainer (const std::string &xmlFilePath)
{
        return ContainerFactory::createAndInit (MXmlMetaService::parseFile (xmlFilePath));
}

/*
 * TODO Zrobić test kiedy parent jest Mapped, a child Indexed etc.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure01 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *parent = new MetaObject ();

        parent->addMapField (DataKey ("field1", new ValueData ("value1", "String")));
        parent->addMapField (DataKey ("field2", new ValueData ("value2", "String")));

        parent->setId ("ojciec");
        parent->setAbstract (true);
        parent->setLazyInit (true);

        parent->addConstructorArg (new ValueData ("carg1", "String"));
        parent->addConstructorArg (new ValueData ("carg2", "String"));

        metaCont->add (parent);

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addMapField (DataKey ("field3", new ValueData ("value3", "String")));
        child->addMapField (DataKey ("field4", new ValueData ("value4", "String")));

        child->setId ("syn");
        child->setParent ("ojciec");

        metaCont->add (child);

        return metaCont;
}

/****************************************************************************/

Ptr <MetaContainer> ContainerTestFactory::createMetaStructure02 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *parent = new MetaObject ();
        parent->setId ("ojciec");
        parent->setAbstract (true);
        metaCont->add (parent);

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();
        child->setId ("syn");
        child->setParent ("ojciec");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = new MetaObject ();
        meta->setId ("aska");
        metaCont->add (meta);

        MetaObject *meta1 = new MetaObject ();
        meta1->setId ("aska2");
        metaCont->add (meta1);

        MetaObject *meta2 = new MetaObject ();
        meta2->setId ("aska3");
        metaCont->add (meta2);

        return metaCont;
}

/****************************************************************************/

Ptr <MetaContainer> ContainerTestFactory::createMetaStructure03 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addMapField (DataKey ("field0", new ValueData ("value0", "String")));
        child->addMapField (DataKey ("field1", new ValueData ("value1", "text")));
        child->addMapField (DataKey ("field2", new ValueData ("6667", "int")));
        child->addMapField (DataKey ("field3", new ValueData ("123.45", "double")));
        child->addMapField (DataKey ("field4", new ValueData ("f", "char")));
        child->addMapField (DataKey ("field5", new ValueData ("true", "bool")));
        child->addMapField (DataKey ("field6", new NullData ()));

        child->setId ("syn");

        metaCont->add (child);

        return metaCont;
}

/****************************************************************************/

Ptr <MetaContainer> ContainerTestFactory::createMetaStructure04 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addListField (new ValueData ("value0", "String"));
        child->addListField (new ValueData ("value1", "text"));
        child->addListField (new ValueData ("6667", "int"));
        child->addListField (new ValueData ("123.45", "double"));
        child->addListField (new ValueData ("f", "char"));
        child->addListField (new ValueData ("true", "bool"));
        child->addListField (new NullData ());

        child->setId ("syn");

        metaCont->add (child);

        return metaCont;
}

/**
 * Tworzy metastrukturę zawierającą same MappedMeta, ale mamy tu dziedziczenie,
 * wartości i referencje.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure05 ()
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

        MetaObject *meta00 = new MetaObject ();
        meta00->setId ("askaParent");
        meta00->setClass ("City");
        meta00->addMapField (DataKey ("name", new ValueData ("value00", "String")));
        metaCont->add (meta00);

        MetaObject *meta0 = new MetaObject ();
        meta0->setId ("aska0");
        meta0->addMapField (DataKey ("name", new ValueData ("value0", "String")));
        meta0->setParent ("askaParent");
        metaCont->add (meta0);

        MetaObject *meta = new MetaObject ();
        meta->setId ("aska");
        meta->setClass ("Note");
        meta->addMapField (DataKey ("title", new ValueData ("value11", "String")));
        meta->addMapField (DataKey ("body", new ValueData ("value11", "String")));
        metaCont->add (meta);

        MetaObject *meta1 = new MetaObject ();
        meta1->setId ("aska2");
        meta1->setClass ("Country");
        meta1->addMapField (DataKey ("name", new ValueData ("value22", "String")));
        metaCont->add (meta1);

        MetaObject *meta2 = new MetaObject ();
        meta2->setId ("aska3");
        meta2->setClass ("Address");
        meta2->addMapField (DataKey ("street", new ValueData ("value33", "String")));
        metaCont->add (meta2);

        return metaCont;
}

/****************************************************************************/

Ptr <MetaContainer> ContainerTestFactory::createMetaStructure06 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addListField (new ValueData ("value0", "String"));
        child->addListField (new ValueData ("value1", "text"));
        child->addListField (new ValueData ("6667", "int"));
        child->addListField (new ValueData ("123.45", "double"));
        child->addListField (new ValueData ("f", "char"));
        child->addListField (new ValueData ("true", "bool"));
        child->addListField (new NullData ());

        child->setId ("syn");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = new MetaObject ();

        child->addListField (new ValueData ("value0", "String"));
        child->addListField (new RefData ("syn"));

        child->setId ("ociec");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = new MetaObject ();

        child->addListField (new ValueData ("value0", "String"));
        child->addListField (new RefData ("ociec"));

        child->setId ("dziadzio");
        metaCont->add (child);

        return metaCont;
}

/**
 *
 * @return
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure07 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addMapField (DataKey ("field0", new ValueData ("value0", "String")));
        child->addMapField (DataKey ("field1", new ValueData ("value1", "text")));
        child->addMapField (DataKey ("field2", new ValueData ("6667", "int")));
        child->addMapField (DataKey ("field3", new ValueData ("123.45", "double")));
        child->addMapField (DataKey ("field4", new ValueData ("f", "char")));
        child->addMapField (DataKey ("field5", new ValueData ("true", "bool")));
        child->addMapField (DataKey ("field6", new NullData ()));

        child->setId ("mojBean");
        child->setClass ("Foo");
        child->setScope (MetaObject::PROTOTYPE);

        metaCont->add (child);

        return metaCont;
}

/**
 *
 * @return
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure08 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = createMetaStructure07 ();

        /*
         * Modyfikujemy bean mojBean stworzony w metodzie createMetaStructure07
         */

        MetaObject *m = metaCont->get ("mojBean");
        MetaObject *meta = dynamic_cast <MetaObject *> (m);
        meta->addMapField (DataKey ("city", new RefData ("city")));

        /*
         * Tworzymy ten city, który jest używany przez mojBean
         */

        MetaObject *child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        child->setId ("city");
        child->setClass ("City");
        metaCont->add (child);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą mapę typu StringMap.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure09 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addMapField (DataKey ("field0", new ValueData ("value0", "String")));
        child->addMapField (DataKey ("field1", new ValueData ("value1", "text")));
        child->addMapField (DataKey ("field2", new ValueData ("value2", "text")));
        child->addMapField (DataKey ("field3", new ValueData ("value3", "text")));

        child->setId ("mojaMapa");
        child->setClass ("StringMap");

        metaCont->add (child);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą mapę typu VariantMap.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure10 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addMapField (DataKey ("field0", new ValueData ("value0", "String")));
        child->addMapField (DataKey ("field1", new ValueData ("value1", "text")));
        child->addMapField (DataKey ("field2", new ValueData ("6667", "int")));
        child->addMapField (DataKey ("field3", new ValueData ("123.45", "double")));
        child->addMapField (DataKey ("field4", new ValueData ("f", "char")));
        child->addMapField (DataKey ("field5", new ValueData ("true", "bool")));
        child->addMapField (DataKey ("field6", new NullData ()));

        child->setId ("mojaMapa");
        child->setClass ("VariantMap");

        metaCont->add (child);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą listę StringList.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure11 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addListField (new ValueData ("value0", "String"));
        child->addListField (new ValueData ("value1", "String"));
        child->addListField (new ValueData ("value2", "String"));
        child->addListField (new ValueData ("value3", "String"));
        child->addListField (new ValueData ("value4", "String"));

        child->setId ("mojaLista");
        child->setClass ("StringList");

        metaCont->add (child);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą listę VariantList.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure12 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addListField (new ValueData ("value0", "String"));
        child->addListField (new ValueData ("value1", "text"));
        child->addListField (new ValueData ("6665", "int"));
        child->addListField (new ValueData ("123.45", "double"));
        child->addListField (new ValueData ("f", "char"));
        child->addListField (new ValueData ("true", "bool"));
        child->addListField (new NullData ());

        child->setId ("mojaLista");
        child->setClass ("VariantList");

        metaCont->add (child);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą listę CountryList.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure13 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Polska", "String")));
        child->setId ("country1");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Jamajka", "String")));
        child->setId ("country2");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Wolny Tybet", "String")));
        child->setId ("country3");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = new MetaObject ();
        meta->addListField (new RefData ("country1"));
        meta->addListField (new RefData ("country2"));
        meta->addListField (new RefData ("country3"));
        meta->setId ("mojaLista");
        meta->setClass ("CountryVector");

        metaCont->add (meta);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą listę CountryMap (czyli klucze String, wartosci Country *).
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure14 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        child->setId ("city1");
        child->setClass ("City");
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Krakow", "String")));
        child->setId ("city2");
        child->setClass ("City");
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Piaseczno", "String")));
        child->setId ("city3");
        child->setClass ("City");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = new MetaObject ();
        meta->addMapField (DataKey ("field0", new RefData ("city1")));
        meta->addMapField (DataKey ("field1", new RefData ("city2")));
        meta->addMapField (DataKey ("field2", new RefData ("city3")));
        meta->setId ("mojaMapka");
        meta->setClass ("CityMap");

        metaCont->add (meta);

        return metaCont;
}

/**
 *
 * @return
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure15 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addConstructorArg (new ValueData ("value2", "String"));
        child->addConstructorArg (new ValueData ("value3", "text"));
        child->addConstructorArg (new ValueData ("6667", "int"));
        child->addConstructorArg (new ValueData ("123.45", "double"));
        child->addConstructorArg (new ValueData ("f", "char"));
        child->addConstructorArg (new ValueData ("true", "bool"));
        child->addConstructorArg (new NullData ());

        child->setId ("mojBean");
        child->setClass ("Bar");

        metaCont->add (child);

        return metaCont;
}

/**
 *
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure16 ()
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addConstructorArg (new ValueData ("value2", "String"));
        child->addConstructorArg (new ValueData ("value3", "text"));
        child->addConstructorArg (new RefData ("city"));
        child->setId ("mojBean");
        child->setClass ("Bar");
        child->setScope (MetaObject::PROTOTYPE);

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *child1 = new MetaObject ();
        child1->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        child1->setId ("city");
        child1->setClass ("City");
        child1->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child1);

        return metaCont;
}

/**
 *
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure17 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = createMetaStructure07 ();

        /*
         * Modyfikujemy bean mojBean stworzony w metodzie createMetaStructure07
         */

        MetaObject *m = metaCont->get ("mojBean");
        MetaObject *meta = dynamic_cast <MetaObject *> (m);
        meta->addMapField (DataKey ("city", new RefData ("ncity")));

        /*
         * Tworzymy ten city, który jest używany przez mojBean
         */

        MetaObject *child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));

        /*
         * Id ma pierwsząliterę "n", czyli będzie w mapie (w metaStrukturze) PO mojBean.
         * To jest ustrudnienie dla kontenera, który będzie musiał przeiterować 2 razy,
         * żeby uzupełnić zależności pomiędzy beanami.
         */
        child->setId ("ncity");
        child->setClass ("City");
        metaCont->add (child);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą listę CountryMap. Skopiowane
 * z createMetaStructure14. Zmienione nazwy beanów, tak, że beany
 * do których są referencje w mapie, występują po definicji samej
 * mapy.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure18 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        child->setId ("ncity1");
        child->setClass ("City");
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Krakow", "String")));
        child->setId ("ncity2");
        child->setClass ("City");
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Piaseczno", "String")));
        child->setId ("ncity3");
        child->setClass ("City");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = new MetaObject ();
        meta->addMapField (DataKey ("field0", new RefData ("ncity1")));
        meta->addMapField (DataKey ("field1", new RefData ("ncity2")));
        meta->addMapField (DataKey ("field2", new RefData ("ncity3")));
        meta->setId ("mojaMapka");
        meta->setClass ("CityMap");

        metaCont->add (meta);

        return metaCont;
}

/**
 * Tworzy metastrukturę definiującą listę CountryList.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure19 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Polska", "String")));
        child->setId ("ncountry1");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Jamajka", "String")));
        child->setId ("ncountry2");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = new MetaObject ();
        child->addMapField (DataKey ("name", new ValueData ("Wolny Tybet", "String")));
        child->setId ("ncountry3");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = new MetaObject ();
        meta->addListField (new RefData ("ncountry1"));
        meta->addListField (new RefData ("ncountry2"));
        meta->addListField (new RefData ("ncountry3"));
        meta->setId ("mojaLista");
        meta->setClass ("CountryVector");

        metaCont->add (meta);

        return metaCont;
}

/**
 * Ta metoda jest taka sama jak 16 z jednym małym wyjątkiem : ncity
 * jest zaczyna się na literę n, co powoduje, że zostanie przetworzony
 * >>>PO<<< mojBean.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure20 ()
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addConstructorArg (new ValueData ("value2", "String"));
        child->addConstructorArg (new ValueData ("value3", "text"));
        child->addConstructorArg (new RefData ("ncity"));

        child->setId ("mojBean");
        child->setClass ("Bar");

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *child1 = new MetaObject ();
        child1->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        child1->setId ("ncity");
        child1->setClass ("City");
        child1->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child1);

        return metaCont;
}

/**
 * Singleton - taki jak w 07.
 * @return
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure21 ()
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addMapField (DataKey ("field0", new ValueData ("value0", "String")));
        child->addMapField (DataKey ("field1", new ValueData ("value1", "text")));
        child->addMapField (DataKey ("field2", new ValueData ("6667", "int")));
        child->addMapField (DataKey ("field3", new ValueData ("123.45", "double")));
        child->addMapField (DataKey ("field4", new ValueData ("f", "char")));
        child->addMapField (DataKey ("field5", new ValueData ("true", "bool")));
        child->addMapField (DataKey ("field6", new NullData ()));

        child->setId ("mojBean");
        child->setClass ("Foo");
        child->setScope (MetaObject::SINGLETON);

        metaCont->add (child);

        return metaCont;
}

/**
 * Prosty bean z init method.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure22 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        child->setId ("mojBean");
        child->setClass ("City");
        child->setInitMethod ("init");

        metaCont->add (child);

        return metaCont;
}

/**
 * Test inner-outer
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure23 ()
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

        MetaObject *meta00 = new MetaObject ();
        meta00->setId ("mainBean");
        meta00->setClass ("Bar");
        meta00->addConstructorArg (new ValueData ("value2", "String"));
        meta00->addMapField (DataKey ("city4", new RefData ("city")));
        meta00->addMapField (DataKey ("city5", new RefData ("city")));
        meta00->setScope (MetaObject::PROTOTYPE);
        metaCont->add (meta00);

        MetaObject *meta0 = new MetaObject ();
        meta0->setId ("city");
        meta0->setClass ("City");
        meta0->setScope (MetaObject::BEAN);
        meta0->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        meta00->addInnerMeta (meta0);

        MetaObject *meta = new MetaObject ();
        meta->setId ("list");
        meta->setClass ("BarMap");
        meta->addMapField (DataKey ("key01", new RefData ("mainBean")));
        meta->addMapField (DataKey ("key02", new RefData ("mainBean")));
        meta->setScope (MetaObject::PROTOTYPE);
        metaCont->add (meta);

        return metaCont;
}

/**
 * Test inner-outer
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure24 ()
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*------Level0-meta-globalne------------------------------------------------*/

        MetaObject *meta00 = new MetaObject ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        metaCont->add (meta00);

/*------Level1-inner-mata-city100-------------------------------------------*/

                MetaObject *meta01 = new MetaObject ();
                meta01->setId ("city110");
                meta01->setClass ("City");
                meta01->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
                meta00->addInnerMeta (meta01);

                        // Taka sama nazwa!
                        MetaObject *meta02 = new MetaObject ();
                        meta02->setId ("cityA");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

                        meta02 = new MetaObject ();
                        meta02->setId ("cityB");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

                meta01 = new MetaObject ();
                meta01->setId ("city120");
                meta01->setClass ("City");
                meta01->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
                meta00->addInnerMeta (meta01);

/*------Level2-inner-meta-city110-i-city120---------------------------------*/

                        meta02 = new MetaObject ();
                        meta02->setId ("cityA");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

                        meta02 = new MetaObject ();
                        meta02->setId ("cityB");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

/*--------------------------------------------------------------------------*/

        meta00 = new MetaObject ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        metaCont->add (meta00);

/*--------------------------------------------------------------------------*/

                meta01 = new MetaObject ();
                meta01->setId ("city110");
                meta01->setClass ("City");
                meta00->addInnerMeta (meta01);

        return metaCont;
}

/**
 * Jeden skomplikowany meta i 2 małe.
 * @return
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure25 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();
        child->addMapField (DataKey ("field0", new ValueData ("value0", "String")));
        child->addMapField (DataKey ("field1", new ValueData ("value1", "text")));
        child->addMapField (DataKey ("field2", new ValueData ("6667", "int")));
        child->addMapField (DataKey ("field3", new ValueData ("123.45", "double")));
        child->addMapField (DataKey ("field4", new ValueData ("f", "char")));
        child->addMapField (DataKey ("field5", new ValueData ("true", "bool")));
        child->addMapField (DataKey ("field6", new NullData ()));
        child->addMapField (DataKey ("field7", new RefData ("city100")));
        child->addMapField (DataKey ("field8", new RefData ("city200")));

        child->setClass ("VariantMap");
        child->setId ("syn");

        MetaObject *meta00 = new MetaObject ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        metaCont->add (meta00);

        meta00 = new MetaObject ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        meta00->addMapField (DataKey ("name", new ValueData ("Wilno", "String")));
        metaCont->add (meta00);

        metaCont->add (child);

        return metaCont;
}
/****************************************************************************/

Ptr <MetaContainer> ContainerTestFactory::createMetaStructure26 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();

/*--------------------------------------------------------------------------*/

        MetaObject *child = new MetaObject ();

        child->addListField (new ValueData ("value0", "String"));
        child->addListField (new ValueData ("value1", "text"));
        child->addListField (new ValueData ("6667", "int"));
        child->addListField (new ValueData ("123.45", "double"));
        child->addListField (new ValueData ("f", "char"));
        child->addListField (new ValueData ("true", "bool"));
        child->addListField (new NullData ());
        child->addListField (new RefData ("city100"));
        child->addListField (new RefData ("city200"));
        child->setId ("syn");
        child->setClass ("VariantVector");
        metaCont->add (child);

        MetaObject *meta00 = new MetaObject ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addMapField (DataKey ("name", new ValueData ("Warszawa", "String")));
        metaCont->add (meta00);

        meta00 = new MetaObject ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        meta00->addMapField (DataKey ("name", new ValueData ("Wilno", "String")));
        metaCont->add (meta00);

        return metaCont;
}
