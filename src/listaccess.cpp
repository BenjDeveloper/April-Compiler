#include "../headers/listaccess.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    ListAccess::~ListAccess()
    {
        if (ident != nullptr)
        {
            delete ident;
            ident = nullptr;
        }

        if (expr != nullptr)
        {
            delete expr;
            expr = nullptr;
        }

        if (expr_index != nullptr)
        {
            delete expr_index;
            expr_index = nullptr;
        }
    }

    Symbol* ListAccess::codeGen(CodeGenContext& context)
    {       
        if (ident == nullptr && expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: ident y expr no definidos.\n");
            context.addError();
            return nullptr;
        }

        if (ident != nullptr && !context.existIdenLocals(ident->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' no existe.\n");
            context.addError();
            return nullptr;
        }

           
        Symbol* sym_expr = nullptr;
        Symbol* sym_index = expr_index->codeGen(context);
        if (sym_index->type != Type::INTEGER)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el indice debe ser entero.\n");
            context.addError();
            return nullptr;
        }

        if (ident != nullptr) { sym_expr = context.findIdentLocals(ident->getName()); }
        else {sym_expr = expr->codeGen(context);}
        if (sym_expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la evaluacion de la expresion es nula en la lista.\n");
            context.addError();
            return nullptr;
        }

        if (sym_expr->type != Type::LIST)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo no es una lista.\n");
            context.addError();
            return nullptr;
        }

        int i = 0; 
        sym_expr = sym_expr->prox;
        for (; i < sym_index->value._ival && sym_expr != nullptr; i += 1)
            sym_expr = sym_expr->prox;
        
        if (sym_expr == nullptr && i != sym_index->value._ival)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: indice fuera del rango.\n");
            context.addError();
            return nullptr;
        }

        if (sym_expr->type == Type::LIST_DOWN && sym_expr->down != nullptr)
            sym_expr = sym_expr->down;

        return sym_expr;
    }
};