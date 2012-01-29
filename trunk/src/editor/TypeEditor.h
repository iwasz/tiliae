/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TYPEEDITOR_H_
#define TYPEEDITOR_H_

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include "IEditor.h"
#include "../core/ApiMacro.h"

namespace Editor {

/**
 * Edytor umożliwiający automatyczne konwersje na podstawie typów.
 */
class TILIAE_API TypeEditor : public IEditor {
public:

        virtual ~TypeEditor () {}
        virtual void convert (const Core::Variant &input, Core::Variant *output, bool *error = NULL, Core::DebugContext *context = NULL);

        /**
         * Edytor używany w przypadku kiedy typy warianta input i output są
         * takie same.
         */
        Ptr <IEditor> getEqType () const { return eqType; }
        void setEqType (Ptr <IEditor> e) { eqType = e; }

        /**
         * Edytor, ktory zostanie użyty kiedy input jest typu Variant::NIL.
         */
        Ptr <IEditor> getNullType () const { return nullType; }
        void setNullType (Ptr <IEditor> e) { nullType = e; }

        /**
         * Typ elementu dla multi_index. Raczekj nie da się tego używać jak mapy, że
         * klucze są osobno, a wartość osobno, tylko bardziej jako set i list.
         */
        struct Type {
                std::type_info const *inputType;
                std::type_info const *outputType;
                Ptr <Editor::IEditor> editor;

                Type (std::type_info const *i, std::type_info const *o, Ptr <Editor::IEditor> e) :
                        inputType (i),
                        outputType (o),
                        editor (e) {}

                Type (std::type_info const &i, std::type_info const &o, Ptr <Editor::IEditor> e) :
                        inputType (&i),
                        outputType (&o),
                        editor (e) {}
        };

        void addType (Type const &t)
        {
                container.insert (t);
        }

private:

        /**
         * Typ kolekcji trzymającej obiekty Type. Indeksowany jest dwoma wskaźnikami do
         * type_info.
         */
        typedef boost::multi_index::multi_index_container<
                Type,
                boost::multi_index::indexed_by<
                        boost::multi_index::ordered_unique<
                                boost::multi_index::composite_key<
                                        Type,
                                        boost::multi_index::member <Type, std::type_info const *, &Type::inputType>,
                                        boost::multi_index::member <Type, std::type_info const *, &Type::outputType>
                                >
                        >
                >
        > Container;

        Ptr <IEditor> findEditor (std::type_info const *inputType, std::type_info const *outputType) const;

private:

        Ptr <IEditor> eqType;
        Ptr <IEditor> nullType;
        Container container;

};

}

#	endif /* TYPEEDITOR_H_ */
