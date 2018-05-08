#include "../headers/for.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* For::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
        // std::vector<Symbol*> tmp_locals = context.getCurrentBlock()->locals;
        
        block->prev = context.getCurrentBlock();
        context.setCurrentBlock(block);
       
        while (sym_expr->value._bval)
        {
            // context.getCurrentBlock()->locals = tmp_locals;
            block->codeGen(context);
            sym_expr = expr->codeGen(context);
        }
        context.popCurrentBlock();
        return nullptr;     
    }
}