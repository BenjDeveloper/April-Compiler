#include <iostream>
#include "../headers/string.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april 
{
    Symbol* String::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = new Symbol();
        tmp->name = "";
        tmp->type = Type::STRING;
        tmp->value._sval = &value;
        tmp->is_constant = false;
        context.getCurrentBlock()->locals.push_back(tmp);
        return tmp;
    }

}