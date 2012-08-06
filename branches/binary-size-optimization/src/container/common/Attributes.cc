/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Attributes.h"

namespace Container {

Attributes::Attributes () : integerData (0)
{
        for (int i = 0; i < LAST_STRING; ++i) {
                strMapData[i] = NULL;
        }
}

/****************************************************************************/

void Attributes::setString (AttributeName key, const char *value)
{
        strMapData[key] = value;
}

/****************************************************************************/

const char *Attributes::getString (AttributeName key, bool getFromParent) const
{
        const char *ret = strMapData[key];

        if (ret) {
                return ret;
        }

        if (getFromParent && parent) {
                return parent->getString (key);
        }

        static const char *EMPTY = "";
        return EMPTY;
}

/****************************************************************************/

void Attributes::setInt (AttributeName key, int value)
{
        switch (key) {
        case ABSTRACT_ARGUMENT:
                integerData |= value & ABSTRACT_ARGUMENT_MASK;
                integerData |= ABSTRACT_ARGUMENT_SET;
                break;

        case LAZYINIT_ARGUMENT:
                integerData |= value & LAZYINIT_ARGUMENT_MASK;
                integerData |= LAZYINIT_ARGUMENT_SET;
                break;

        case SCOPE_ARGUMENT:
                integerData |= value & SCOPE_ARGUMENT_MASK;
                integerData |= SCOPE_ARGUMENT_SET;
                break;

        default:
                break;
        }
}

/****************************************************************************/

int Attributes::getIntPriv (AttributeName key) const
{
        switch (key) {
        case ABSTRACT_ARGUMENT:
                return (integerData & ABSTRACT_ARGUMENT_SET) ? (integerData & ABSTRACT_ARGUMENT_MASK) : (-1);

        case LAZYINIT_ARGUMENT:
                return (integerData & LAZYINIT_ARGUMENT_SET) ? (integerData & LAZYINIT_ARGUMENT_MASK) : (-1);

        case SCOPE_ARGUMENT:
                return (integerData & SCOPE_ARGUMENT_SET) ? (integerData & SCOPE_ARGUMENT_MASK) : (-1);

        default:
                return -1;
        }

        return -1;
}

/****************************************************************************/

int Attributes::getInt (AttributeName key, bool getFromParent) const
{
        int ret = getIntPriv (key);

        if (ret >= 0) {
               return ret;
        }

        if (getFromParent && parent) {
                return parent->getInt (key);
        }

        return -1;
}

/****************************************************************************/

bool Attributes::containsKey (AttributeName key, bool getFromParent) const
{
        bool foundInParent = false;

        if (getFromParent && parent) {
                foundInParent = parent->containsKey (key);
        }

        bool foundInChild = false;
        int iKey = static_cast <int> (key);

        if (iKey > 0 && iKey < LAST_STRING) {
                foundInChild = bool (strMapData[iKey]);
        }
        else if (iKey >= ABSTRACT_ARGUMENT && iKey <= SCOPE_ARGUMENT) {
                 foundInChild = ((iKey == ABSTRACT_ARGUMENT) && (integerData & ABSTRACT_ARGUMENT_SET)) ||
                                ((iKey == LAZYINIT_ARGUMENT) && (integerData & LAZYINIT_ARGUMENT_SET)) ||
                                ((iKey == SCOPE_ARGUMENT) && (integerData & SCOPE_ARGUMENT_SET));
        }

        return foundInChild || foundInParent;
}

}
