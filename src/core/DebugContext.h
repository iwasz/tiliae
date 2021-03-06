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
#include "core/ApiMacro.h"
#include <vector>

namespace Core {

/**
 * Status operacji get/set w beanwrapperze + informacja o
 * błędzie. Można subklasować i dodać jakieś swoje metody,
 * ale wówczas pluginy muszą to obsługiwać.
 */
class TILIAE_API DebugContext {
public:

        DebugContext () : transaction (-1) {}
        virtual ~DebugContext () {}

/*--------------------------------------------------------------------------*/

        std::string getMessage () const;
        void clear () { stack.clear (); }

/*--------------------------------------------------------------------------*/

        /**
         * Dopisuje na koniec.
         */
        void addMessage (const std::string &e);
        void addContext (DebugContext const &c);

/*--------------------------------------------------------------------------*/

        void begin ();
        void commit ();
        void rollback ();

private:

        std::vector <std::string> stack;
        int transaction;

};


}

#ifndef NDEBUG
#define dcError(context_, errorMsg_)                              \
                                                                  \
        if ((context_)) {                                         \
                (context_)->addMessage ((errorMsg_));             \
        }
#else
#define dcError(context_, errorMsg_)
#endif

#ifndef NDEBUG
extern TILIAE_API void dcBegin (Core::DebugContext *dc);
extern TILIAE_API void dcCommit (Core::DebugContext *dc);
extern TILIAE_API void dcRollback (Core::DebugContext *dc);
#else
#define dcBegin(a)
#define dcCommit(a)
#define dcRollback(a)
#endif


#endif /* CONTEXT_H_ */
