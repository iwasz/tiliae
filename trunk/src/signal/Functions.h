/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <string>
#include "K202.h"
#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "core/string/String.h"
#include "core/ApiMacro.h"

namespace Signal {
class Scope;

/**
 * Wysyła anonimowo sygnał. System nie wie od kogo pochodzi ten sygnał
 * (odbiorca nigdy nie wie).
 *
 * Sygnał zawsze wysyłany z aktualnego scope (czyli tak samo, jak byśmy
 * dodali do sygnału przedrostek /aktualne/scope/).
 * \ingroup Signal
 */
extern TILIAE_API Core::Variant emit (const std::string &path,
        const Core::VariantVector &paramVector = Core::VariantVector (),
        const Core::VariantMap &argsMap = Core::VariantMap ());

/**
 * Emituje sygnał w scope podanym jako pierwszy argument.
 * \ingroup Signal
 */
extern TILIAE_API Core::Variant emit (Ptr <Scope> scope, /*const std::string &signalName,*/
        const Core::VariantVector &paramVector = Core::VariantVector (),
        const Core::VariantMap &argsMap = Core::VariantMap ());

/**
 * Przyporządkowuje dany obiekt do scope podanego ako pierwszy argument. Obiekty w jednym scope
 * stają się siebie świadome, czyli de facto stają się połączone ze sobą.
 * \ingroup Signal
 */
extern TILIAE_API void bind (const std::string &scope, void *receiver);

/**
 * Przyporządkowuje dany obiekt do scope podanego ako pierwszy argument. Obiekty w jednym scope
 * stają się siebie świadome, czyli de facto stają się połączone ze sobą.
 * \ingroup Signal
 */
extern TILIAE_API void bind (const std::string &scope, void *r1, void *r2);

/**
 * Przyporządkowuje dany obiekt do scope podanego ako pierwszy argument. Obiekty w jednym scope
 * stają się siebie świadome, czyli de facto stają się połączone ze sobą.
 * \ingroup Signal
 */
extern TILIAE_API void bind (const std::string &scope, void *r1, void *r2, void *r3);

/**
 * Pozwala pobrać wskaźnik do scope-a.
 * \ingroup Signal
 */
extern TILIAE_API Ptr <Scope> findScope (const std::string &scopePath);

} // nam

#endif /* FUNCTIONS_H_ */
