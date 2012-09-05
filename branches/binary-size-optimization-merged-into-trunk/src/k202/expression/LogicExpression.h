/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LOGIC_EXPRESSION_H
#define LOGIC_EXPRESSION_H

#include "ExpressionCollection.h"
#include "IExpression.h"
#include "NArryExpression.h"

namespace k202 {

/**
 * op==
 */
class LogicEq : public NArryExpression {
public:

        LogicEq () : NArryExpression (2) {}
        virtual ~LogicEq () {}

        static Ptr <LogicEq> create () { return Ptr <LogicEq> (new LogicEq ()); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Type <bool> type;
};

/**
 * op!=
 */
class LogicNe : public NArryExpression {
public:

        LogicNe () : NArryExpression (2) {}
        virtual ~LogicNe () {}

        static Ptr <LogicNe> create () { return Ptr <LogicNe> (new LogicNe ()); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Type <bool> type;
};

/**
 * op&&
 */
class LogicAnd : public NArryExpression {
public:

        LogicAnd () : NArryExpression (2) {}
        virtual ~LogicAnd () {}

        static Ptr <LogicAnd> create () { return Ptr <LogicAnd> (new LogicAnd ()); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Type <bool> type;
};

/**
 * op||
 */
class LogicOr : public NArryExpression {
public:

        LogicOr () : NArryExpression (2) {}
        virtual ~LogicOr () {}

        static Ptr <LogicOr> create () { return Ptr <LogicOr> (new LogicOr ()); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Type <bool> type;
};

/**
 * op!
 */
class LogicNegation : public NArryExpression {
public:

        LogicNegation () : NArryExpression (1) {}
        virtual ~LogicNegation () {}

        static Ptr <LogicNegation> create () { return Ptr <LogicNegation> (new LogicNegation ()); }

        virtual std::string toString () const;
        virtual Core::Variant evaluate (Context *);

        const IType *getType () const { return &type; }

private:

        Type <bool> type;
};

}

#endif /* PLACEHOLDER_H_ */
