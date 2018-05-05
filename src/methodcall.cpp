#include "../headers/methodcall.hpp"
#include "../headers/codegencontext.hpp"
#include <iostream>

namespace april 
{
    Symbol* MethodCall::codeGen(CodeGenContext& context)
    {
        for(Expression* expr: *args)
        {
            Symbol* tmp = expr->codeGen(context);
            if (tmp->is_variable)
                tmp = context.findIdentLocals(tmp->name);

            if (ident->getName() == "println")
                std::cout << ">> "<< *tmp << std::endl;
        }        
        return nullptr;
    }
}