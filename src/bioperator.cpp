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
        //---------------------------------------------
        //                  VALIDACION
        //---------------------------------------------
        //context.valOperator(left_value , right_value);

		if (left_value->getType()->isIntegerTy() && right_value->getType()->isDoubleTy())
		{
			left_value = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(left_value, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), left_value, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast_double", context.currentBlock());
		}
		else if (left_value->getType()->isDoubleTy() && right_value->getType()->isIntegerTy())
		{
			right_value = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(right_value, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), right_value, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast_double", context.currentBlock());
		}
        //---------------------------------------------

        bool op_decimal = (left_value->getType()->isDoubleTy() || right_value->getType()->isDoubleTy())?(true):(false);

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
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FDiv, left_value, right_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::SDiv, left_value, right_value, "", context.currentBlock()); }
			
            case TAND: 
                return llvm::BinaryOperator::Create(llvm::Instruction::And, left_value, right_value, "", context.currentBlock()); 
			
			case TOR: 
                return llvm::BinaryOperator::Create(llvm::Instruction::Or, left_value, right_value, "", context.currentBlock());
        }

        return nullptr;
    }
}
