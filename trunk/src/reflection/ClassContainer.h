/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLASSCONTAINER_H_
#define CLASSCONTAINER_H_

#include <map>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include "model/Class.h"
#include "model/Constructor.h"
#include "model/Method.h"
#include "IClassContainer.h"
#include "core/Pointer.h"
#include "core/string/String.h"

namespace Reflection {

typedef boost::multi_index::multi_index_container<
        Class *, // Element type

        boost::multi_index::indexed_by<
                boost::multi_index::ordered_unique< // Dodać funkcję haszującą, albo coś i hash_unique
                        boost::multi_index::const_mem_fun <Class, std::string, &Class::getName>
                >
        >
>
Multi;

/**
 *
 */
struct ClassContainer : public IClassContainer {

        virtual ~ClassContainer ();

        Class *get (const std::string &className) const;
        Class *get (std::type_info const &t) const;

        bool add (Class *clazz);
        std::string toString () const;

private:

        Multi body;
        typedef std::map <std::type_info const *, Class *> TypeMap;
        TypeMap typeMap;
};

}

#	endif /* CLASSCONTAINER_H_ */
