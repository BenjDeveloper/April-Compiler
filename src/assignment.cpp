#include "../headers/assignment.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Assignment::~Assignment()
    {
        
    }

    Symbol* Assignment::codeGen(CodeGenContext& context)
    {
        if (ident == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: identificador nulo en la operacion de asignacion.\n");
            context.addError();
            return nullptr;
        }
       
        if (ident != nullptr && !context.existIdenLocals(ident->getName()))
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

        symbol->prox = sym_expr->prox;
        symbol->down = sym_expr->down;

        return symbol; //devuelve la expresion OJO
    }
}