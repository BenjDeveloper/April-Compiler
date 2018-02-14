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
        else if (type.name.compare("bool") == 0)
        {
            return llvm::Type::getInt1Ty(context.getGlobalContext());
        }
        
        std::cout << ">>> Error no existe tipo: "<< type.name << " <<<" << std::endl;
        exit(1);
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
        llvm::Type* type_value = typeOf(type, context);
        llvm::AllocaInst* alloc = new llvm::AllocaInst(type_value, id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;

        
        if (assignmentExpr != nullptr)
        { 
            llvm::Value* expr_value = assignmentExpr->codeGen(context);
            if (expr_value == nullptr)
            {
                std::cout << "Error con el token de tipo "<< type.name << std::endl;
                exit(1);
            }
            // condicional para hacer una asignacion de un int a un float se hace un cast al int 
            if (type_value->isDoubleTy() && expr_value->getType()->isIntegerTy())
            {
                auto double_type = llvm::Type::getDoubleTy(context.getGlobalContext());
                auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, double_type, true);
                expr_value = llvm::CastInst::Create(cast_instr, expr_value, double_type, "cast", context.currentBlock());
            }
            if (type_value->isIntegerTy() && expr_value->getType()->isDoubleTy())
            {
                std::cout << "Error al asignar una variable tipo int con un float" << std::endl;
                exit(1);
            }
            std::cout << "azul" << std::endl;
            Assignment assn(id, *assignmentExpr, expr_value);
            assn.codeGen(context);
        }

        return alloc;
    }
}