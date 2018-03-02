#include "../include/assigbiope.hpp"
#include "../include/codegencontext.hpp"
#include "../include/vardeclaration.hpp"
#include "../parser.h"

extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* AssigBioperator::codeGen(CodeGenContext& context)
    {
        if (expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: asignacion nula\n");
            context.addError();
            return nullptr;
        }

        if (context.locals()[ident->name] == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable "+ ident->name +" no ha sido declarada\n");
            context.addError();
            return nullptr;
        }
        
        llvm::Value* expr_value = expr->codeGen(context);
        if (expr_value == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: al evaluar la expresion aa\n");
            context.addError();
            return nullptr;
        }

        llvm::Value* ident_value = ident->codeGen(context);
        llvm::Type* new_type = nullptr;
        
        //---------------------------------------------
        //                  VALIDACION
        //---------------------------------------------

        if (ident_value->getType()->isIntegerTy() && expr_value->getType()->isIntegerTy(64))
        {
            if (!ident_value->getType()->isIntegerTy(64))
            { 
                expr_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(expr_value, true, ident_value->getType(), true) , expr_value, ident_value->getType(), "cast", context.currentBlock());
            }
        }
        else if (ident_value->getType()->isFloatingPointTy() && (expr_value->getType()->isDoubleTy() || expr_value->getType()->isIntegerTy()))
        {
            if (!ident_value->getType()->isDoubleTy())
            {
                expr_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(expr_value, true, ident_value->getType(), true), expr_value, ident_value->getType(), "cast", context.currentBlock());
            }
        }

        // if (left_value->getType()->isIntegerTy() && right_value->getType()->isFloatingPointTy())
        // {
        //     left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(left_value, true, right_value->getType(), true) , left_value, right_value->getType(), "cast", context.currentBlock() );
        // }
        // else if (left_value->getType()->isFloatingPointTy() && right_value->getType()->isIntegerTy())
        // {
        //     left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(right_value, true, left_value->getType(), true) , right_value, left_value->getType(), "cast", context.currentBlock() );
        // }
        // else if (left_value->getType()->isIntegerTy() && right_value->getType()->isIntegerTy())
        // {
        //     if ( left_value->getType()->getIntegerBitWidth() < right_value->getType()->getIntegerBitWidth())
        //     {
        //         left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( left_value, true, right_value->getType(), true ), left_value, right_value->getType(), "cast", context.currentBlock() );   
        //     }
        //     else if  ( left_value->getType()->getIntegerBitWidth() > right_value->getType()->getIntegerBitWidth())
        //     {
        //         right_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( right_value, true, left_value->getType(), true ), right_value, left_value->getType(), "cast", context.currentBlock() );
        //     }
        // }
        // else if (left_value->getType()->isFloatingPointTy() && right_value->getType()->isFloatingPointTy())
        // {
        //     if (right_value->getType()->isDoubleTy())
        //     {
        //         left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( left_value, true, right_value->getType(), true ), left_value, right_value->getType(), "cast", context.currentBlock() ); 
        //     }
        //     else if  (left_value->getType()->isDoubleTy())
        //     {
        //         right_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( right_value, true, left_value->getType(), true ), right_value, left_value->getType(), "cast", context.currentBlock() );
        //     }
        // }
        //---------------------------------------------
        
        bool op_decimal = (context.locals()[ident->name]->getType()->isFloatingPointTy() || expr_value->getType()->isFloatingPointTy())?(true):(false);

        if (ident_value == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: bitchesss\n");
            context.addError();
            return nullptr;
        }

        llvm::Value* result = nullptr;
        switch(_operator)
        {
            case TASIGPLUS:
                // result = llvm::BinaryOperator::Create(llvm::Instruction::Add, ident_value, expr_value,  "", context.currentBlock());
                if (op_decimal) { result = llvm::BinaryOperator::Create(llvm::Instruction::FAdd, ident_value, expr_value, "", context.currentBlock()); }
                else { result = llvm::BinaryOperator::Create(llvm::Instruction::Add, ident_value, expr_value, "", context.currentBlock()); }
                break;

            case TASIGMINUS:
                // result = llvm::BinaryOperator::Create(llvm::Instruction::Sub, ident_value, expr_value,  "", context.currentBlock());
                if (op_decimal) { result = llvm::BinaryOperator::Create(llvm::Instruction::FSub, ident_value, expr_value, "", context.currentBlock()); }
                else { result = llvm::BinaryOperator::Create(llvm::Instruction::Sub, ident_value, expr_value, "", context.currentBlock()); }
                break;

            case TASIGMULT:
                // result = llvm::BinaryOperator::Create(llvm::Instruction::Sub, ident_value, expr_value,  "", context.currentBlock());
                if (op_decimal) { result = llvm::BinaryOperator::Create(llvm::Instruction::FMul, ident_value, expr_value, "", context.currentBlock()); }
                else { result = llvm::BinaryOperator::Create(llvm::Instruction::Mul, ident_value, expr_value, "", context.currentBlock()); }
                break;
            
            case TASIGDIV:
                // result = llvm::BinaryOperator::Create(llvm::Instruction::Sub, ident_value, expr_value,  "", context.currentBlock());
                if (op_decimal) { result = llvm::BinaryOperator::Create(llvm::Instruction::FDiv, ident_value, expr_value, "", context.currentBlock()); }
                else { result = llvm::BinaryOperator::Create(llvm::Instruction::SDiv, ident_value, expr_value, "", context.currentBlock()); }
                break;
        }

        return new llvm::StoreInst(result, context.locals()[ident->name], false, context.currentBlock());
        // context.locals()[ident->name] = (llvm::AllocaInst*) result;
        // return nullptr;
    }
}