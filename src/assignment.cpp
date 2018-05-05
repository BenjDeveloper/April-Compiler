#include "../headers/assignment.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_error;

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
        Symbol* symbol_expr = expr->codeGen(context);
        if (!symbol_expr){
            //erro por symbolo nullo - creacion 
        }
        Symbol* symbol_ident = context.findIdentLocals(ident->getName());
        if (!symbol_ident){
            //erro por symbolo nullo - busqueda
        }

        Symbol* tmp = expr->codeGen(context);
        if ((symbol->type != tmp->type) && !(symbol->type == Type::DOUBLE && tmp->type == Type::INTEGER))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de dato incompatible\n");
            context.addError();
            return nullptr;
        }
        symbol->value = tmp->value;

        if (symbol_expr->type == symbol_ident->type)
            symbol_expr->value = symbol_ident->value;

        return symbol_expr;
    }
}
