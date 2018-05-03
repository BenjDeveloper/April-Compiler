#include <iostream>
#include "../headers/vardeclaration.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* VarDeclaration::codeGen(CodeGenContext& context)
    {
        
        if (context.findIdentLocals(ident->getName()) != nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident->getName()+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        ident->codeGen(context);
        type->codeGen(context);

        Symbol* symbol = context.findIdentLocals(ident->getName());
        symbol->type = context.typeOf(type->getName());
    }
}