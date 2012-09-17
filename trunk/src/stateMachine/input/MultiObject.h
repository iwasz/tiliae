/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MULTIOBJECT_H_
#define MULTIOBJECT_H_

#include "IObject.h"
#include <map>
#include "core/variant/Variant.h"
#include "core/string/String.h"

namespace StateMachine {

/**
 * To mapuje znów tylko jeden int, ale przyrównuje go nie do jednej
 * wartości jak IntObject, ale do całego zestawu wartości. Każdej
 * z wartości odpowiada jeden virtual input do maszyny.
 *
 * Uwaga, obiekt object nie jest zainincjowany na poczatku!
 * \ingroup StateMachine
 */
template <typename KeyType>
class MultiObject : public IObject {
public:

        typedef typename std::map <KeyType, Core::Variant> MapType;

        virtual ~MultiObject () {}

        virtual Core::VariantMap run () const;

        std::string getName () const { return name; }
        void setName (const std::string &name) { this->name = name; }

        KeyType getObject () const { return object; }
        void setObject (KeyType object) { this->object = object; }

        MapType const &getMatches () const { return matches; }
        void setMatches (const MapType &matches) { this->matches = matches; }

private:

        std::string name;
        KeyType object;
        MapType matches;

};

/****************************************************************************/

template <typename KeyType>
Core::VariantMap MultiObject <KeyType>::run () const
{
        Core::VariantMap ret;

        typename MapType::const_iterator i = matches.find (getObject ());

//        TODO pogubiłem się - nie wiem co to ma robić, więc zkomentowałem.
//        if (i != matches.end ()) {
//                ret.set (i->second);
//        }

        return ret;
}

/****************************************************************************/

typedef MultiObject <int> MultiIntObject;
typedef MultiObject <std::string> MultiStrObject;

} // nam

#endif /* MULTIOBJECT_H_ */
