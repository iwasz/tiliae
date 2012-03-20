/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLMETASERVICE_H_
#define XMLMETASERVICE_H_

#include <IXmlReader.h>
#include <Machine.h>
#include <Reflection.h>
#include <logger/ILogger.h>
#include <queue>

#include "ChainMachine.h"
#include "input/MultiObject.h"
#include "input/Input.h"
#include "metaStructure/model/meta/IMeta.h"

namespace Container {

class IIdGenerator;
class MetaContainer;
struct ListElem;
struct MapElem;
struct MappedMeta;
struct IndexedMeta;
class AbstractElem;
class IElem;

/**
 * Tworzy meta-strukturę z XML.
 * Serwis wczytujący strukturę metadanych z pliku XML
 * w formacie TiliaeContainer.
 *
 * Zasady działania:
 *
 * Co się składa na stan serwisu?
 * - Aktualnie wczytany tag/atrybut/vartość
 * - Wartość zagnieżdżenia tagów / ilość na Meta stosie.
 * - Aktualny Meta
 * - Aktualny MetaElem - moze nie istniec
 *
 * Legenda:
 * <Xxx> : tag Xxx
 * Xxx= : argument taga
 *
 * 1. <beans>
 * - Utwórz nowy Meta.
 * - Dodaj mu MetaElem o systemowej nazwie #beans.
 *
 *      a. (default-lazy-init= || default-init-method= ||
 *      default-merge=) && aktualny
 *      tag == <beans>
 *      - Wtwórz MetaElem odpowiednio : lazy-init, init-method,
 *        merge
 *      - Dodaj do aktualnego taga (na wierzchołku stosu).
 *
 * 2. <description>
 * - Wczytaj jego opis do stringa.
 *
 *      a. Aktualny MetaElem istnieje -> dodaj description do niego.
 *      b. Aktualny MetaElem nie jest ustawiony i aktualny Meta istnieje ->
 *      dodaj opis do aktualnego Meta.
 *
 * 3. <alias name="test" alias="tescior">
 * 4. <import>
 * - No tu sie trzeba bedzie zastanowic, ale chyba po prostu nowy reader,
 * czyli readery tez musza byc na stosie. Ograniczenie zagniezdzenia do N.
 *
 * 5. <bean>
 * - Stworz klucz:
 *      - Jesli argument id jest obecny, to użyj go. Jesli nie, to wygeneruj
 *      nazwe.
 *
 *      - Jesli aktualny Meta.name != #beans, to oznacza, ze ten bean jest w
 *      jakims innym. Trzeba zasymulowac <ref local="nazwaPowyzej" />, czyli
 *      wywolac akcje, ktora by sie wtedy wykonala.
 *
 * - No napewno stworz nowy obiekt Meta.
 * - Wczytaj wszystkie argumenty (kazdy z nich to MetaElem).
 *
 * 6. <meta>
 * - Jak w przypadku description
 * \ingroup Container
 */
class TILIAE_API XmlMetaService/* : public IMetaService*/ {
public:

        REFLECTION_CONSTRUCTOR_ (void)

        XmlMetaService ();
        virtual ~XmlMetaService () {}

        virtual void populate (const std::string &xmlFile);
        virtual void reset ();

/*--------------------------------------------------------------------------*/

        Ptr <Xml::IXmlReader> getXmlReader () const { return xmlReader; }
        void setXmlReader (Ptr <Xml::IXmlReader> xmlReader) { this->xmlReader = xmlReader; }

        /**
         * Zwraca obiekt MetaContainer uzupełniony za pomoca
         * populate.
         */
        Ptr <MetaContainer> getMetaContainer () const { return metaContainer ;}
        void setMetaContainer (Ptr <MetaContainer> m) { metaContainer = m; }

        Ptr<StateMachine::Machine> getMachine () const { return machine; }
        void setMachine (Ptr<StateMachine::Machine> machine) { this->machine = machine; }

        Ptr<IIdGenerator> getIdGenerator() const { return idGenerator; }
        void setIdGenerator(Ptr<IIdGenerator> idGenerator) { this->idGenerator = idGenerator; }

/*-- Metody wołane przez FSM -----------------------------------------------*/

        REFLECTION_METHOD (setDefaultLazyInit);
        void setDefaultLazyInit ();

        REFLECTION_METHOD (setDefaultInitMethod);
        void setDefaultInitMethod ();

        REFLECTION_METHOD (setDefaultMerge);
        void setDefaultMerge ();

        REFLECTION_METHOD (popCurrentBean); void popCurrentBean ();
        REFLECTION_METHOD (popCurrentMetaAndGenerateRef); void popCurrentMetaAndGenerateRef (); /// Obsługuje zagnieżdżone beany.


        /// Nowy MappedMeta. Na przykład kiedy <bean> lub <map>
        REFLECTION_METHOD (pushNewMappedMeta); void pushNewMappedMeta ();

        /// Nowy IndexedMeta. Uruchamia się w okolicach <list>
        REFLECTION_METHOD (pushNewIndexedMeta); void pushNewIndexedMeta ();

        /// Nowy MapElem - wywoływane podzac pracy w mapach i beanach.
        REFLECTION_METHOD (pushNewMapElem); void pushNewMapElem ();

        /// Nowy ListElem - wywoływane podzac pracy w listach.
        REFLECTION_METHOD (pushNewListElem); void pushNewListElem ();

