#include <iostream>
#include "../headers/vardeclaration.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/assignment.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* VarDeclaration::codeGen(CodeGenContext& context)
    {
        if(ident)
        {
            //mala inicializacion
        }

        if(type)
        {
            //mala inicializacion
        }
        
        if (context.findIdentLocals(ident->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' ya existe\n");
            context.addError();
            return nullptr;
        }

        ident->codeGen(context);
        Symbol* symbol = context.findIdentLocals(ident->getName());
        symbol->type = context.typeOf(type->getName());
        symbol->is_variable = true;
        
        if (symbol->type == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de dato '"+type->getName()+"' no esta definido\n");
            context.addError();
            return nullptr;
        }

        if (expr)
        {
            Assignment assig = Assignment(ident,expr);
            assig.codeGen(context);  
        }

        Symbol* tmp = context.findIdentLocals(ident->getName());

        return symbol;
    }
}