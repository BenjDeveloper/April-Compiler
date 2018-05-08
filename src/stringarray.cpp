#include "../headers/stringarray.hpp"
#include "../headers/codegencontext.hpp"

namespace
{
    Symbol* StringArray::codeGen(CodeGenContext& context)
    {

        Symbol* sym_ident = context.findIdentLocals(ident_var->getName());
        if (!(sym_ident))
        {
            // el variable no existe
        }

        if (num > (sym_ident->v)
        {

        }

        return nullptr;
    };
}