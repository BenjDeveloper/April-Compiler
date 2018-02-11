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
        std::cout << "creando operacion binaria: " << op << std::endl;
        llvm::Instruction::BinaryOps instr;

        switch(op)
        {
            case TPLUS: 
                std::cout << "sumando :)" << std::endl;
                return llvm::BinaryOperator::Create(llvm::Instruction::Add, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
            case TMIN: 
                return llvm::BinaryOperator::Create(llvm::Instruction::Sub, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
            case TMUL: 
                return llvm::BinaryOperator::Create(llvm::Instruction::Mul, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
            case TDIV: 
                return llvm::BinaryOperator::Create(llvm::Instruction::SDiv, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
        }

        return NULL;
    }
}