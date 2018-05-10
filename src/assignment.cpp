#include "../headers/assignment.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* Assignment::codeGen(CodeGenContext& context)
    {
        if (!(context.existIdenLocals(ident->getName())))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' no definida.\n");
            context.addError();
            return nullptr;
        }

        Symbol* symbol = context.findIdentLocals(ident->getName());
        Symbol* sym_expr = expr->codeGen(context);

        if ((symbol->type != sym_expr->type) && !(symbol->type == Type::DOUBLE && sym_expr->type == Type::INTEGER))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede establecer la asignacion, tipos de datos distintos.\n");
            context.addError();
            return nullptr;
        }

        if (symbol->type == Type::DOUBLE && sym_expr->type == Type::INTEGER)
            symbol->value._dval = sym_expr->value._ival;
        else
            symbol->value = sym_expr->value;
        
        //std::cout <<*sym_expr<< " " << *symbol<< std::endl;


        return symbol;
    }
}