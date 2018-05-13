#include "../headers/vardeclarationdeduce.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    VarDeclarationDeduce::~VarDeclarationDeduce()
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
    }

    Symbol* VarDeclarationDeduce::codeGen(CodeGenContext& context)
    {
        if (context.existIdenLocals(ident->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' ya existe.\n");
            context.addError();
            return nullptr;
        }
        Symbol* sym_expr = expr->codeGen(context);
        if (sym_expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula.\n");
            context.addError();
            return nullptr; 
        }
        if (sym_expr->type == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de dato no esta definido.\n");
            context.addError();
            return nullptr;
        }

        Symbol* sym = new Symbol{};
        sym->name = ident->getName();
        sym->type = sym_expr->type;
        sym->is_variable = true;
        sym->is_constant = false;
        sym->value = sym_expr->value;
        sym->prox = sym_expr->prox;
        context.getCurrentBlock()->locals.push_back(sym);

        return sym;
    }
}