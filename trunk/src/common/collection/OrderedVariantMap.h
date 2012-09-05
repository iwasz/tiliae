/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ORDEREDVARIANTMAP_H_
#define ORDEREDVARIANTMAP_H_

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <utility>
#include <string>
#include "../../core/Pointer.h"
#include "../../core/IToStringEnabled.h"
#include "../../core/variant/Variant.h"
#include "../../core/ApiMacro.h"

namespace Common {

/**
 * Special case of map, which basically is the same as
 * VariantMap (but is not std:: compliant) and it differs
 * in the way elements are ordered. In VariantMap you
 * have iterators in sorted order, they are sorted by the
 * key. Here you iterate in order of insertion.
 */
class TILIAE_API OrderedVariantMap : public Core::IToStringEnabled {
public:

        OrderedVariantMap () {}
        virtual ~OrderedVariantMap () {}

/*------Data types--------------------------------------------------*/

        typedef std::pair <std::string, Core::Variant> Elem;

        typedef boost::multi_index::multi_index_container<
                Elem,
                boost::multi_index::indexed_by<
                        // Jak mapa
                        boost::multi_index::ordered_non_unique<
                                boost::multi_index::member <Elem, std::string, &Elem::first>
                        >,
                        // Jak lista
                        boost::multi_index::sequenced<>
                >
        > Container;

        typedef Container::nth_index<0>::type::iterator Iterator0;
        typedef Container::nth_index<1>::type::iterator Iterator1;

        typedef Container::nth_index<1>::type::const_iterator const_iterator;

        const_iterator begin () const { return container.get <1> ().begin (); }
        Iterator1 begin () { return container.get <1> ().begin (); }

        const_iterator end () const { return container.get <1> ().end (); }
        Iterator1 end () { return container.get <1> ().end (); }

/*------IMap----------------------------------------------------------------*/

        virtual void clear ();

        virtual bool containsKey (const Core::Variant &key) const;
        virtual bool containsValue (const Core::Variant &value) const;

        virtual Core::Variant get (const Core::Variant &key) const;
        virtual void set (const Core::Variant &key, const Core::Variant &value);

        virtual void remove (const Core::Variant &key);

        virtual int size () const;
        virtual bool isEmpty () const;

        void insert (Elem const &e) { container.insert (e); }

/*------IToStringEnabled----------------------------------------------------*/

        virtual std::string toString () const;

/*------Convenience---------------------------------------------------------*/

        bool containsKey (const std::string &key) const;
        Core::Variant get (const std::string &key) const;
        void set (const std::string &key, const Core::Variant &value);
        void remove (const std::string &key);

private:

        Container container;

};

}

#endif /* ORDEREDVARIANTMAP_H_ */
