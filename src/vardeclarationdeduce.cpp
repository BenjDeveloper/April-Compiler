#include "../include/vardeclarationdeduce.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

namespace april
{
    llvm::Value* VariableDeclarationDeduce::codeGen(CodeGenContext& context)
    {
        if (context.locals().find(id.name) != context.locals().end())
        {
            std::cout << "la variable ya existe, no se puede declarar de nuevo" << std::endl;
            exit(1);
        }

        llvm::Value* expr_value = expr->codeGen(context);
        llvm::Type* type = nullptr;
        char* name;
        if (expr_value->getType()->isIntegerTy())
        {
            if (expr->getType() == Type::boolean)
            {
                type = llvm::Type::getInt1Ty(context.getGlobalContext());      
                name = "bool";
            }
            else
            {
                type = llvm::Type::getInt64Ty(context.getGlobalContext());      
                name = "integer";
            }
        }
        else if (expr_value->getType()->isDoubleTy())
        {
            type = llvm::Type::getDoubleTy(context.getGlobalContext());      
            name = "float";    
        }
        else
        {
            std::cout << "-->shit!!" << std::endl;
        }
        

        llvm::AllocaInst* alloc = new llvm::AllocaInst(type, id.name.c_str(), context.currentBlock());
        std::cout << "---> Creating variable declaration " << name  << ", " << id.name << std::endl;
        context.locals()[id.name] = alloc;
        Assignment assn(id, *expr, expr_value);
        assn.codeGen(context);
        return alloc;
    }
}