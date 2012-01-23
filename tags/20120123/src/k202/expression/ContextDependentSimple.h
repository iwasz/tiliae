/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PLACEHOLDER_H_
#define PLACEHOLDER_H_

#include "ExpressionCollection.h"
#include "IExpression.h"
#include "NArryExpression.h"
#include "../../core/variant/Variant.h"
#include "../../core/string/String.h"

namespace k202 {

/**
 * %0, %1 etc
 */
class Placeholder : public IExpression {
public:

        Placeholder (unsigned int p) : place (p) {}
        virtual ~Placeholder () {}

        static Ptr <Placeholder> create (unsigned int p) { return Ptr <Placeholder> (new Placeholder (p)); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Type <Core::Variant> type;
        unsigned int place;
};

/**
 * $kupa, ${kupa}, ${}, $!kupa
 * Domyślnie conditional jest false.
 */
class Property : public IExpression {
public:

        Property (const std::string & p, bool c = false) : property (p), conditional (c) {}
        virtual ~Property () {}

        static Ptr <Property> create (const std::string &p, bool c = false) { return Ptr <Property> (new Property (p, c)); }

        virtual std::string toString () const { return std::string ("Property (") + property + ")"; }
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }
        std::string getPath () const { return property; }

private:

        Type <Core::Variant> type;
        std::string property;
        bool conditional;
};

/**
 * $kupa (1, 2, 4)
 */
class Function : public NArryExpression {
public:

        Function (const std::string &name, unsigned int arity) : NArryExpression (arity), name (name) {}
        virtual ~Function () {}

        static Ptr <Function> create (const std::string &s, unsigned int arity) { return Ptr <Function> (new Function (s, arity)); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        std::string name;
        Type <Core::Variant> type;

};

}

#endif /* PLACEHOLDER_H_ */
