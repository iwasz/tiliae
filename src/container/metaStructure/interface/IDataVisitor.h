/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDATAVISITOR_H_
#define IDATAVISITOR_H_

#include <string>

namespace Container {
class ValueData;
class NullData;
class RefData;
class MetaObject;
class MetaContainer;
struct DataKey;

/**
 * Implementacja paternu Visitor. Ten visitor będzie odwiedzał
 * obiekty typu IData.
 * Visitor został zastosowany głównie po to, żeby nie zaśmiecać
 * klas metastruktury niepotrzebnymi metodami. Zależało mi, żeby
 * metastruktura była jak najprostsza, ponieważ ma się ją prosto
 * tworzyć i łatwo zrozumieć.
 * \ingroup Container
 */
struct IDataVisitor {

        virtual ~IDataVisitor () {}
        virtual void visit (DataKey const *dk, ValueData *data) = 0;
        virtual void visit (DataKey const *dk, NullData *data) = 0;
        virtual void visit (DataKey const *dk, RefData *data) = 0;
};

/**
 * Implementacja paternu Visitor. Ten visitor będzie odwiedzał
 * obiekty typu IMeta.
 * \ingroup Container
 */
struct IMetaVisitor {
        virtual ~IMetaVisitor () {}
        virtual void visit (MetaObject const *data) = 0;
};

/**
 * Odwiedza kontener. Mimo, ze kontener jest tylko jeden
 * to zostawiam ten Visitor, zeby nie zaśmiecać go kolejnymi
 * operacjami wykonywanymi na metastrukturze.
 * \ingroup Container
 */
struct IContainerVisitor {
        virtual ~IContainerVisitor () {}
        virtual void visit (MetaContainer *data) = 0;
};

}

#endif /* IDATAVISITOR_H_ */
