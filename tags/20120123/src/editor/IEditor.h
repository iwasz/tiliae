/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TTEE_IEDITOR_H_
#define TTEE_IEDITOR_H_

#include <list>
#include <vector>
#include <map>
#include <wctype.h>
#include "../core/Object.h"
#include "../core/variant/Variant.h"
#include "../core/Pointer.h"
#include "../core/Exception.h"
#include "../core/ApiMacro.h"
#include "../common/Context.h"

namespace Editor {

/**
 * Interfejs edytorów dla użytkownika. Ten interfejs jest przeznaczony
 * dla końcowego użytkownika biblioteki. Nie oznacza to, ze nie mozna
 * go uzywac do implementacji samej biblioteki.
 *
 *  Interfejs klas, ktore implementuja konwersje obiektu jednego typu w
 *  obiekt innego typu. Zarowno obiekt wejsciowy jak i wyjsciowy sa
 *  przekazywane w postaci wariantow. IEditor moze (ale nie musi)
 *  tworzyc obiekt docelowy.
 */
class TILIAE_API IEditor : public Core::Object {
public:

        virtual ~IEditor () {}

        /**
         *  Nie ruszac tego API bez tygodniowego namyslu!
         *  Output ma typ Variant::NONE gdy konwersja nie udala sie. Zatem kiedy nie uda
         *  sie skonwertowac input w output z jakiegos powodu (zle typy wejsiocwych danych,
         *  albo inny blad), nie nalezy wywalac aplikacji, tylko zwrocic pusty output
         *  (taki, ktorego getType () == Variant::NONE). Chyba, ze blad jest zupelnie
         *  krytyczny.
         */
        virtual void convert (const Core::Variant &input, Core::Variant *output, Common::Context *context = NULL) = 0;

};

typedef std::list <Ptr <IEditor> > EditorList;
typedef std::vector <Ptr <IEditor> > EditorVector;
typedef std::map <std::string, Ptr <IEditor> > EditorMap;

struct TILIAE_API EditorException : public Core::Exception {

        EditorException (const std::string &m = "") : Core::Exception (m) {}
        virtual ~EditorException () throw () {}
};

}

#endif /* IEDITOR_H_ */
