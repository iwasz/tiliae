/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BEANWRAPPEROUTPUT_H_
#define BEANWRAPPEROUTPUT_H_

#include "IOutput.h"
#include "../../core/Pointer.h"
#include "../../core/ApiMacro.h"

namespace Wrapper {
class IBeanWrapper;
}

namespace StateMachine {

/**
 * TODO implement
 * To jest daleka przyszłość, ale chodzi o to, zeby zrobic Output
 * tak, żeby korzystał z BeanWrappera i akcje czerpał z niego. Narazie
 * to nie jest w ogóle możliwe, bo BeanWrappery nie potrafią zwracać
 * IHandler, a tylko same dane. Ale pomysł jest taki, żeby mogły też
 * handlery. Wtdy nie trzeba będzie konfigurować Output, tylko się
 * wrapuje jakiś obiekt i wywołuje jego metody.
 * \ingroup StateMachine
 */
class TILIAE_API BeanWrapperOutput : public IOutput {
public:

        virtual ~BeanWrapperOutput () {}
        virtual Core::StringList run (const Core::StringList &inputs);

        Ptr<Wrapper::IBeanWrapper> getBeanWrapper() const { return beanWrapper; }
        void setBeanWrapper(Ptr<Wrapper::IBeanWrapper> beanWrapper) { this->beanWrapper = beanWrapper; }

private:

        Ptr <Wrapper::IBeanWrapper> beanWrapper;

};

}

#endif /* BEANWRAPPEROUTPUT_H_ */
