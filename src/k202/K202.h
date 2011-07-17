/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef K202_H_
#define K202_H_

#include "../core/variant/Variant.h"
#include "../core/Typedefs.h"
#include "../core/string/String.h"
#include "Context.h"
#include "extension/IExtension.h"
#include "Reflection.h"
#include "../beanWrapper/IBeanWrapper.h"

namespace k202 {

class Script;
class Compiler;

/**
 * Odpowiedzialność : Centralna klasa/serwis udostępniająca zewnętrzne API
 * do uruchamiania (i niejawnego kompilowania) skryptów.
 */
class TILIAE_API K202 {
public:
        __d

        virtual ~K202 () {}

        /**
         * Create new instance.
         */
        static Ptr <K202> create (Ptr <Wrapper::IBeanWrapper> b = Ptr <Wrapper::IBeanWrapper> (),
                                  Ptr <IExtension> ext = Ptr <IExtension> ());

        /**
         * Return singleton one.
         */
        static K202 *instance ();

        /**
         * Parametr domain ma takie samo zadanie jak argsMap, w zasadzie mógłby być
         * jednym z argumentów, ale dla uproszczenia jest osobno (nie trzeba tworzyć
         * listy). W skrypcie odwołujemy się do niego bezpośrednio : wyrażenie ${}
         * ma właśnie jego wartość.
         *
         * dimain jest przekazywany do skryptu niejako "przez referencję (można go
         * zmienić). Natomiast argsMap przez wartość (nie można zmienić mapy, zmiany
         * są tylko lokalne i widoczne podczas działania skryptu).
         */
        Core::Variant run (const std::string &sourceCode,
                           const Core::Variant &domain = Core::Variant (),
                           const Core::VariantVector &paramVector = Core::VariantVector (),
                           const Core::VariantMap &argsMap = Core::VariantMap ());

        /**
         * Automatycznie skompiluje Instruction, jeśli nie jest jeszcze skopilowana.
         * Zasady mergowania parametrów i argumentów są następujące : argsMap ze
         * script i argument argsMap tej metody są dodawane do wspólnej mapy za pomocą
         * setAll. Podobnie jest z paramVector, ale na początku idą parametry z
         * obiektu script a następnie z parametru paramVector tej metody.
         */
        Core::Variant run (Ptr <Script> script,
                           Core::Variant *domain = NULL,
                           const Core::VariantVector &paramVector = Core::VariantVector (),
                           const Core::VariantMap &argsMap = Core::VariantMap ());

        // Tworzy nowy obiekt instrukcji.
        Ptr <Script> prepare (const std::string &sourceCode,
                        const Core::Variant &domain = Core::Variant (),
                        const Core::VariantVector &paramVector = Core::VariantVector (),
                        const Core::VariantMap &argsMap = Core::VariantMap ());

/*--------------------------------------------------------------------------*/

        Ptr <Wrapper::IBeanWrapper> getBeanWrapper () const { return ctx.getBeanWrapper (); }
        _s (setBeanWrapper) void setBeanWrapper (Ptr <Wrapper::IBeanWrapper> b) { ctx.setBeanWrapper (b); }

private:

        template <typename T>
        static T createHelper (Ptr <IExtension> ext);

        K202 () {}
        K202 (const K202 &) {}

private:

        Context ctx;
        Ptr <Compiler> compiler;

        _e (K202)
};

}

#endif /* K202_H_ */
