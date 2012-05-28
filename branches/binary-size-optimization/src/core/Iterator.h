/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_ITERATOR_H_
#define TILIAE_ITERATOR_H_

#include "../core/variant/Variant.h"
#include "../core/Object.h"
#include "../core/ApiMacro.h"

namespace Core {

/**
 * Versy simple iterator facade. It implements only a forward iterator
 * and is read only. Interface.
 */
struct TILIAE_API IIterator : public Core::Object {
public:

        virtual ~IIterator () {}
        virtual Core::Variant next () const = 0;
        virtual bool hasNext () const = 0;
};

/**
 *
 */
template <typename Collection>
class TIterator : public IIterator {
public:

        typedef typename Collection::const_iterator Iterator;
        TIterator (Iterator const &b, Iterator const &e) : i (b), end (e) {}
        virtual ~TIterator () {}

        virtual Core::Variant next () const { return Core::Variant (*i++); }
        virtual bool hasNext () const { return i != end; };

private:

        mutable Iterator i;
        Iterator end;
};

}

#	endif /* ITERATOR_H_ */
