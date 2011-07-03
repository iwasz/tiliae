/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAPPING_H_
#define MAPPING_H_

#include <String.h>
#include <StringList.h>
#include <List.h>

#include "../IEditor.h"
#include "IRule.h"
#include "RuleList.h"
#include "PathPair.h"

namespace Editor {

/**
 * Na mapping proponuje cos takiego (Mapping jest uzywany w MappedEditor).
 * TODO nie wiem jak to sie bedzie konfigurowac - moze jakas zgrabna mapa?
 */
class Mapping {
public:

        typedef std::pair <Core::StringList, Core::StringList> ListPair;

        Mapping (RuleList *rl = NULL) : ruleList (rl) {}
        virtual ~Mapping () {}

        /**
         * To ma byc wywolane, kiedy pola tego obiektu beda
         * poustawiane. Przyporzadkuje jedne do drugich, zeby
         * metody get zwracaly to co trzeba.
         */
//        virtual void init ();

        /**
         * Zwraca ścieżkę wy. dla zadanej ścieżki we.
         */
        PathPair getOutputPath (const Core::String &input) const;

        /**
         * Zwraca edytor towarzyszący danej ścieżce inputPath
         * lub NULL. Działa w ten sposób, że odpytuje pokolei
         * wszsytkie reguły używając ich metody getEditor. Jeśli
         * którać zwróci wskaźnik nie NULL, to zostanie on
         * zwrócony. Jeśli dwie reguły zwracają dla danej ścieżki
         * edytor nie NULL, to zwrócony zostanie pierwszy.
         */
        IEditor *getEditor (const Core::String &inputPath) const;

        /**
         * Zwraca listę wszystkich ścieżek input:output, które zwracają reguły.
         * Nie muszą to być wszystkie ścieżki akceptowane przez edytor.
         * Są (będą) reguły, ktore zwracają pustą listę ścieżek input
         * Paths. Na przykład reguła, która mapuje 1:1.
         */
        ListPair getInputOutputPaths () const;

        /**
         * Lista reguł.
         */
        RuleList *getRuleList () const { return ruleList; }

        /**
         * Lista reguł.
         */
        void setRuleList (RuleList *ruleList) { this->ruleList = ruleList; }

/*--------------------------------------------------------------------------*/

private:

        RuleList *ruleList;

};

}

#endif /* MAPPING_H_ */
