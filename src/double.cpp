#include "../headers/double.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* Double::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = new Symbol();
        tmp->name = "";
        tmp->type = Type::DOUBLE;
        tmp->value._dval = value;
        tmp->is_constant = true;

        context.getCurrentBlock()->locals.push_back(tmp);
        return tmp;
    }
}