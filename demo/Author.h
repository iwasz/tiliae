/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef AUTHOR_H_
#define AUTHOR_H_

#include <string>
#include <map>
#include <string>
#include "../src/reflection/Reflection.h"
#include "../src/core/IToStringEnabled.h"
#include "Filters.h"

/**
 *
 */
class Author : public Core::IToStringEnabled {
public:
        __c (void)
        Author () : age (0) {}

        _c (std::string const &)
        Author (std::string const &s) : firstname (s), lastname (s), age (0) {}

        _c (std::string const &, std::string const &)
        Author (std::string const &f, std::string const &l) : firstname (f), lastname (l), age (0) {}

        virtual ~Author () {}

        std::string const &getFirstname () const { return firstname; }
        _m (setFirstname) void setFirstname (std::string const &s) { firstname = s; }

        std::string const &getLastname () const { return lastname; }
        _m (setLastname) void setLastname (std::string const &s) { lastname = s; }

        int getAge () const { return age; }
        _m (setAge) void setAge (int i) { age = i; }

        Ptr <IFilter> getFilter () const { return filter; }
        _s (setFilter) void setFilter (Ptr <IFilter> f) { filter = f; }

        std::string toString () const
        {
                std::string s = "Author [" + getFirstname () + " " + getLastname () +
                                ", age : " + boost::lexical_cast <std::string> (age) + "]";

                if (filter) {
                        s = filter->filter (s);
                }

                return s;
        }

private:

        std::string firstname;
        std::string lastname;
        int age;

        // It's short for boost::shared_ptr.
        Ptr <IFilter> filter;

        _e (Author)
};

typedef std::map <std::string, Ptr <Author> > AuthorMap;
_g (AuthorMap)


#	endif /* AUTHOR_H_ */
