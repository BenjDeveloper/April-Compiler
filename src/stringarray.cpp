#include "../headers/stringarray.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* StringArray::codeGen(CodeGenContext& context)
    {

        Symbol* sym_ident = context.findIdentLocals(ident_var->getName());
        if (!(sym_ident))
        {
            // el variable no existe
        }

        if (num > (sym_ident->value._sval)->length())
        {

        }

        return nullptr;
    };
}