#include "../headers/for.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* For::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
        Symbol* result = nullptr;
        
        block->type_scope = BlockScope::FOR;
        block->prev = context.getCurrentBlock();
        context.setCurrentBlock(block);
       
        while (sym_expr->value._bval && !block->stop)
        {

            result = block->codeGen(context);
            if (!block->stop)
                sym_expr = expr->codeGen(context);
        }

        block->stop = false;
        context.popCurrentBlock();
        // if (result == nullptr)
        //     std::cout << "result es NULO (FOR)" << std::endl;
        // else
        //     std::cout << "result (FOR): " << *result << std::endl;

        return result;     
    }
}