#include "../headers/identifier.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* Identifier::codeGen(CodeGenContext& context)
    {
        if (context.scope_type == Scope::BLOCK)
        {
            if (!context.existIdenLocals(name))
            {
                Symbol* tmp = new Symbol{};
                tmp->name = name;
                tmp->type = Type::UNDEFINED;
                tmp->is_constant = false;
                tmp->is_variable = true;
                
                context.getCurrentBlock()->locals.push_back(tmp);

                return tmp;
            }
                
            return context.findIdentLocals(name);
        }

        Symbol* tmp = new Symbol{};
        tmp->name = name;
        tmp->type = Type::UNDEFINED;
        tmp->is_constant = false;
        tmp->is_variable = true;
        
        context.getCurrentFunction()->getLocals().push_back(tmp);
        return tmp;
    }
}