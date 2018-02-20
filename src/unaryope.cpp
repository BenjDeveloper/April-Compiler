#include <iostream>
#include "../include/unaryope.hpp"
#include "../include/vardeclaration.hpp"
#include "../parser.h"

namespace april
{
	llvm::Value* UnaryOpe::codeGen(CodeGenContext& context)
	{
		llvm::Instruction::BinaryOps instr;

		switch(operation)
		{
			case TNOT:
				instr = llvm::Instruction::Xor;
				break;

			default:
				std::cout << "Operador el operador unario no esta definido..." << std::endl;
				// context.addError() -> definir funcion que maneje el error
				return nullptr;
		}
		
		llvm::Value* rhs_value = rhs.codeGen(context);

		if (rhs_value->getType() != llvm::Type::getInt1Ty(context.getGlobalContext()))
		{
			std::cout << "Error el operando tiene que ser de tipo integer" << std::endl;
			exit(1);
			// context.addError() -> definir funcion que maneje el error
			return nullptr;
		}
		

		llvm::Value* lhs_value = llvm::ConstantInt::get(llvm::IntegerType::get(context.getGlobalContext(),llvm::Type::getInt1Ty(context.getGlobalContext())->getIntegerBitWidth()), llvm::StringRef("-1"), 10);

		return llvm::BinaryOperator::Create(instr, lhs_value, rhs_value, "unarytmp", context.currentBlock());
	}
}
