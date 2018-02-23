#include <iostream>
#include "../include/vardeclaration.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

//----------------------------

namespace april
{
    llvm::Value* VariableDeclaration::codeGen(CodeGenContext& context)
    {
        if (context.searchVariable(id.name))
        {
            printError("la variable '"+id.name+"' ya existe\n");
            context.addError();
            return nullptr;
        }
        
        // std::cout << "Creating variable declaration " << type.name << ", " << id.name << std::endl;
        llvm::Type* type_value = context.typeOf(type);
        llvm::AllocaInst* alloc = new llvm::AllocaInst(type_value, id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
		
        if (assignmentExpr != nullptr)
        { 
            llvm::Value* expr_value = assignmentExpr->codeGen(context);
            if (expr_value == nullptr)
            {
                printError("Error con el token de tipo "+type.name+"\n");
                context.addError();
                return nullptr;
            }

            if (type_value->isIntegerTy() && expr_value->getType()->isIntegerTy(64))
            {
                if (type_value->isIntegerTy(1))
                { 
                    auto new_type = llvm::Type::getInt1Ty(context.getGlobalContext());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());
                }
                else if (type_value->isIntegerTy(8))
                { 
                    auto new_type = llvm::Type::getInt8Ty(context.getGlobalContext());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());
                }
                else if (type_value->isIntegerTy(16))
                { 
                    auto new_type = llvm::Type::getInt16Ty(context.getGlobalContext());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());
                }
                else if (type_value->isIntegerTy(32))
                { 
                    auto new_type = llvm::Type::getInt32Ty(context.getGlobalContext());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());
                }
            }
            else if (type_value->isFloatingPointTy() && (expr_value->getType()->isDoubleTy() || expr_value->getType()->isIntegerTy()))
            {
                if (type_value->isHalfTy())
                {
                    auto new_type = llvm::Type::getHalfTy(context.getGlobalContext());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());
                }
                else if (type_value->isFloatTy())
                {
                    auto new_type = llvm::Type::getFloatTy(context.getGlobalContext());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());
                }
                else if (type_value->isDoubleTy() && expr_value->getType()->isIntegerTy())
                {
                    auto new_type = llvm::Type::getDoubleTy(context.getGlobalContext());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());
                }
            }
            else if (type_value->isIntegerTy() && expr_value->getType()->isFloatingPointTy())
            {
                printError("Error al asignar una variable tipo int con un float");
                context.addError();
                return nullptr;
            }
            
           
            Assignment assn(id, *assignmentExpr, expr_value);
            assn.codeGen(context);
        }

        return alloc;
    }
}
