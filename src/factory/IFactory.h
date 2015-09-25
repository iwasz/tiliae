/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IFACTORY_H_
#define IFACTORY_H_

#include <vector>
#include <wctype.h>

#include "core/Exception.h"
#include "core/variant/Variant.h"
#include "core/Object.h"
#include "core/Typedefs.h"
#include "core/ApiMacro.h"
#include "core/Pointer.h"
#include "core/DebugContext.h"
#include "ReflectionParserAnnotation.h"

namespace Factory {

/**
 * Interfejs fabryk dla użytkownika. Ten interfejs jest przeznaczony
 * dla końcowego użytkownika biblioteki. Nie oznacza to, ze nie mozna
 * go uzywac do implementacji samej biblioteki.
 *
 * Interfejs fabryk. Fabryka to coś, co tworzy nowe obiekty.
 * Jedyna funkcja w jej interfejsie przyjmuje dodatkowe parametry,
 * na podstawie których tworzy sie ten nowy obiekt.
 *
 * Dana klasa konkretna IFactory moze sluzyc do tworzenia tylko
 * jednego okreslonego obiektu (wowczas parameters sluza do skonfigurowania
 * tego obiektu), ale moze byc tez tak, ze dana klasa konkretna IFactory
 * moze tworzyc obiekty roznych klas (wowczas parameters posluza do
 * wyboru klasy). Nie da sie tego uniknac. Spojrzmy na przyklad na
 * ReflectionFactory ponizej : parametr "class" sluzy do wyboru klasy,
 * a parametr "constructor-args" przekazuje wrapowane w liscie
 * argumenty.
 * Natomiast GtkTreeModelFactory jest przykladem fabryki, ktora tworzy
 * tylko obiekty jednej okreslonej klasy. Parametry podawane do create
 * sa niezbedne do stworzenia te klasy.
 *
 * Nie da sie tez uniknac, ze ktos zaimplementuje fabryke zawierajaca inne
 * fabryki. Patrz TreeFactory i ComplicatedFactory.
 *
 * Nie zrzuca wyjątków, ponieważ fabryki można chainować (ChainFactory) i zrzucanie
 * wyjątków jest nieefektywne (a w ChainFactory dużo by ich leciało bez sensu). Do
 * informowania o statusie operacji służy ostatni parametr context.
 */
struct TILIAE_API __tiliae_reflect__ IFactory : public Core::Object {

        virtual ~IFactory () {}
        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const = 0;

};

/**
 *
 */
typedef std::vector <IFactory *> FactoryVector;

/**
 *
 */
struct TILIAE_API FactoryException : public Core::Exception {

        FactoryException (const std::string &m = "") : Core::Exception (m) {}
        virtual ~FactoryException () throw () {}
};


} // namespace

#endif /* IFACTORY_H_ */
