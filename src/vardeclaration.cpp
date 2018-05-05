#include <iostream>
#include "../headers/vardeclaration.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/assignment.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* VarDeclaration::codeGen(CodeGenContext& context)
    {
        
        if (context.existIdenLocals(ident->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' ya existe\n");
            context.addError();
            return nullptr;
        }

        ident->codeGen(context);
        Symbol*& symbol = context.findIdentLocals(ident->getName());
        if (context.typeOf(type->getName()) == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: typo de dato indefinido.\n");
            context.addError();
            return nullptr;
        }
        
        symbol->type = context.typeOf(type->getName());
        if (symbol->type == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de dato '"+type->getName()+"' no esta definido\n");
            context.addError();
            return nullptr;
        }

        symbol->is_variable = true;
        
        if (expr)
        {
            Assignment* assig = new Assignment{ident, expr};
            assig->codeGen(context);            
        }
        return symbol;
    }
}