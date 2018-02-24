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
        llvm::Value* lhs_value = lhs.codeGen(context);
        llvm::Value* rhs_value = rhs.codeGen(context);

        if (lhs_value == nullptr || rhs_value == nullptr)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: al evaluar la expresion en la operacion binaria\n");
            context.addError();
            return nullptr;
		}

        // std::cout << "creando operacion binaria: " << op << std::endl;
        llvm::Instruction::BinaryOps instr;
        
        llvm::Type* new_type = nullptr;

        if (lhs_value->getType()->isIntegerTy() && rhs_value->getType()->isFloatingPointTy())
        {
            if (rhs_value->getType()->isHalfTy())
            {
                new_type = llvm::Type::getHalfTy(context.getGlobalContext());
            }
            else if (rhs_value->getType()->isFloatTy())
            {
                new_type = llvm::Type::getFloatTy(context.getGlobalContext());
            }
            else if (rhs_value->getType()->isDoubleTy())
            {
                new_type = llvm::Type::getDoubleTy(context.getGlobalContext());    
            }
            auto cast_instr = llvm::CastInst::getCastOpcode(lhs_value, true, new_type, true);
            lhs_value = llvm::CastInst::Create(cast_instr, lhs_value, new_type, "cast", context.currentBlock());
        }
        else if (lhs_value->getType()->isFloatingPointTy() && rhs_value->getType()->isIntegerTy())
        {
            if (lhs_value->getType()->isHalfTy())
            {
                new_type = llvm::Type::getHalfTy(context.getGlobalContext());
            }
            else if (lhs_value->getType()->isFloatTy())
            {
                new_type = llvm::Type::getFloatTy(context.getGlobalContext());
            }
            else if (lhs_value->getType()->isDoubleTy())
            {
                new_type = llvm::Type::getDoubleTy(context.getGlobalContext());    
            }
            auto cast_instr = llvm::CastInst::getCastOpcode(rhs_value, true, new_type, true);
            rhs_value = llvm::CastInst::Create(cast_instr, rhs_value, new_type, "cast", context.currentBlock());
        }
        else if (lhs_value->getType()->isIntegerTy() && rhs_value->getType()->isIntegerTy())
        {
            if ( lhs_value->getType()->getIntegerBitWidth() < rhs_value->getType()->getIntegerBitWidth())
            {
                new_type = llvm::Type::getIntNTy(context.getGlobalContext(), rhs_value->getType()->getIntegerBitWidth());
                auto cast_instr = llvm::CastInst::getCastOpcode(lhs_value, true, new_type, true);
                lhs_value = llvm::CastInst::Create(cast_instr, lhs_value, new_type, "cast", context.currentBlock());   
            }
            else if  ( lhs_value->getType()->getIntegerBitWidth() > rhs_value->getType()->getIntegerBitWidth())
            {
                new_type = llvm::Type::getIntNTy(context.getGlobalContext(), lhs_value->getType()->getIntegerBitWidth());
                auto cast_instr = llvm::CastInst::getCastOpcode(rhs_value, true, new_type, true);
                rhs_value = llvm::CastInst::Create(cast_instr, rhs_value, new_type, "cast", context.currentBlock());
            }
           
        }
        else if (lhs_value->getType()->isFloatingPointTy() && rhs_value->getType()->isFloatingPointTy())
        {
            if ( lhs_value->getType()->getPrimitiveSizeInBits() < rhs_value->getType()->getPrimitiveSizeInBits())
            {
                auto cast_instr = llvm::CastInst::getCastOpcode(lhs_value, true, rhs_value->getType(), true);
                lhs_value = llvm::CastInst::Create(cast_instr, lhs_value, rhs_value->getType(), "cast", context.currentBlock()); 
            }
            else if  ( lhs_value->getType()->getPrimitiveSizeInBits() > rhs_value->getType()->getPrimitiveSizeInBits())
            {
                auto cast_instr = llvm::CastInst::getCastOpcode(rhs_value, true, lhs_value->getType(), true);
                rhs_value = llvm::CastInst::Create(cast_instr, rhs_value, lhs_value->getType(), "cast", context.currentBlock());
            }
        }

        bool op_decimal = (lhs_value->getType()->isFloatingPointTy() || rhs_value->getType()->isFloatingPointTy())?(true):(false);

        switch(op)
        {
            case TPLUS: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FAdd, lhs_value, rhs_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::Add, lhs_value, rhs_value, "", context.currentBlock()); }
            
            case TMIN: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FSub, lhs_value, rhs_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::Sub, lhs_value, rhs_value, "", context.currentBlock()); }
            
            case TMUL: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FMul, lhs_value, rhs_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::Mul, lhs_value, rhs_value, "", context.currentBlock()); }
            
            case TDIV: 
                if (op_decimal) { return llvm::BinaryOperator::Create(llvm::Instruction::FDiv, lhs_value, rhs_value, "", context.currentBlock()); }
                else { return llvm::BinaryOperator::Create(llvm::Instruction::SDiv, lhs_value, rhs_value, "", context.currentBlock()); }
       		
			case TAND: 
                return llvm::BinaryOperator::Create(llvm::Instruction::And, lhs_value, rhs_value, "", context.currentBlock()); 
			
			case TOR: 
                return llvm::BinaryOperator::Create(llvm::Instruction::Or, lhs_value, rhs_value, "", context.currentBlock());
		}

        return nullptr;
    }
}
