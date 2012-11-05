/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ContainerTestFactory.h"
#include "container/metaStructure/model/MetaStructure.h"
#include "container/ContainerFactory.h"
#include "container/beanFactory/BeanFactory.h"
#include <boost/make_shared.hpp>
#include "container/inputFormat/mxml/MXmlMetaService.h"

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

Ptr <MetaContainer> ContainerTestFactory::createMetaStructure01 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *parent = factory.newMetaObject ();

        parent->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "String")));
        parent->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("value2", "String")));

        parent->setId ("ojciec");
        parent->setAbstract (true);
        parent->setLazyInit (true);

        parent->addConstructorArg (factory.newValueDataNewString ("carg1", "String"));
        parent->addConstructorArg (factory.newValueDataNewString ("carg2", "String"));

        metaCont->add (parent);

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("value3", "String")));
        child->addMapField (factory.newDataKeyNewString ("field4", factory.newValueDataNewString ("value4", "String")));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *parent = factory.newMetaObject ();
        parent->setId ("ojciec");
        parent->setAbstract (true);
        metaCont->add (parent);

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();
        child->setId ("syn");
        child->setParent ("ojciec");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("aska");
        metaCont->add (meta);

        MetaObject *meta1 = factory.newMetaObject ();
        meta1->setId ("aska2");
        metaCont->add (meta1);

        MetaObject *meta2 = factory.newMetaObject ();
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("field0", factory.newValueDataNewString ("value0", "String")));
        child->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "text")));
        child->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("6667", "int")));
        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("123.45", "double")));
        child->addMapField (factory.newDataKeyNewString ("field4", factory.newValueDataNewString ("f", "char")));
        child->addMapField (factory.newDataKeyNewString ("field5", factory.newValueDataNewString ("true", "bool")));
        child->addMapField (factory.newDataKeyNewString ("field6", factory.newNullData ()));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value1", "text")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("6667", "int")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("123.45", "double")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("f", "char")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("true", "bool")));
        child->addListField (factory.newDataKey (factory.newNullData ()));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta00 = factory.newMetaObject ();
        meta00->setId ("askaParent");
        meta00->setClass ("City");
        meta00->setScope (MetaObject::PROTOTYPE);
        meta00->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("value00", "String")));
        metaCont->add (meta00);

        MetaObject *meta0 = factory.newMetaObject ();
        meta0->setId ("aska0");
        meta0->setScope (MetaObject::PROTOTYPE);
        meta0->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("value0", "String")));
        meta0->setParent ("askaParent");
        metaCont->add (meta0);

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("aska");
        meta->setClass ("Note");
        meta->setScope (MetaObject::PROTOTYPE);
        meta->addMapField (factory.newDataKeyNewString ("title", factory.newValueDataNewString ("value11", "String")));
        meta->addMapField (factory.newDataKeyNewString ("body", factory.newValueDataNewString ("value11", "String")));
        metaCont->add (meta);

        MetaObject *meta1 = factory.newMetaObject ();
        meta1->setId ("aska2");
        meta1->setClass ("Country");
        meta1->setScope (MetaObject::PROTOTYPE);
        meta1->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("value22", "String")));
        metaCont->add (meta1);

        MetaObject *meta2 = factory.newMetaObject ();
        meta2->setId ("aska3");
        meta2->setClass ("Address");
        meta2->setScope (MetaObject::PROTOTYPE);
        meta2->addMapField (factory.newDataKeyNewString ("street", factory.newValueDataNewString ("value33", "String")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value1", "text")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("6667", "int")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("123.45", "double")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("f", "char")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("true", "bool")));
        child->addListField (factory.newDataKey (factory.newNullData ()));

        child->setId ("syn");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "String")));
        child->addListField (factory.newDataKey (factory.newRefDataNewString ("syn")));

        child->setId ("ociec");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "String")));
        child->addListField (factory.newDataKey (factory.newRefDataNewString ("ociec")));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("field0", factory.newValueDataNewString ("value0", "String")));
        child->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "text")));
        child->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("6667", "int")));
        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("123.45", "double")));
        child->addMapField (factory.newDataKeyNewString ("field4", factory.newValueDataNewString ("f", "char")));
        child->addMapField (factory.newDataKeyNewString ("field5", factory.newValueDataNewString ("true", "bool")));
        child->addMapField (factory.newDataKeyNewString ("field6", factory.newNullData ()));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

        /*
         * Modyfikujemy bean mojBean stworzony w metodzie createMetaStructure07
         */

        MetaObject *meta = const_cast <MetaObject *> (metaCont->get ("mojBean"));
        meta->addMapField (factory.newDataKeyNewString ("city", factory.newRefDataNewString ("city")));

        /*
         * Tworzymy ten city, który jest używany przez mojBean
         */

        MetaObject *child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("field0", factory.newValueDataNewString ("value0", "String")));
        child->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "text")));
        child->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("value2", "text")));
        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("value3", "text")));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("field0", factory.newValueDataNewString ("value0", "String")));
        child->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "text")));
        child->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("6667", "int")));
        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("123.45", "double")));
        child->addMapField (factory.newDataKeyNewString ("field4", factory.newValueDataNewString ("f", "char")));
        child->addMapField (factory.newDataKeyNewString ("field5", factory.newValueDataNewString ("true", "bool")));
        child->addMapField (factory.newDataKeyNewString ("field6", factory.newNullData ()));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value1", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value2", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value3", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value4", "String")));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value1", "text")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("6665", "int")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("123.45", "double")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("f", "char")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("true", "bool")));
        child->addListField (factory.newDataKey (factory.newNullData ()));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Polska", "String")));
        child->setId ("country1");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Jamajka", "String")));
        child->setId ("country2");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Wolny Tybet", "String")));
        child->setId ("country3");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = factory.newMetaObject ();
        meta->addListField (factory.newDataKey (factory.newRefDataNewString ("country1")));
        meta->addListField (factory.newDataKey (factory.newRefDataNewString ("country2")));
        meta->addListField (factory.newDataKey (factory.newRefDataNewString ("country3")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
        child->setId ("city1");
        child->setClass ("City");
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Krakow", "String")));
        child->setId ("city2");
        child->setClass ("City");
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Piaseczno", "String")));
        child->setId ("city3");
        child->setClass ("City");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = factory.newMetaObject ();
        meta->addMapField (factory.newDataKeyNewString ("field0", factory.newRefDataNewString ("city1")));
        meta->addMapField (factory.newDataKeyNewString ("field1", factory.newRefDataNewString ("city2")));
        meta->addMapField (factory.newDataKeyNewString ("field2", factory.newRefDataNewString ("city3")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addConstructorArg (factory.newValueDataNewString ("value2", "String"));
        child->addConstructorArg (factory.newValueDataNewString ("value3", "text"));
        child->addConstructorArg (factory.newValueDataNewString ("6667", "int"));
        child->addConstructorArg (factory.newValueDataNewString ("123.45", "double"));
        child->addConstructorArg (factory.newValueDataNewString ("f", "char"));
        child->addConstructorArg (factory.newValueDataNewString ("true", "bool"));
        child->addConstructorArg (factory.newNullData ());

        child->setId ("mojBean");
        child->setClass ("Bar");
        child->setScope (MetaObject::PROTOTYPE);

        metaCont->add (child);

        return metaCont;
}

/**
 *
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure16 ()
{
        Ptr <MetaContainer> metaCont = boost::make_shared <MetaContainer> ();
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addConstructorArg (factory.newValueDataNewString ("value2", "String"));
        child->addConstructorArg (factory.newValueDataNewString ("value3", "text"));
        child->addConstructorArg (factory.newRefDataNewString ("city"));
        child->setId ("mojBean");
        child->setClass ("Bar");
        child->setScope (MetaObject::PROTOTYPE);

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *child1 = factory.newMetaObject ();
        child1->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

        /*
         * Modyfikujemy bean mojBean stworzony w metodzie createMetaStructure07
         */

        MetaObject *meta = const_cast <MetaObject *> (metaCont->get ("mojBean"));
        meta->addMapField (factory.newDataKeyNewString ("city", factory.newRefDataNewString ("ncity")));

        /*
         * Tworzymy ten city, który jest używany przez mojBean
         */

        MetaObject *child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
        child->setId ("ncity1");
        child->setClass ("City");
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Krakow", "String")));
        child->setId ("ncity2");
        child->setClass ("City");
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Piaseczno", "String")));
        child->setId ("ncity3");
        child->setClass ("City");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = factory.newMetaObject ();
        meta->addMapField (factory.newDataKeyNewString ("field0", factory.newRefDataNewString ("ncity1")));
        meta->addMapField (factory.newDataKeyNewString ("field1", factory.newRefDataNewString ("ncity2")));
        meta->addMapField (factory.newDataKeyNewString ("field2", factory.newRefDataNewString ("ncity3")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Polska", "String")));
        child->setId ("ncountry1");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Jamajka", "String")));
        child->setId ("ncountry2");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

        child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Wolny Tybet", "String")));
        child->setId ("ncountry3");
        child->setClass ("Country");
        child->setScope (MetaObject::PROTOTYPE);
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *meta = factory.newMetaObject ();
        meta->addListField (factory.newDataKey (factory.newRefDataNewString ("ncountry1")));
        meta->addListField (factory.newDataKey (factory.newRefDataNewString ("ncountry2")));
        meta->addListField (factory.newDataKey (factory.newRefDataNewString ("ncountry3")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addConstructorArg (factory.newValueDataNewString ("value2", "string"));
        child->addConstructorArg (factory.newValueDataNewString ("value3", "text"));
        child->addConstructorArg (factory.newRefDataNewString ("ncity"));

        child->setId ("mojBean");
        child->setClass ("Bar");
        child->setScope (MetaObject::PROTOTYPE);

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        MetaObject *child1 = factory.newMetaObject ();
        child1->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "string")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("field0", factory.newValueDataNewString ("value0", "String")));
        child->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "text")));
        child->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("6667", "int")));
        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("123.45", "double")));
        child->addMapField (factory.newDataKeyNewString ("field4", factory.newValueDataNewString ("f", "char")));
        child->addMapField (factory.newDataKeyNewString ("field5", factory.newValueDataNewString ("true", "bool")));
        child->addMapField (factory.newDataKeyNewString ("field6", factory.newNullData ()));

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

        MetaObject *meta00 = factory.newMetaObject ();
        meta00->setId ("mainBean");
        meta00->setClass ("Bar");
        meta00->addConstructorArg (factory.newValueDataNewString ("value2", "String"));
        meta00->addMapField (factory.newDataKeyNewString ("city4", factory.newRefDataNewString ("city")));
        meta00->addMapField (factory.newDataKeyNewString ("city5", factory.newRefDataNewString ("city")));
        meta00->setScope (MetaObject::PROTOTYPE);
        metaCont->add (meta00);

        MetaObject *meta0 = factory.newMetaObject ();
        meta0->setId ("city");
        meta0->setClass ("City");
        meta0->setScope (MetaObject::BEAN_PROTOTYPE);
        meta0->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->addInner (meta00, meta0);

        MetaObject *meta = factory.newMetaObject ();
        meta->setId ("list");
        meta->setClass ("BarMap");
        meta->addMapField (factory.newDataKeyNewString ("key01", factory.newRefDataNewString ("mainBean")));
        meta->addMapField (factory.newDataKeyNewString ("key02", factory.newRefDataNewString ("mainBean")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*------Level0-meta-globalne------------------------------------------------*/

        MetaObject *meta00 = factory.newMetaObject ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta00);

/*------Level1-inner-mata-city100-------------------------------------------*/

                MetaObject *meta01 = factory.newMetaObject ();
                meta01->setId ("city110");
                meta01->setClass ("City");
                meta01->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
                metaCont->addInner (meta00, meta01);

                        // Taka sama nazwa!
                        MetaObject *meta02 = factory.newMetaObject ();
                        meta02->setId ("cityA");
                        meta02->setClass ("City");
                        metaCont->addInner (meta01, meta02);

                        meta02 = factory.newMetaObject ();
                        meta02->setId ("cityB");
                        meta02->setClass ("City");
                        metaCont->addInner (meta01, meta02);

                meta01 = factory.newMetaObject ();
                meta01->setId ("city120");
                meta01->setClass ("City");
                meta01->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
                metaCont->addInner (meta00, meta01);

/*------Level2-inner-meta-city110-i-city120---------------------------------*/

                        meta02 = factory.newMetaObject ();
                        meta02->setId ("cityA");
                        meta02->setClass ("City");
                        metaCont->addInner (meta01, meta02);

                        meta02 = factory.newMetaObject ();
                        meta02->setId ("cityB");
                        meta02->setClass ("City");
                        metaCont->addInner (meta01, meta02);

/*--------------------------------------------------------------------------*/

        meta00 = factory.newMetaObject ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        metaCont->add (meta00);

/*--------------------------------------------------------------------------*/

                meta01 = factory.newMetaObject ();
                meta01->setId ("city110");
                meta01->setClass ("City");
                metaCont->addInner (meta00, meta01);

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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();
        child->addMapField (factory.newDataKeyNewString ("field0", factory.newValueDataNewString ("value0", "String")));
        child->addMapField (factory.newDataKeyNewString ("field1", factory.newValueDataNewString ("value1", "text")));
        child->addMapField (factory.newDataKeyNewString ("field2", factory.newValueDataNewString ("6667", "int")));
        child->addMapField (factory.newDataKeyNewString ("field3", factory.newValueDataNewString ("123.45", "double")));
        child->addMapField (factory.newDataKeyNewString ("field4", factory.newValueDataNewString ("f", "char")));
        child->addMapField (factory.newDataKeyNewString ("field5", factory.newValueDataNewString ("true", "bool")));
        child->addMapField (factory.newDataKeyNewString ("field6", factory.newNullData ()));
        child->addMapField (factory.newDataKeyNewString ("field7", factory.newRefDataNewString ("city100")));
        child->addMapField (factory.newDataKeyNewString ("field8", factory.newRefDataNewString ("city200")));

        child->setClass ("VariantMap");
        child->setId ("syn");

        MetaObject *meta00 = factory.newMetaObject ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta00);

        meta00 = factory.newMetaObject ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        meta00->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Wilno", "String")));
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
        MetaFactory factory (metaCont->getMemoryAllocator ());

/*--------------------------------------------------------------------------*/

        MetaObject *child = factory.newMetaObject ();

        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value0", "String")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("value1", "text")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("6667", "int")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("123.45", "double")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("f", "char")));
        child->addListField (factory.newDataKey (factory.newValueDataNewString ("true", "bool")));
        child->addListField (factory.newDataKey (factory.newNullData ()));
        child->addListField (factory.newDataKey (factory.newRefDataNewString ("city100")));
        child->addListField (factory.newDataKey (factory.newRefDataNewString ("city200")));
        child->setId ("syn");
        child->setClass ("VariantVector");
        metaCont->add (child);

        MetaObject *meta00 = factory.newMetaObject ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Warszawa", "String")));
        metaCont->add (meta00);

        meta00 = factory.newMetaObject ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        meta00->addMapField (factory.newDataKeyNewString ("name", factory.newValueDataNewString ("Wilno", "String")));
        metaCont->add (meta00);

        return metaCont;
}
