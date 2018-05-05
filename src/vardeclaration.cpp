#include <iostream>
#include "../headers/vardeclaration.hpp"
#include "../headers/codegencontext.hpp"

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
            Symbol* tmp = expr->codeGen(context);
            
            if ((symbol->type != tmp->type) && !(symbol->type == Type::DOUBLE && tmp->type == Type::INTEGER))
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de dato incompatible\n");
                context.addError();
                return nullptr;
            }
            
            symbol->value = tmp->value;
        }

        //std::cout << "alloc: " << *symbol << std::endl;
        return symbol;
    }
}