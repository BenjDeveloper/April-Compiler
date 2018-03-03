#include <iostream>
#include "../include/unaryope.hpp"
#include "../include/vardeclaration.hpp"
#include "../parser.h"
#include "../include/integer.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* UnaryOpe::codeGen(CodeGenContext& context)
	{
		llvm::Instruction::BinaryOps instr;
		llvm::Value* rhs_value = nullptr;
		llvm::Value* lhs_value = nullptr;

		if (operation  == TUNARIPLUS)
		{
			instr = llvm::Instruction::Add;
			Integer* num = new Integer(1);
			rhs_value = num->codeGen(context);
			// rhs_value = context.locals()[ident->getName()];
			lhs_value = hs->codeGen(context);

			llvm::Value* result =  llvm::BinaryOperator::Create(instr, rhs_value , lhs_value, "unarAdd", context.currentBlock());

			return new llvm::StoreInst(result, context.locals()[ident->getName()], false, context.currentBlock());
		}
		else if (operation  == TUNARIMIN)
		{
			instr = llvm::Instruction::Sub;
		}
		printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el operador unario no esta definido\n");
		context.addError();
		return nullptr;
	}
}