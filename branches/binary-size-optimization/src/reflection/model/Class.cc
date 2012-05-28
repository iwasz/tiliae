/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Class.h"
#include "Tools.h"
#include "Exceptions.h"
#include "Manager.h"
#include <algorithm>
#include "../../core/Typedefs.h"
#include "../Exceptions.h"

using namespace Core;

namespace Reflection {

void Class::initBaseClasses ()
{
        if (!Manager::getInit ()) {
                throw ManagerNotInitializedException ("For class name : " + name);
        }

        foreach (std::string name, baseClassNames) {
                Ptr <Class> c = Manager::classForName (name);

                if (!c) {
                        throw NoSuchBaseClassException (name);
                }

                baseClassList.push_back (c);
        }

        initialized = true;
}

/****************************************************************************/

void Class::initWithCheck ()
{
        if (initialized) {
                return;
        }

        initBaseClasses ();
}

/****************************************************************************/

ClassList Class::getBaseClassList() const
{
        (const_cast <Class *> (this))->initWithCheck ();
        return baseClassList;
}

/****************************************************************************/

void Class::addBaseClassNames (const Core::StringList &names)
{
        std::copy (names.begin (), names.end (), std::back_inserter (baseClassNames));
}

/****************************************************************************/

const MethodList &Class::getMethodList () const
{
        (const_cast <Class *> (this))->initWithCheck ();
        return methodList;
}

/****************************************************************************/

Ptr <Method> Class::getMethod (const std::string &s, std::type_info const &ti) const
{
        (const_cast <Class *> (this))->initWithCheck ();

        for (MethodList::const_iterator i = methodList.begin (); i != methodList.end (); ++i) {
            if ((*i)->getName () == name && (*i)->getType() == ti) {
                    return *i;
            }
        }

        for (ClassList::const_iterator i = baseClassList.begin (); i != baseClassList.end (); ++i) {
            Ptr <Method> m = (*i)->getMethod (name, ti);

            if (m) {
                    return m;
            }
        }

        return Ptr <Method> ();
}

/****************************************************************************/

Ptr<Method> Class::getMethod (const std::string &name, int arity) const
{
        (const_cast <Class *> (this))->initWithCheck ();

        for (MethodList::const_iterator i = methodList.begin (); i != methodList.end (); ++i) {
            if ((*i)->getName () == name && (arity == -1 || (*i)->getArity () == arity)) {
                    return *i;
            }
        }

        for (ClassList::const_iterator i = baseClassList.begin (); i != baseClassList.end (); ++i) {
            Ptr <Method> m = (*i)->getMethod (name, arity);

            if (m) {
                    return m;
            }
        }

        return Ptr <Method> ();
}

/****************************************************************************/

Ptr<Constructor> Class::getConstructor (std::type_info const &type) const
{
        // Jeśli podano jednak jakieś typy, t dopasuj
        foreach (Ptr<Constructor> ctr, constructorList) {
                if (ctr->getType () == type) {
                        return ctr;
                }
        }

        return Ptr<Constructor> ();
}

/****************************************************************************/

Ptr<Constructor> Class::getConstructor (unsigned int noOfArgs) const
{
        foreach (Ptr<Constructor> ctr, constructorList) {
                if (ctr->getArity () == noOfArgs) {
                        return ctr;
                }
        }

        return Ptr<Constructor> ();
}

/****************************************************************************/

std::string Class::toString () const
{
        return "Class (name:'" + name + "')";
}

}
