/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "IOutput.h"
#include "../../common/handler/ZeroHandler.h"
#include "../../core/Exception.h"
#include "../../core/string/String.h"
#include "../../core/ApiMacro.h"

namespace StateMachine {

/**
 * Output jest jednym z rodzajów IOutput. Jest to po prostu
 * fancy-method of invoking actions (IHandler objects). (Że tak
 * z angielska napisze). W zasadzie nie ma w nim wielkiej filozofii.
 * Odwzorowuje nazwy na bezargumentowe IHandlery. Wykorzystując
 * interfejs IOutput można go użyć tak:
 *
 * ak->addInput ("FANCY_ACTION");
 * ak->addInput ("START_MOTOR");
 * ak->run ();
 *
 * Powyzsze spowoduje wywolanie metod odpowiadających podanym
 * parametrom wejśiowym.
 *
 * TODO powinienem zmienic nomenklature : w outpucie nie powinno
 * byc ,,akcji'', tylko ,,handlery''. Akcje są w State.
 * \ingroup StateMachine
 */
class TILIAE_API Output : public IOutput {
public:

        virtual ~Output () {}

/*-- IOutput ---------------------------------------------------------------*/

//        virtual void addInput (const Core::String &input) { inputs.add (input); }
//        virtual void removeInput (const Core::String &input) { inputs.remove (input); }
//        virtual Core::StringList getInputs () const { return inputs; }
//        virtual void setInputs (const Core::StringList &inputs) { this->inputs = inputs; }
//        virtual void clearInputs () { inputs.clear (); }
//
//        virtual void run ();

        /**
         * Odpowiednik:
         * ak->setInputs (inputs);
         * ak->run ();
         * ak->clearInputs ();
         */
        virtual Core::StringList run (const Core::StringList &inputs);

/*-- Output -------------------------------------------------------------*/

        void setActions (const Common::ZeroHandlerMap &actions) { this->actions = actions; }
        Common::ZeroHandlerMap getActions () const { return actions; }

        void addAction (const std::string &name, Ptr <Common::ZeroHandler> action) { actions[name] = action; }
        void removeAction (const std::string &name);

private:

        Common::ZeroHandlerMap actions;

};

/**
 * To jest wyjątek zrzucany kiedy Output dostanie nazwę
 * akcji do wykonania, ale nie ma takiej akcji skojarzonej
 * z tą nazwą.
 */
struct TILIAE_API OutputException : public Core::Exception {

};

} // nam

#endif /* OUTPUT_H_ */
