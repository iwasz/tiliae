/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>
#include "core/ApiMacro.h"
#include "core/DebugContext.h"

namespace Core {

/**
 * Klasa bazowa dla wyjątków w Core.
 * \ingroup CoreAPI
 */
class TILIAE_API Exception : public std::exception {
public:

        /**
         * Inicjuje wyjątek napisem.
         */
        Exception (std::string const &s = "");
        Exception (DebugContext const &db, std::string const &s = "");
        virtual ~Exception () throw () {}

        /**
         * Dodaje wiadomość na stos.
         */
        void addMessage (std::string const &m);
        void addContext (DebugContext const &dc);

        const char* what() const throw ();

        /**
         * Zwraca stos wiadomości w postaci napisu rozdzielonego znakami
         * nowej linii. Każda wiadomość jest poprzedzona swoim numerkiem
         * porządkowym.
         */
        std::string getMessage () const { return ctx.getMessage (); }
        DebugContext const &getContext () const { return ctx; }

private:

        DebugContext ctx;
        static std::string whatCopy;

};

}

#	endif /* EXCEPTION_H_ */
