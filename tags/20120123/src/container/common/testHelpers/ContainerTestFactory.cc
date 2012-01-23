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

using namespace Container;
using namespace Core;

/****************************************************************************/

Container::XmlContainerFactory ContainerTestFactory::cf;
Ptr <Container::BeanFactoryContainer> ContainerTestFactory::container;

/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerTestFactory::getContainer (const std::string &xmlFilePath)
{
//        try {
                if (!container) {
                        container = cf.create ();
                }

                container->reset ();
                cf.fill (container, xmlFilePath);
                return container;
//        }
//        catch (const Core::Exception &e) {
//                std::cerr << "Error @ ContainerFactory::createContainer : [" << e.getMessage() << "]. ";
//
//                if (container) {
//                        std::cerr << container->toString ();
//                }
//
//                std::cerr << std::endl;
//                throw;
//        }
}

/*
 * TODO Zrobić test kiedy parent jest Mapped, a child Indexed etc.
 * TODO Mergowanie jest b. ograniczone. W Springu jest tak, ze kolekcje
 * merguja sie nawet jesli nie maja ustawionego przodka. Wystarczy, ze
 * sa propertisami jakiegos beana, ktory ma.
 * TODO Wiecej testów. Jak na razie jest tylko 1.
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure01 ()
{
        /*
         * 1. Najpierw utworzymy MetaContainer i dodamy do niego
         * 2 elementy jeden elementy typu list.
         */
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> parent = boost::make_shared <MappedMeta> ();

        Ptr <MapElem> elem1 = MapElem::create ("field1", ValueData::create ("value1", "String"));
        elem1->addAttribute ("description", "To jest property bardzo ważne.");
        parent->addField (elem1);

        elem1 = MapElem::create ("field2", ValueData::create ("value2", "String"));
        elem1->addAttribute ("meta", "XXX");
        parent->addField (elem1);

        parent->setId ("ojciec");
        parent->setAbstract (true);
        parent->setLazyInit (true);

//        parent->addMetaInfo ("test1", Core::Variant (String ("valTest1")));
//        parent->addMetaInfo ("test2", Core::Variant (String ("valTest2")));

        Ptr <ListElem> elem2 = ListElem::create (ValueData::create ("carg1", "String"));
        parent->addConstructorArg (elem2);

        elem2 = ListElem::create (ValueData::create ("carg2", "String"));
        parent->addConstructorArg (elem2);

        metaCont->add (parent);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        elem1 = MapElem::create ("field3", ValueData::create ("value3", "String"));
        elem1->addAttribute ("meta", "YYY");
        child->addField (elem1);

        elem1 = MapElem::create ("field4", ValueData::create ("value4", "String"));
        elem1->addAttribute ("meta", "ZZZ");
        child->addField (elem1);

        child->setId ("syn");
        child->setParent ("ojciec");

