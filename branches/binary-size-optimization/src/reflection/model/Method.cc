/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                              //                return true;
 *    *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Method.h"
#include "Class.h"
#include <cassert>
#include "../../core/Typedefs.h"

namespace Reflection {

/****************************************************************************/

std::string Method::toString () const
{
        return "TODO";
}

/****************************************************************************/

Core::Variant Method::invoke (Core::Variant const &o, Core::VariantVector *list)
{
        try {
                assert (callableWrapper);
                return callableWrapper->call (o, list);
        }
        catch (Core::Exception &e) {
                e.addMessage ("In Method::invoke. Method name : [" + name + "]");
                throw;
        }
}

/****************************************************************************/

Core::Variant Method::invoke (Core::Variant const  &o, Core::Variant const &arg)
{
    try {
            assert (callableWrapper);
            /*
             * TODO To z pewnością jest bardzo nieoptymalne, ale dodanie analogicznej metody do
             * ICallablaWrapper i wszystkich szablonów spowoduje skonkretyzowanie kilkuset nowych metod!
             * Trzeba się zastanowic jak to zrobić.
             *
             * Uwaga, tu idzie kopia! Czyli jeśli metoda zmieni swój argument, to nic z tego.
             */
            Core::VariantVector v (1);
            v[0] = arg;
            return callableWrapper->call (o, &v);
    }
    catch (Core::Exception &e) {
            e.addMessage ("In Method::invoke. Method name : [" + name + "]");
            throw e;
    }
}

}
