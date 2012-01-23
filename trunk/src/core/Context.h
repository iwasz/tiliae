/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTEXT_BW_H_
#define CONTEXT_BW_H_

#include <string>
#include <deque>
#include "../core/ApiMacro.h"

namespace Core {

/**
 * Status operacji get/set w beanwrapperze + informacja o
 * błędzie. Można subklasować i dodać jakieś swoje metody,
 * ale wówczas pluginy muszą to obsługiwać.
 */
class TILIAE_API Context {
public:

        Context () : error (false) {}
        virtual ~Context () {}

/*--------------------------------------------------------------------------*/

        std::string getMessage () const;

        void clear ()
        {
                stack.clear ();
                error = false;
        }

        /**
         * Clears error status, leaves message intact.
         */
        void clearError () { error = false; }
        bool isError () const { return !stack.empty (); }

/*--------------------------------------------------------------------------*/

        /**
         * Dopisuje na koniec.
         */
        void appendError (const std::string &e) { stack.push_back (e); }
        void prependError (const std::string &e) { stack.push_front (e); }

        void apendContext (Context const &c);
        void prependContext (Context const &c);

private:

        std::deque <std::string> stack;
        bool error;

};


}

#if defined (TILIAE_DEBUG)

#define error(context_, ExceptionClass_, errorNum_, errorMsg_) \
                                                               \
        if ((context_)) {                                      \
                (context_)->appendError ((errorMsg_));            \
        }                                                      \
        else {                                                 \
                throw ExceptionClass_ ((errorMsg_));           \
        }

#else

#define error(context_, ExceptionClass_, errorNum_, errorMsg_) \
                                                               \
        if ((context_)) {                                      \
                (context_)->appendError ((errorNum_));         \
        }                                                      \
        else {                                                 \
                throw ExceptionClass_ ((errorMsg_));           \
        }

#endif


#endif /* CONTEXT_H_ */