//        child->addMetaInfo ("test3", Core::Variant (String ("valTest3")));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> parent = boost::make_shared <MappedMeta> ();
        parent->setId ("ojciec");
        parent->setAbstract (true);
        metaCont->add (parent);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->setId ("syn");
        child->setParent ("ojciec");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();
        meta->setId ("aska");
        metaCont->add (meta);

        Ptr <IndexedMeta> meta1 = boost::make_shared <IndexedMeta> ();
        meta1->setId ("aska2");
        metaCont->add (meta1);

        Ptr <IndexedMeta> meta2 = boost::make_shared <IndexedMeta> ();
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addField (MapElem::create ("field0", ValueData::create ("value0", "String")));
        child->addField (MapElem::create ("field1", ValueData::create ("value1", "text")));
        child->addField (MapElem::create ("field2", ValueData::create ("6667", "int")));
        child->addField (MapElem::create ("field3", ValueData::create ("123.45", "double")));
        child->addField (MapElem::create ("field4", ValueData::create ("f", "char")));
        child->addField (MapElem::create ("field5", ValueData::create ("true", "bool")));
        child->addField (MapElem::create ("field6", NullData::create ()));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <IndexedMeta> child = boost::make_shared <IndexedMeta> ();

        child->addField (ListElem::create (ValueData::create ("value0", "String")));
        child->addField (ListElem::create (ValueData::create ("value1", "text")));
        child->addField (ListElem::create (ValueData::create ("6667", "int")));
        child->addField (ListElem::create (ValueData::create ("123.45", "double")));
        child->addField (ListElem::create (ValueData::create ("f", "char")));
        child->addField (ListElem::create (ValueData::create ("true", "bool")));
        child->addField (ListElem::create (NullData::create ()));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

        Ptr <MappedMeta> meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("askaParent");
        meta00->setClass ("City");
        meta00->addField (MapElem::create ("field00", ValueData::create ("value00", "String")));
        metaCont->add (meta00);

        Ptr <MappedMeta> meta0 = boost::make_shared <MappedMeta> ();
        meta0->setId ("aska0");
        meta0->addField (MapElem::create ("field0", ValueData::create ("value0", "String")));
        meta0->setParent ("askaParent");
        metaCont->add (meta0);

        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();
        meta->setId ("aska");
        meta->setClass ("Note");
        meta->addField (MapElem::create ("field1", RefData::create ("aska0")));
        meta->addField (MapElem::create ("field11", ValueData::create ("value11", "String")));
        metaCont->add (meta);

        Ptr <MappedMeta> meta1 = boost::make_shared <MappedMeta> ();
        meta1->setId ("aska2");
        meta1->setClass ("Country");
        meta1->addField (MapElem::create ("field2", RefData::create ("aska")));
        meta1->addField (MapElem::create ("field22", ValueData::create ("value22", "String")));
        metaCont->add (meta1);

        Ptr <MappedMeta> meta2 = boost::make_shared <MappedMeta> ();
        meta2->setId ("aska3");
        meta2->setClass ("Address");
        meta2->addField (MapElem::create ("field3", RefData::create ("aska2")));
        meta2->addField (MapElem::create ("field33", ValueData::create ("value33", "String")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <IndexedMeta> child = boost::make_shared <IndexedMeta> ();

        child->addField (ListElem::create (ValueData::create ("value0", "String")));
        child->addField (ListElem::create (ValueData::create ("value1", "text")));
        child->addField (ListElem::create (ValueData::create ("6667", "int")));
        child->addField (ListElem::create (ValueData::create ("123.45", "double")));
        child->addField (ListElem::create (ValueData::create ("f", "char")));
        child->addField (ListElem::create (ValueData::create ("true", "bool")));
        child->addField (ListElem::create (NullData::create ()));

        child->setId ("syn");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = boost::make_shared <IndexedMeta> ();

        child->addField (ListElem::create (ValueData::create ("value0", "String")));
        child->addField (ListElem::create (RefData::create ("syn")));

        child->setId ("ociec");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        child = boost::make_shared <IndexedMeta> ();

        child->addField (ListElem::create (ValueData::create ("value0", "String")));
        child->addField (ListElem::create (RefData::create ("ociec")));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addField (MapElem::create ("field0", ValueData::create ("value0", "String")));
        child->addField (MapElem::create ("field1", ValueData::create ("value1", "text")));
        child->addField (MapElem::create ("field2", ValueData::create ("6667", "int")));
        child->addField (MapElem::create ("field3", ValueData::create ("123.45", "double")));
        child->addField (MapElem::create ("field4", ValueData::create ("f", "char")));
        child->addField (MapElem::create ("field5", ValueData::create ("true", "bool")));
        child->addField (MapElem::create ("field6", NullData::create ()));

        child->setId ("mojBean");
        child->setClass ("Foo");

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

        Ptr <IMeta> m = metaCont->get ("mojBean");
//        std::tr1::shared_ptr
//        std::tr1::shared_ptr <IMeta> =
        Ptr <MappedMeta> meta = dynamic_pointer_cast <MappedMeta> (m);
        meta->addField (MapElem::create ("city", RefData::create ("city")));

        /*
         * Tworzymy ten city, który jest używany przez mojBean
         */

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addField (MapElem::create ("field0", ValueData::create ("value0", "String")));
        child->addField (MapElem::create ("field1", ValueData::create ("value1", "text")));
        child->addField (MapElem::create ("field2", ValueData::create ("value2", "text")));
        child->addField (MapElem::create ("field3", ValueData::create ("value3", "text")));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addField (MapElem::create ("field0", ValueData::create ("value0", "String")));
        child->addField (MapElem::create ("field1", ValueData::create ("value1", "text")));
        child->addField (MapElem::create ("field2", ValueData::create ("6667", "int")));
        child->addField (MapElem::create ("field3", ValueData::create ("123.45", "double")));
        child->addField (MapElem::create ("field4", ValueData::create ("f", "char")));
        child->addField (MapElem::create ("field5", ValueData::create ("true", "bool")));
        child->addField (MapElem::create ("field6", NullData::create ()));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <IndexedMeta> child = boost::make_shared <IndexedMeta> ();

        child->addField (ListElem::create (ValueData::create ("value0", "String")));
        child->addField (ListElem::create (ValueData::create ("value1", "String")));
        child->addField (ListElem::create (ValueData::create ("value2", "String")));
        child->addField (ListElem::create (ValueData::create ("value3", "String")));
        child->addField (ListElem::create (ValueData::create ("value4", "String")));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <IndexedMeta> child = boost::make_shared <IndexedMeta> ();

        child->addField (ListElem::create (ValueData::create ("value0", "String")));
        child->addField (ListElem::create (ValueData::create ("value1", "text")));
        child->addField (ListElem::create (ValueData::create ("6665", "int")));
        child->addField (ListElem::create (ValueData::create ("123.45", "double")));
        child->addField (ListElem::create (ValueData::create ("f", "char")));
        child->addField (ListElem::create (ValueData::create ("true", "bool")));
        child->addField (ListElem::create (NullData::create ()));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Polska", "String")));
        child->setId ("country1");
        child->setClass ("Country");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Jamajka", "String")));
        child->setId ("country2");
        child->setClass ("Country");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Wolny Tybet", "String")));
        child->setId ("country3");
        child->setClass ("Country");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <IndexedMeta> meta = boost::make_shared <IndexedMeta> ();
        meta->addField (ListElem::create (RefData::create ("country1")));
        meta->addField (ListElem::create (RefData::create ("country2")));
        meta->addField (ListElem::create (RefData::create ("country3")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        child->setId ("city1");
        child->setClass ("City");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Krakow", "String")));
        child->setId ("city2");
        child->setClass ("City");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Piaseczno", "String")));
        child->setId ("city3");
        child->setClass ("City");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();
        meta->addField (MapElem::create ("field0", RefData::create ("city1")));
        meta->addField (MapElem::create ("field1", RefData::create ("city2")));
        meta->addField (MapElem::create ("field2", RefData::create ("city3")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addConstructorArg (ListElem::create (ValueData::create ("value2", "String")));
        child->addConstructorArg (ListElem::create (ValueData::create ("value3", "text")));
        child->addConstructorArg (ListElem::create (ValueData::create ("6667", "int")));
        child->addConstructorArg (ListElem::create (ValueData::create ("123.45", "double")));
        child->addConstructorArg (ListElem::create (ValueData::create ("f", "char")));
        child->addConstructorArg (ListElem::create (ValueData::create ("true", "bool")));
        child->addConstructorArg (ListElem::create (NullData::create ()));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addConstructorArg (ListElem::create (ValueData::create ("value2", "String")));
        child->addConstructorArg (ListElem::create (ValueData::create ("value3", "text")));
        child->addConstructorArg (ListElem::create (RefData::create ("city")));
//        child->addConstructorArg (ListElem::create (NullData::create ()));

        child->setId ("mojBean");
        child->setClass ("Bar");

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child1 = boost::make_shared <MappedMeta> ();
        child1->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        child1->setId ("city");
        child1->setClass ("City");
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

        Ptr <IMeta> m = metaCont->get ("mojBean");
        Ptr <MappedMeta> meta = dynamic_pointer_cast <MappedMeta> (m);
        meta->addField (MapElem::create ("city", RefData::create ("ncity")));

        /*
         * Tworzymy ten city, który jest używany przez mojBean
         */

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        child->setId ("ncity1");
        child->setClass ("City");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Krakow", "String")));
        child->setId ("ncity2");
        child->setClass ("City");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Piaseczno", "String")));
        child->setId ("ncity3");
        child->setClass ("City");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();
        meta->addField (MapElem::create ("field0", RefData::create ("ncity1")));
        meta->addField (MapElem::create ("field1", RefData::create ("ncity2")));
        meta->addField (MapElem::create ("field2", RefData::create ("ncity3")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Polska", "String")));
        child->setId ("ncountry1");
        child->setClass ("Country");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Jamajka", "String")));
        child->setId ("ncountry2");
        child->setClass ("Country");
        metaCont->add (child);

        child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("name", ValueData::create ("Wolny Tybet", "String")));
        child->setId ("ncountry3");
        child->setClass ("Country");
        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <IndexedMeta> meta = boost::make_shared <IndexedMeta> ();
        meta->addField (ListElem::create (RefData::create ("ncountry1")));
        meta->addField (ListElem::create (RefData::create ("ncountry2")));
        meta->addField (ListElem::create (RefData::create ("ncountry3")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addConstructorArg (ListElem::create (ValueData::create ("value2", "String")));
        child->addConstructorArg (ListElem::create (ValueData::create ("value3", "text")));
        child->addConstructorArg (ListElem::create (RefData::create ("ncity")));

        child->setId ("mojBean");
        child->setClass ("Bar");

        metaCont->add (child);

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child1 = boost::make_shared <MappedMeta> ();
        child1->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        child1->setId ("ncity");
        child1->setClass ("City");
        metaCont->add (child1);

        return metaCont;
}

/**
 * Singleton - taki jak w 07.
 * @return
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure21 ()
{
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addField (MapElem::create ("field0", ValueData::create ("value0", "String")));
        child->addField (MapElem::create ("field1", ValueData::create ("value1", "text")));
        child->addField (MapElem::create ("field2", ValueData::create ("6667", "int")));
        child->addField (MapElem::create ("field3", ValueData::create ("123.45", "double")));
        child->addField (MapElem::create ("field4", ValueData::create ("f", "char")));
        child->addField (MapElem::create ("field5", ValueData::create ("true", "bool")));
        child->addField (MapElem::create ("field6", NullData::create ()));

        child->setId ("mojBean");
        child->setClass ("Foo");
        child->setScope (IMeta::SINGLETON);

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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();

        child->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

        Ptr <MappedMeta> meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("mainBean");
        meta00->setClass ("Bar");
        meta00->addConstructorArg (ListElem::create (ValueData::create ("value2", "String")));
        meta00->addField (MapElem::create ("city", RefData::create ("city")));
        meta00->addField (MapElem::create ("city3", RefData::create ("city")));
        metaCont->add (meta00);

        Ptr <MappedMeta> meta0 = boost::make_shared <MappedMeta> ();
        meta0->setId ("city");
        meta0->setClass ("City");
        meta0->setScope (IMeta::BEAN);
        meta0->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        meta00->addInnerMeta (meta0);

        Ptr <MappedMeta> meta = boost::make_shared <MappedMeta> ();
        meta->setId ("list");
        meta->setClass ("BarMap");
        meta->addField (MapElem::create ("key01", RefData::create ("mainBean")));
        meta->addField (MapElem::create ("key02", RefData::create ("mainBean")));
        metaCont->add (meta);

        return metaCont;
}

/**
 * Test inner-outer
 */
Ptr <MetaContainer> ContainerTestFactory::createMetaStructure24 ()
{
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*------Level0-meta-globalne------------------------------------------------*/

        Ptr <MappedMeta> meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        metaCont->add (meta00);

/*------Level1-inner-mata-city100-------------------------------------------*/

                Ptr <MappedMeta> meta01 = boost::make_shared <MappedMeta> ();
                meta01->setId ("city110");
                meta01->setClass ("City");
                meta01->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
                meta00->addInnerMeta (meta01);

                        // Taka sama nazwa!
                        Ptr <MappedMeta> meta02 = boost::make_shared <MappedMeta> ();
                        meta02->setId ("cityA");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

                        meta02 = boost::make_shared <MappedMeta> ();
                        meta02->setId ("cityB");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

                meta01 = boost::make_shared <MappedMeta> ();
                meta01->setId ("city120");
                meta01->setClass ("City");
                meta01->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
                meta00->addInnerMeta (meta01);

/*------Level2-inner-meta-city110-i-city120---------------------------------*/

                        meta02 = boost::make_shared <MappedMeta> ();
                        meta02->setId ("cityA");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

                        meta02 = boost::make_shared <MappedMeta> ();
                        meta02->setId ("cityB");
                        meta02->setClass ("City");
                        meta01->addInnerMeta (meta02);

/*--------------------------------------------------------------------------*/

        meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        metaCont->add (meta00);

/*--------------------------------------------------------------------------*/

                meta01 = boost::make_shared <MappedMeta> ();
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <MappedMeta> child = boost::make_shared <MappedMeta> ();
        child->addField (MapElem::create ("field0", ValueData::create ("value0", "String")));
        child->addField (MapElem::create ("field1", ValueData::create ("value1", "text")));
        child->addField (MapElem::create ("field2", ValueData::create ("6667", "int")));
        child->addField (MapElem::create ("field3", ValueData::create ("123.45", "double")));
        child->addField (MapElem::create ("field4", ValueData::create ("f", "char")));
        child->addField (MapElem::create ("field5", ValueData::create ("true", "bool")));
        child->addField (MapElem::create ("field6", NullData::create ()));
        child->addField (MapElem::create ("field7", RefData::create ("city100")));
        child->addField (MapElem::create ("field8", RefData::create ("city200")));

        child->setClass ("VariantMap");
        child->setId ("syn");

        Ptr <MappedMeta> meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        metaCont->add (meta00);

        meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        meta00->addField (MapElem::create ("name", ValueData::create ("Wilno", "String")));
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
        Ptr <MetaContainer> metaCont = MetaContainer::create ();

/*--------------------------------------------------------------------------*/

        Ptr <IndexedMeta> child = boost::make_shared <IndexedMeta> ();

        child->addField (ListElem::create (ValueData::create ("value0", "String")));
        child->addField (ListElem::create (ValueData::create ("value1", "text")));
        child->addField (ListElem::create (ValueData::create ("6667", "int")));
        child->addField (ListElem::create (ValueData::create ("123.45", "double")));
        child->addField (ListElem::create (ValueData::create ("f", "char")));
        child->addField (ListElem::create (ValueData::create ("true", "bool")));
        child->addField (ListElem::create (NullData::create ()));
        child->addField (ListElem::create (RefData::create ("city100")));
        child->addField (ListElem::create (RefData::create ("city200")));
        child->setId ("syn");
        metaCont->add (child);

        Ptr <MappedMeta> meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("city100");
        meta00->setClass ("City");
        meta00->addField (MapElem::create ("name", ValueData::create ("Warszawa", "String")));
        metaCont->add (meta00);

        meta00 = boost::make_shared <MappedMeta> ();
        meta00->setId ("city200");
        meta00->setClass ("City");
        meta00->addField (MapElem::create ("name", ValueData::create ("Wilno", "String")));
        metaCont->add (meta00);
        metaCont->add (child);

        return metaCont;
}
