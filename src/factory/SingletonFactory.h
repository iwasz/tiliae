/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SINGLETONFACTORY_H_
#define SINGLETONFACTORY_H_

#include "IFactory.h"
#include <cassert>
#include "../core/variant/Variant.h"
#include "../core/Typedefs.h"
#include "../core/Pointer.h"
#include "../core/ApiMacro.h"

namespace Factory {

/**
 * To jest implementacja fabryki singletonów. Ona uzywa
 * zyklej fabryki IFactory, a wynik keszuje. To oznacza,
 * ze ta fabryka tworzy obiekt tylko raz, a potem, przy
 * kazdym nastepny uruchomieniu zwraca wskaznik do tego
 * utworzonego obiektu.
 * Ta fabryke mozna zresetowac metoda reset i wówczas
 * zachowuje sie ona jakby byla uzyta pierwszy raz.
 */
class TILIAE_API SingletonFactory : public IFactory {
public:

        SingletonFactory () {}
        SingletonFactory (Ptr <IFactory> f) : factory (f) {}
        virtual ~SingletonFactory () {}

/*--------------------------------------------------------------------------*/

        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::Context *context = NULL) const
        {
                if (cache.isNone ()) {
                        assert (factory);
                        cache = factory->create (parameters, context);
                }

                return cache;
        }

        /**
         * Ta metoda wyczysci cache, czyli nastepne wywolanie
         * create spowoduje wykonanie metody create z factory.
         */
        virtual void reset () { cache = Core::Variant (); }

        Ptr <IFactory> getFactory () const { return factory; }
        void setFactory (Ptr <IFactory> factory) { this->factory = factory; }

private:

        Ptr <IFactory> factory;
        mutable Core::Variant cache;
};

}

#endif /* SINGLETONFACTORY_H_ */
