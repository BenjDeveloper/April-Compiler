#include "../include/vardeclarationdeduce.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

namespace april
{
    llvm::Value* VariableDeclarationDeduce::codeGen(CodeGenContext& context)
    {
        llvm::Value* expr_value = expr->codeGen(context);
        llvm::Type* type = nullptr;
        
        if (expr_value->getType()->isIntegerTy())
        {
            type = llvm::Type::getInt64Ty(context.getGlobalContext());      
        }
        else if (expr_value->getType()->isDoubleTy())
        {
            std::cout << "entro nena" << std::endl;
            type = llvm::Type::getDoubleTy(context.getGlobalContext());      
        }
        else
        {
            std::cout << "-->shit!!" << std::endl;
        }
        

        llvm::AllocaInst* alloc = new llvm::AllocaInst(type, id.name.c_str(), context.currentBlock());

        context.locals()[id.name] = alloc;
        Assignment assn(id, *expr, expr_value);
        assn.codeGen(context);
        return alloc;
    }
}