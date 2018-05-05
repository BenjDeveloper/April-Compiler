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
                else if (tmp->type == Type::STRING)
                {
                    std::cout<< "Type::STRING "<<tmp->name<< std::endl;
                    std::cout<< tmp->value._sval->c_str() <<std::endl;
                }else{
                    std::cout<< "ELSE ->"<<tmp->name<< std::endl;
                }
            }
        }        
        return nullptr;
    }
}