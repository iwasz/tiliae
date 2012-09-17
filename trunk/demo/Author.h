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
#include "reflection/Reflection.h"
#include "core/IToStringEnabled.h"
#include "Filters.h"

/**
 *
 */
class Author : public Core::IToStringEnabled {
public:
        REFLECTION_CONSTRUCTOR_ (void)
        Author () : age (0), filter (NULL) {}

        REFLECTION_CONSTRUCTOR (std::string const &)
        Author (std::string const &s) : firstname (s), lastname (s), age (0), filter (NULL) {}

        REFLECTION_CONSTRUCTOR (std::string const &, std::string const &)
        Author (std::string const &f, std::string const &l) : firstname (f), lastname (l), age (0), filter (NULL) {}

        virtual ~Author () {}

        std::string const &getFirstname () const { return firstname; }
        REFLECTION_METHOD (setFirstname) void setFirstname (std::string const &s) { firstname = s; }

        std::string const &getLastname () const { return lastname; }
        REFLECTION_METHOD (setLastname) void setLastname (std::string const &s) { lastname = s; }

        int getAge () const { return age; }
        REFLECTION_METHOD (setAge) void setAge (int i) { age = i; }

        IFilter *getFilter () const { return filter; }
        REFLECTION_SETTER (setFilter) void setFilter (IFilter *f) { filter = f; }

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
        IFilter *filter;

        REFLECTION_END (Author)
};

typedef std::map <std::string, Author *> AuthorMap;
REFLECTION_COLLECTION (AuthorMap)


#	endif /* AUTHOR_H_ */
