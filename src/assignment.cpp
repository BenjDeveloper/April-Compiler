#include "../headers/assignment.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april 
{
    Symbol* Assignment::codeGen(CodeGenContext& context)
    {
        if(!expr)
        {
            //error de expresion nula
        }
        if(!ident)
        {
            // error de identificardo nullo
        }

        Symbol* sym_expr = expr->codeGen(context);
        if (!sym_expr)
        {
            //erro por symbolo nullo - creacion 
        }

        Symbol* sym_ident = context.findIdentLocals(ident->getName());
        if (!sym_ident){
            //erro por symbolo nullo - busqueda
        }

        if ((sym_expr->type != sym_ident->type) && !(sym_expr->type == Type::DOUBLE && sym_ident->type == Type::INTEGER))
        {
            // error: el tipo de dato incompatible\n");
        }

        sym_ident->value = sym_expr->value;

        return sym_ident;
    }
}
