/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTAINER_H_
#define CONTAINER_H_

/**
 * \page Kontener Kontener IoC
 * \section KPoKolei Co się dzieje po kolei
 * Klasa Container::ContainerFactory potrafi stworzyć obiekt BeanFactoryContainer, który jest gotowy do stworzenia
 * beanów z opisu dostarczonego w obiekcie typu MetaContainer. MetaContainer musi byc stworzony gdzies
 * indziej.
 *
 * Konstruktor ContainerFactory tworzy 2 obiekty "iterujące" typu MetaVisitor, do których przypisywane
 * są rózne serwisy (handlery reagujące na poszczególne elementy meta-struktury):
 *
 * - Tworzy mapę singletonów, które są niezbędne do pracy kontenera (systemowe).
 * - Tworzy obiekt Container::MetaVisitor (iteracja 1), który służy do iterowania po meta-strukturze (implementuje
 * pętlę for).
 *   - Container::ParentService - parent service służy do uzupełnianai child-meta parametrami z ich rodziców.
 *   - Container::BeanFactoryInitService - już od razu tworzy jeden BeanFactory per jeden IMeta. Stworzone fabryki umieszcza pod
 *   odpowiednim kluczem w BeanFactoryMap (jeśli są główne, czyli globalne), lub umieszcza je w innej BeanFactory jako innerBeanFactory.
 *   - Container::MappedValueService - tworzy ustawia input typu OrderedVariantMap do BeanFactory. Kiedy napotka na Value, umieszcza je w
 *   tej mapie (używa do tego jakiegoś serwisu). Napotykając refy tworzy pusty klucza w mapie. Analogicznie z nulami (unllowego warianta wrzuca).
 *   - Container::IndexedValueService - ustawia input do BeanFactory, tylko inputem jest VariantList. Reszta tak samo.
 * - Tworzy obiekt Container::MetaVisitor (iteracja 2).
 *   - Container::BeanStackUpdateService - jedynie umieszcza każdy BeanFactory na stosie (i zdejmuje po zakończeniu
 *   obsługi). Beany mogą być przecież zagnieżdżone. W poprzedniej iteracji to serwis Container::BeanFactoryInitService
 *   tworząc fabryki umieszczał je na stosie - a w tej iteracji stos trzeba przygotować od nowa.
 *   - Container::EditorService - tworzy mapped editory i ustawia je BeanFactory-om.
 *   - Container::ListEditorService - tworzy Indexed editory i ustawia je BeanFactory-om.
 *   - Container::FactoryService - sprawdza, czy user nie podał swojej customowej fabryki.
 */

#include "ContainerFactory.h"
#include "Defs.h"
#include "beanFactory/BeanFactory.h"
#include "common/Common.h"
#include "inputFormat/InputFormat.h"
#include "metaStructure/MetaStructure.h"

#	endif /* CONTAINER_H_ */
