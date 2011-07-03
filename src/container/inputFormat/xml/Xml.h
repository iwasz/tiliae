/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XML_H_
#define XML_H_

/**
\subsection ContainerInputFormat Format XML
\subsubsection ContainerInputFormatHeader Nagłowek XML
Xml zaczynamy nagłówkiem. Japroponuję taki, zawerający link do DTD:

<pre>
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE beans PUBLIC "-//SPRING//DTD BEAN 2.0//EN". 
        "file:///home/iwasz/program/projects/tiliae/sandBox/sandBox/tiliae-container-1.0.dtd">
</pre>


\subsubsection ContainerInputFormatRoot Root element <beans>
Root element to tag <beans>. Element <beans> może mieć następujące atrybuty:

- default-lazy-init : wartość true oznacza, że beany domyślnie będą miały ustawiony atrybut lazy-init na true. Każda inna, lub brak wartości oznacza, że beany będą miały lazy-init na false.
- default-init-method : specyfikuje domyślną nazwę metody inicjującej, którą będą wywoływać beany. Metodę tą można tez podac per bean za pomocą atrybutu init-method.
- default-merge : dotyczy kolekcji i to nie jest jeszcze zaimplementowane (chyba - sprawdzić).

\subsubsection ContainerInputFormatBean Tworzenie beana <bean>
Tag <bean> opisuje jeden bean. Bean może być dowolnego typu (łącznie z listami, mapami i skalarami typu int, string etc) pod warunkiem, że podsystem reflekcji będzie go znał. Atrybuty taga bean to:

- id : oznacza id tego beana. Musi być unikalne per kontener + zlikowane kontenery. ID beana jest używane jak wskaxnik do niego.
- class : nazwa klasy. Ta nazwa musi być dostępna w reflekcji, czyli classForName z tą nazwa musi coś zwracać. Klasa musi mieć jakiś publiczny konstruktor.
- parent : jako wrtość tego atrybutu podajemy ID beana, który ma być rodzicem. Ten nowy dziedziczy z niego prawie wszystkie wałsciwości.
- singleton : jesli warotścią tego atrybutu jest "true", to dajemy do zrozumienia kontenerowi, że nas zbean ma być singletonem, czyli każdorazowe pobranie go za pomocą getBean zwróci zawsze tą samą instancję.
- scope : możliwe wartości to : "singleton" (ekwiwalent singleton="true"), "prototype" (odwrotność singletonu - każdorazowe pobranie beana z kontenera za pomocą getBean pwoduje uruchomienie konstruktora klasy i stworzenie nowej instancji beana).
- init-method : wartością jest nazwa metody inicjującej. Metoda ta jest wywoływana przy tworzeniu beana zaraz po ustawieniu wszystkich property.
- editor : 
- factory :

Tagi które mogą występować w środku taga <bean> to : <property>, <constructor-arg> i <bean>.

\subsubsection ContainerInputFormatProperty Wywołanie settera, czyil <property>
Tag property równa się wywołaniu settera danego obiektu. Oczywiście setter musi mieć javowy format setNazwa i musi być dostępny z poziomu refleksji (czyli zaadnotowany za pomocą np. _m). Atrybuyu tagu to :

- name : nazwa, czyli nazwa pola - tak samo jak w javie.
- value : wartość. W tym momencie kontener napotkawszy ten atrybut stworzy obiekt typu Core::String i niestety nie dokona żadnej automatycznej konwersji. Jeśli typ ustawianego pola jest inny niż Core::String, nalezy użyć notacji z zagnieżdżonym tagiem <value type="mojTyp">, gdzie mojTyp oznacza własciwy typ.
- ref : wartością tego tagu musi być ID istniejącego beana (w tym lub zlinkowanym kontenerze).
*/

#include "XmlMetaService.h"
#include "XmlMetaServiceFactory.h"

#	endif /* XML_H_ */
