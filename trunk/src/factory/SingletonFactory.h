/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SINGLETONFACTORY_H_
#define SINGLETONFACTORY_H_

#include "factory/IFactory.h"
#include <cassert>
#include "core/variant/Variant.h"
#include "core/Typedefs.h"
#include "core/Pointer.h"
#include "core/ApiMacro.h"

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

        SingletonFactory (IFactory *f = NULL, bool b = false) : factory (f), deleteContents (b) {}
        virtual ~SingletonFactory ()
        {
                if (deleteContents) {
                        delete factory;
                }
        }

/*--------------------------------------------------------------------------*/

        virtual Core::Variant create (const Core::VariantMap &parameters = Core::VariantMap (), Core::DebugContext *context = NULL) const
        {
                if (cache.isNone ()) {
                        if (!factory) {
                                dcError (context, "SingletonFactory : factory == NULL!");
                                return Core::Variant ();
                        }

                        cache = factory->create (parameters, context);
                }

                return cache;
        }

        /**
         * Ta metoda wyczysci cache, czyli nastepne wywolanie
         * create spowoduje wykonanie metody create z factory.
         */
        virtual void reset () { cache = Core::Variant (); }

        IFactory *getFactory () const { return factory; }
        void setFactory (IFactory *factory) { this->factory = factory; }

private:

        IFactory *factory;
        mutable Core::Variant cache;
        bool deleteContents;
};

}

#endif /* SINGLETONFACTORY_H_ */
