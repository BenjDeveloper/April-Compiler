#include "../include/return.hpp"
#include "../include/codegencontext.hpp"

namespace april
{
    llvm::Value* Return::codeGen(CodeGenContext& context)
    {
        if (expr != nullptr)
        {
            llvm::Value* expr_value = expr->codeGen(context);
            if (expr_value == nullptr) { return nullptr; }
            return llvm::ReturnInst::Create(context.getGlobalContext(), expr_value, context.currentBlock());            
        }
        else
        {
            return llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
        }
    }
}