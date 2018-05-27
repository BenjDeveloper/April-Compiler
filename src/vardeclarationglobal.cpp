#include "../headers/vardeclarationglobal.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    VarDeclarationGlobal::~VarDeclarationGlobal()
    {
        if (ident != nullptr)
        {
            delete ident;
            ident = nullptr;
        }

        if (type != nullptr)
        {
            delete type;
            type = nullptr;
        }

        if (expr != nullptr)
        {
            delete expr;
            expr = nullptr;
        }
    }

    Symbol* VarDeclarationGlobal::codeGen(CodeGenContext& context)
    {
        if (context.scope_type != Scope::BLOCK)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: las variable globales deben declarase en el ambito principal.\n");
            context.addError();
            return nullptr;
        }

        if (context.existIdenGlobals(ident->getName()) != nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable global '"+ident->getName()+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        if (context.typeOf(type->getName()) == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipo de dato indefinido.\n");
            context.addError();
            return nullptr;
        }

        Type tmp_type = context.typeOf(type->getName());
        Symbol* sym_expr = expr->codeGen(context);
        if (sym_expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula en asignacion global.\n");
            context.addError();
            return nullptr;
        }

        if ((tmp_type != sym_expr->type) && !(tmp_type == Type::DOUBLE && sym_expr->type == Type::INTEGER))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede establecer la asignacion, tipos de datos distintos.\n");
            context.addError();
            return nullptr;
        }
        
        Symbol* sym = new Symbol{};
        sym->name = ident->getName();
        sym->type = tmp_type;
        
        if (sym->type == Type::DOUBLE && sym_expr->type == Type::INTEGER)
            sym->value._dval = sym_expr->value._ival;
        else
            sym->value = sym_expr->value;

        sym->is_constant = false;
        sym->is_variable = true;
        sym->prox = sym_expr->prox;
        sym->down = sym_expr->down;
        context.getGlobals().push_back(sym);


        return sym;
    }
}