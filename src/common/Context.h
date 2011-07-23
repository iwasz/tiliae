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
#include <boost/lexical_cast.hpp>
#include "../core/ApiMacro.h"

namespace Common {

enum {

        UNDEFINED_ERROR = 0x0000000000000001UL
};

#if defined (TILIAE_DEBUG)

/**
 * Status operacji get/set w beanwrapperze + informacja o
 * błędzie. Można subklasować i dodać jakieś swoje metody,
 * ale wówczas pluginy muszą to obsługiwać.
 */
class TILIAE_API Context {
public:

        Context () : msgCount (0), fatal (false), error (false) {}
        virtual ~Context () {}

/*--------------------------------------------------------------------------*/

        std::string getMessage () const { return message; }

        void clear ()
        {
                message = std::string ();
                msgCount = 0;
                fatal = false;
                error = false;
        }

/*--------------------------------------------------------------------------*/

        /**
         * Dopisuje na koniec.
         */
        void addFatal (const std::string &errorMessage);
        void addError (const std::string &errorMessage);

/*--------------------------------------------------------------------------*/

        bool isFatal () const { return fatal; }
        bool isError () const { return error; }
        bool isEmpty () const { return !fatal && !error; }

private:

        std::string message;
        int msgCount;

        bool fatal;
        bool error;

};

#else

class TILIAE_API Context {
public:

        Context () : message (0UL), fatal (false), error (false) {}
        virtual ~Context () {}

/*--------------------------------------------------------------------------*/

        std::string getMessage () const { return boost::lexical_cast <std::string> (message); }

        void clear ()
        {
                message = 0UL;
                fatal = false;
                error = false;
        }

/*--------------------------------------------------------------------------*/

        /**
         * Dopisuje na koniec.
         */
        void addFatal (unsigned long int i)
        {
                fatal = true;
                message |= i;
        }

        void addError (unsigned long int i)
        {
                error = true;
                message |= i;
        }

/*--------------------------------------------------------------------------*/

        bool isFatal () const { return fatal; }
        bool isError () const { return error; }
        bool isEmpty () const { return !fatal && !error; }

private:

        unsigned long int message;

        bool fatal;
        bool error;

};

#endif

}

#if defined (TILIAE_DEBUG)

#define fatal(context_, ExceptionClass_, errorNum_, errorMsg_) \
                                                               \
        if ((context_)) {                                      \
                (context_)->addFatal ((errorMsg_));            \
        }                                                      \
        else {                                                 \
                throw ExceptionClass_ ((errorMsg_));           \
        }

#else

#define fatal(context_, ExceptionClass_, errorNum_, errorMsg_) \
                                                               \
        if ((context_)) {                                      \
                (context_)->addFatal ((errorNum_));            \
        }                                                      \
        else {                                                 \
                throw ExceptionClass_ ((errorMsg_));           \
        }

#endif

#if defined (TILIAE_DEBUG)

#define error(context_, ExceptionClass_, errorNum_, errorMsg_) \
                                                               \
        if ((context_)) {                                      \
                (context_)->addError ((errorMsg_));            \
        }                                                      \
        else {                                                 \
                throw ExceptionClass_ ((errorMsg_));           \
        }

#else

#define error(context_, ExceptionClass_, errorNum_, errorMsg_) \
                                                               \
        if ((context_)) {                                      \
                (context_)->addError ((errorNum_));            \
        }                                                      \
        else {                                                 \
                throw ExceptionClass_ ((errorMsg_));           \
        }

#endif


#endif /* CONTEXT_H_ */
