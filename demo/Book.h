/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include "../src/reflection/Reflection.h"
#include "../src/core/Pointer.h"
#include "../src/core/IToStringEnabled.h"
#include "Author.h"

class Book : public Core::IToStringEnabled {
public:
        c__ (void)

        virtual ~Book () {}

        std::string const &getIsbn () const { return isbn; }
        m_ (setIsbn) void setIsbn (std::string const &s) { isbn = s; }

        std::string const &getTitle () const { return title; }
        m_ (setTitle) void setTitle (std::string const &s) { title = s; }

        Ptr <Author> getAuthor () const { return author; }
        m_ (setAuthor) void setAuthor (Ptr <Author> a) { author = a; }

        std::string toString () const { return "Book [" + getTitle () + ", " + getAuthor()->toString () + "]"; }

private:

        std::string title;
        std::string isbn;
        Ptr <Author> author;

        e_ (Book)
};

typedef std::vector <Ptr <Book> > BookVector;
g_ (BookVector)

#	endif /* BOOK_H_ */
