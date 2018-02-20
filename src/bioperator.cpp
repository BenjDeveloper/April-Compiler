#include <iostream>
#include "../include/bioperator.hpp"
#include "../include/codegencontext.hpp"
#include "../include/vardeclaration.hpp"
#include "../parser.h"

//----------------------------


namespace april
{
    llvm::Value* BinaryOperator::codeGen(CodeGenContext& context)
    {
        llvm::Value* lhs_value = lhs.codeGen(context);
        llvm::Value* rhs_value = rhs.codeGen(context);

        std::cout << "creando operacion binaria: " << op << std::endl;
        llvm::Instruction::BinaryOps instr;
        
        if ((lhs_value->getType()->isDoubleTy() && rhs_value->getType()->isIntegerTy()) || (lhs_value->getType()->isIntegerTy() && rhs_value->getType()->isDoubleTy()))
        {
            std::cout << "-->entro operacion binaria diferente" << std::endl;
            
            auto double_type = llvm::Type::getDoubleTy(context.getGlobalContext());
            auto cast_instr = llvm::CastInst::getCastOpcode(rhs_value, true, double_type, true);
            rhs_value = llvm::CastInst::Create(cast_instr, rhs_value, double_type, "cast", context.currentBlock());
            cast_instr = llvm::CastInst::getCastOpcode(lhs_value, true, double_type, true);
            lhs_value = llvm::CastInst::Create(cast_instr, lhs_value, double_type, "cast", context.currentBlock());
        }

        bool op_decimal = (lhs_value->getType()->isDoubleTy() || rhs_value->getType()->isDoubleTy())?(true):(false);

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

        return NULL;
    }
}
