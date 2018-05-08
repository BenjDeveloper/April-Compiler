#include <vector>
#include "../headers/if.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* If::codeGen (CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
        if (sym_expr->type != Type::BOOLEAN)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la expresion no es un boolean.\n");
            context.addError();
            return nullptr;
        }
        std::vector<Symbol*> tmp_locals = context.getCurrentBlock()->locals;
    
        if (sym_expr->value._bval == true)
        {
            context.setCurrentBlock(_then);
            
            context.getCurrentBlock()->locals = tmp_locals;

            _then->codeGen(context);
            context.setCurrentBlock(context.getStackBlock().top());
        }
        else if (_else != nullptr) 
        {
            context.setCurrentBlock(_else);
            context.getCurrentBlock()->locals = tmp_locals;
            
            _else->codeGen(context);
            context.setCurrentBlock(context.getStackBlock().top());
        }

        context.getCurrentBlock()->locals = tmp_locals;
        return nullptr;
    }
}