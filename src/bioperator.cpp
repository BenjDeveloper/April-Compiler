#include <iostream>
#include "../include/bioperator.hpp"
#include "../include/codegencontext.hpp"
#include "../include/vardeclaration.hpp"
#include "../parser.h"

 //===----------------------------------------------------------------------===//
 //                         Type Class Binary Operator
 //===----------------------------------------------------------------------===//

extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* BinaryOperator::codeGen(CodeGenContext& context)
    {
        llvm::Value* left_value = lhs.codeGen(context);
        llvm::Value* right_value = rhs.codeGen(context);

        if (left_value == nullptr || right_value == nullptr)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: al evaluar la expresion en la operacion binaria\n");
            context.addError();
            return nullptr;
		}


        // std::cout << "creando operacion binaria: " << op << std::endl;
        // llvm::Instruction::BinaryOps instr;

        //---------------------------------------------
        //                  VALIDACION
        //---------------------------------------------

        if (left_value->getType()->isIntegerTy() && right_value->getType()->isFloatingPointTy())
        {
            left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(left_value, true, right_value->getType(), true) , left_value, right_value->getType(), "cast", context.currentBlock() );
        }
        else if (left_value->getType()->isFloatingPointTy() && right_value->getType()->isIntegerTy())
        {
            std::cout << "creando operacion binaria" << std::endl;
            left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(right_value, true, left_value->getType(), true) , right_value, left_value->getType(), "cast", context.currentBlock() );

        }
        else if (left_value->getType()->isIntegerTy() && right_value->getType()->isIntegerTy())
        {
            if ( left_value->getType()->getIntegerBitWidth() < right_value->getType()->getIntegerBitWidth())
            {
                left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( left_value, true, right_value->getType(), true ), left_value, right_value->getType(), "cast", context.currentBlock() );   
            }
            else if  ( left_value->getType()->getIntegerBitWidth() > right_value->getType()->getIntegerBitWidth())
            {
                right_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( right_value, true, left_value->getType(), true ), right_value, left_value->getType(), "cast", context.currentBlock() );
            }
        }
        else if (left_value->getType()->isFloatingPointTy() && right_value->getType()->isFloatingPointTy())
        {
            if (right_value->getType()->isDoubleTy())
            {
                left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( left_value, true, right_value->getType(), true ), left_value, right_value->getType(), "cast", context.currentBlock() ); 
            }
            else if  (left_value->getType()->isDoubleTy())
            {
                right_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( right_value, true, left_value->getType(), true ), right_value, left_value->getType(), "cast", context.currentBlock() );
            }
        }

        context.valOperator(left_value , right_value);

        //---------------------------------------------

        bool op_decimal = (left_value->getType()->isFloatingPointTy() || right_value->getType()->isFloatingPointTy())?(true):(false);

        switch(op)
        {
            case TPLUS: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FAdd, left_value, right_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::Add, left_value, right_value, "", context.currentBlock()); }
            
            case TMIN: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FSub, left_value, right_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::Sub, left_value, right_value, "", context.currentBlock()); }
            
            case TMUL: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FMul, left_value, right_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::Mul, left_value, right_value, "", context.currentBlock()); }
            
            case TDIV: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FDiv, lhs_value, rhs_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::SDiv, lhs_value, rhs_value, "", context.currentBlock()); }
			
            case TAND: 
                return llvm::BinaryOperator::Create(llvm::Instruction::And, lhs_value, rhs_value, "", context.currentBlock()); 
			
			case TOR: 
                return llvm::BinaryOperator::Create(llvm::Instruction::Or, left_value, right_value, "", context.currentBlock());
        }

        return nullptr;
    }
}
