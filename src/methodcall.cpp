#include "../headers/methodcall.hpp"
#include <iostream>

namespace april 
{
    Symbol* MethodCall::codeGen(CodeGenContext& context)
    {
        for(Expression* expr: *args)
        {
            Symbol* tmp = expr->codeGen(context);
            if (ident->getName() == "println")
            {
                if (tmp->type == Type::INTEGER)
                    std::cout<< tmp->value._ival <<std::endl;
                else if (tmp->type == Type::DOUBLE)
                    std::cout<< tmp->value._dval <<std::endl;
            }

        }        

        return nullptr;
    }
}