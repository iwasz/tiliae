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
#include "ApiMacro.h"

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
        virtual ~Exception () throw () {}

        /**
         * Czyści stos wiadomości i ustawia m jako pierwszą wiadomość.
         */
        void setMessage (std::string const &m);

        /**
         * Dodaje wiadomość na stos.
         */
        void addMessage (std::string const &m);

        /**
         * Zwraca stos wiadomości w postaci napisu rozdzielonego znakami
         * nowej linii. Każda wiadomość jest poprzedzona swoim numerkiem
         * porządkowym.
         */
        const char* what() const throw () { return message.c_str (); }

private:

        std::string message;
        int msgCount;
};

}

#	endif /* EXCEPTION_H_ */
