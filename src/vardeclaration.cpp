#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

//----------------------------

namespace april
{
    static llvm::Type* typeOf(const Identifier& type)
    {
        if (type.name.compare("int") == 0)
        {
            return llvm::Type::getInt64Ty(llvm::getGlobalContext());
        }
        else if (type.name.compare("float") == 0)
        {
            return llvm::Type::getDoubleTy(llvm::getGlobalContext());            
        }
        else if (type.name.compare("string") == 0)
        {
            return llvm::Type::getInt8PtrTy(llvm::getGlobalContext());
        }
        
        std::cout << ">>> Error no existe tipo: "<< type.name << " <<<" << std::endl;

        return llvm::Type::getVoidTy(llvm::getGlobalContext());
    }

    llvm::Value* VariableDeclaration::codeGen(CodeGenContext& context)
    {
        std::cout << "Creating variable declaration " << type.name << ", " << id.name << std::endl;
        llvm::AllocaInst* alloc = new llvm::AllocaInst(typeOf(type), id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
        if (assignmentExpr != nullptr)
        {   
            Assignment assn(id, *assignmentExpr);
            assn.codeGen(context);
        }

        return alloc;
    }
}