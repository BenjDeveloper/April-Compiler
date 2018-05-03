#include "../headers/identifier.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* Identifier::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = new Symbol{};
        tmp->name = name;
        tmp->type = Type::UNDEFINED;
        tmp->is_constant = false;

        context.getCurrentBlock()->locals.push_back(tmp);
        return tmp;
    }
}