        REFLECTION_METHOD (popCurrentMapElem);         void popCurrentMapElem (); /// Zdejmuje aktualnie przetwarzany MapElem.
        REFLECTION_METHOD (popCurrentIndexedElem);     void popCurrentIndexedElem (); /// Zdejmuje aktualnie przetwarzany IndexedElem.
        REFLECTION_METHOD (popCurrentCArg);            void popCurrentCArg (); /// Zdejmuje aktualnie przetwarzany IndexedElem i dodaje go do aktualnego meta jako cArg.

        REFLECTION_METHOD (setCurrentMapElemKey);      void setCurrentMapElemKey (const std::string &s); /// Oczekuje, że aktualny Elem to MapElem. Ustawia mu Key.
        REFLECTION_METHOD (setCurrentRefDataData);     void setCurrentRefDataData (const std::string &s);

        REFLECTION_METHOD (newValueData);              void newValueData (); /// Tworzy nowe ValueData
        REFLECTION_METHOD (newRefData);                void newRefData (); /// Tworzy nowe RefData.
        REFLECTION_METHOD (setCurrentValueDataType);   void setCurrentValueDataType (const std::string &s); /// Ustawia w nim type
        REFLECTION_METHOD (setCurrentValueDataData);   void setCurrentValueDataData (const std::string &s); /// Ustawia w nim data lub tworzy zupełnie nowe z typem string.

        REFLECTION_METHOD (newNullData);       void newNullData ();                            /// Tworzy nowe NullData i ustawia do currentElem.
        REFLECTION_METHOD (setMetaId);         void setMetaId (const std::string &id);        /// Ustawia ID w katualnym Meta.
        REFLECTION_METHOD (setMetaClass);      void setMetaClass (const std::string &clazz);  /// Ustawia parametr class w aktualnym Meta.
        REFLECTION_METHOD (setMetaParent);     void setMetaParent (const std::string &par);   /// Ustawia parametr 'parent' w aktualnym Meta.
        REFLECTION_METHOD (setMetaFactory);    void setMetaFactory (const std::string &s);    /// Ustawia parametr 'factory' w aktualnym Meta.
        REFLECTION_METHOD (setMetaEditor);     void setMetaEditor (const std::string &s);     /// Ustawia parametr 'editor' w aktualnym Meta.
        REFLECTION_METHOD (setMetaSingleton);  void setMetaSingleton (bool b);                 /// Ustawia parametr 'singleton' w aktualnym Meta.
        REFLECTION_METHOD (setMetaLazyInit);   void setMetaLazyInit (bool b);                  /// Ustawia parametr 'lazy-init' w aktualnym Meta.
        REFLECTION_METHOD (setMetaScope);      void setMetaScope (const std::string &scope);  /// Ustawia parametr 'scope (singleton/prototype/bean)' w aktualnym Meta.
        REFLECTION_METHOD (setMetaInitMethod); void setMetaInitMethod (const std::string &s); /// Ustawia parametr 'init-method' w aktualnym Meta.
        REFLECTION_METHOD (importFile);        void importFile (const std::string &s);        /// Importuje kolejny plik.
        //        REFLECTION_METHOD (setMetaScopeId); void setMetaScopeId (const std::string &id); /// Ustawia parametr 'scope-id' w aktualnym Meta.

private:

        void prepareType (Core::VariantMap *map, int nodeType) const;
        void prepareInputs (Core::VariantMap *run,
                            Core::VariantMap *transition,
                            Ptr <Xml::IXmlReader> reader, bool end = false);

        Ptr <IMeta> getCurrentMeta () const;
        Ptr <MappedMeta> getCurrentMappedMeta () const;
        Ptr <IndexedMeta> getCurrentIndexedMeta () const;

        Ptr <IElem> getCurrentElem () const;
        Ptr <AbstractElem> getCurrentAbstractElem () const;
        Ptr <MapElem> getCurrentMapElem () const;
        Ptr <ListElem> getCurrentListElem () const;

        void runLog (bool back = false);

private:

        Ptr <Xml::IXmlReader> xmlReader;
        // XmlReaderService, a service ma Factory i  XmlReaderStack i nie zagnieździ wiecej niz 10 razy.

/*-- MetaObjects -----------------------------------------------------------*/

        /// Pamięć podręczna obiektów Meta (odzwierciadlających beany, mapy listy).
        MetaStack metaStack;

        /// Pamięć podręczna obiektów MetaElem (odzwierciadlających property beanów, elementy list i map).
        MetaElemStack metaElemStack;

        /// Konter na obiekty meta utworzone po wczytaniu XML.
        Ptr <MetaContainer> metaContainer;

        /// Generuje id dla benów, które są embednięte jeden w drugim.
        Ptr <IIdGenerator> idGenerator;

        /// Paths to files to import.
        std::queue <std::string> imports;

/*-- Smieci od maszyny stanow ----------------------------------------------*/

        Ptr <StateMachine::Machine> machine;
        StateMachine::MachineContext ctx;
        Core::VariantMap machScope;

/*-- Smieć -----------------------------------------------------------------*/

        Ptr <Common::ILogger> log;

        REFLECTION_END (XmlMetaService);
};

} // namespace

#endif /* XMLMETASERVICE_H_ */
