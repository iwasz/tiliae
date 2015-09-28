#include "reflection/Reflection.h"
#include "core/variant/Variant.h"
#include "core/variant/Cast.h"

using namespace Core;

class __tiliae_reflect__ A {
public:
        REFLECTION_CONSTRUCTOR_ (void)
        virtual ~A () {}

        REFLECTION_METHOD (init) void init () {}

        REFLECTION_METHOD (getField) std::string const &getField () const { return field; }
        REFLECTION_METHOD (setField) void setField (std::string const &field) { this->field = field; }

        /// Szuka we wszystkich, zwraca pierwszy znaleziony.
        REFLECTION_METHOD (get) virtual Core::Variant get (const std::string &name) const
        {
                if (name == "name") {
                        return Variant (field);
                }
                else if (name == "pole.name") {
                        return Variant ("ala ma kota");
                }

                return Variant ();
        }

        /// Ustawia w transition.
        REFLECTION_METHOD (set) virtual void set (const std::string &name, const Core::Variant &object)
        {
                if (name == "name") {
                        field = vcast <std::string> (object);
                }
                else if (name == "pole.name") {
                        field = vcast <std::string> (object);
                }
        }

private:

       std::string field;

       REFLECTION_END (A)
};
