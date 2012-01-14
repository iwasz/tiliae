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
        REFLECTION_CONSTRUCTOR_ (void)

        virtual ~Book () {}

        std::string const &getIsbn () const { return isbn; }
        REFLECTION_METHOD (setIsbn) void setIsbn (std::string const &s) { isbn = s; }

        std::string const &getTitle () const { return title; }
        REFLECTION_METHOD (setTitle) void setTitle (std::string const &s) { title = s; }

        Ptr <Author> getAuthor () const { return author; }
        REFLECTION_METHOD (setAuthor) void setAuthor (Ptr <Author> a) { author = a; }

        std::string toString () const { return "Book [" + getTitle () + ", " + getAuthor()->toString () + "]"; }

private:

        std::string title;
        std::string isbn;
        Ptr <Author> author;

        REFLECTION_END (Book)
};

typedef std::vector <Ptr <Book> > BookVector;
REFLECTION_COLLECTION (BookVector)

#	endif /* BOOK_H_ */
