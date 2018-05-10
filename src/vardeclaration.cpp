#include <iostream>
#include "../headers/vardeclaration.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/assignment.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    VarDeclaration::~VarDeclaration()
    {
        std::cout << "des varde" << std::endl;
        if (type != nullptr)
            delete type;
        
        if (ident != nullptr)
            delete ident;

        if (expr != nullptr)
            delete expr;
    }

    Symbol* VarDeclaration::codeGen(CodeGenContext& context)
    {
        Symbol* symbol = nullptr;
        if ((context.scope_type == Scope::BLOCK)?(context.existIdenLocals(ident->getName())):(context.getCurrentFunction()->existIdenLocals(ident->getName()))  )
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        ident->codeGen(context);
        if (context.scope_type == Scope::BLOCK)
            symbol = context.findIdentLocals(ident->getName());
        else
            symbol = context.getCurrentFunction()->existIdenLocals(ident->getName());

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
            symbol = assig->codeGen(context);            
        }
        //std::cout<< "VARDECLARATION -> "<< symbol->name <<" - "<< *symbol <<std::endl;
        
        return symbol;
    }
}