#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

//----------------------------

namespace april
{
    static llvm::Type* typeOf(const Identifier& type, CodeGenContext& context)
    {
        if (type.name.compare("int") == 0)
        {
            return llvm::Type::getInt64Ty(context.getGlobalContext());
        }
        else if (type.name.compare("float") == 0)
        {
            return llvm::Type::getDoubleTy(context.getGlobalContext());            
        }
        else if (type.name.compare("string") == 0)
        {
            return llvm::Type::getInt8PtrTy(context.getGlobalContext());
        }
        
        std::cout << ">>> Error no existe tipo: "<< type.name << " <<<" << std::endl;

        return llvm::Type::getVoidTy(llvm::getGlobalContext());
    }

    llvm::Value* VariableDeclaration::codeGen(CodeGenContext& context)
    {
        if (context.locals().find(id.name) != context.locals().end())
        {
            std::cout << "la variable ya existe, no se puede declarar de nuevo" << std::endl;
            exit(1);
        }
        
        std::cout << "Creating variable declaration " << type.name << ", " << id.name << std::endl;
        llvm::AllocaInst* alloc = new llvm::AllocaInst(typeOf(type, context), id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
        if (assignmentExpr != nullptr)
        {   
            Assignment assn(id, *assignmentExpr);
            assn.codeGen(context);
        }

        return alloc;
    }
}