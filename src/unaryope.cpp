#include <iostream>
#include "../include/unaryope.hpp"
#include "../include/vardeclaration.hpp"
#include "../parser.h"
#include "../include/integer.hpp"
#include "../include/double.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* UnaryOpe::codeGen(CodeGenContext& context)
	{
		llvm::Instruction::BinaryOps instr;
		llvm::Value* rhs_value = nullptr;
		llvm::Value* lhs_value = nullptr;
		bool is_int = true;
		Integer* int_num = nullptr;
		Double* double_num = nullptr;

		if (ope  == TUNARIPLUS)
		{
			lhs_value = iden->codeGen(context);
			
			if (lhs_value->getType()->isIntegerTy())
			{
				instr = llvm::Instruction::Add;
				int_num = new Integer(1);
				rhs_value = int_num->codeGen(context);
			}
			else if(lhs_value->getType()->isDoubleTy())
			{
				instr = llvm::Instruction::FAdd;
				double_num = new Double(1.0);
				rhs_value = double_num->codeGen(context);
			}
			else
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el operador unario '++' no esta definido para este tipo de dato.\n");
				context.addError();
				return nullptr;
			}

			llvm::Value* result =  llvm::BinaryOperator::Create(instr, rhs_value , lhs_value, "unarAdd", context.currentBlock());
			new llvm::StoreInst(result, context.searchVariableAll(iden->getName()), false, context.currentBlock());
			return new llvm::LoadInst(context.searchVariableAll(iden->getName()), "", false, context.currentBlock());
		}
		else if (ope  == TUNARIMIN)
		{
			lhs_value = iden->codeGen(context);

			if (lhs_value->getType()->isIntegerTy())
			{
				instr = llvm::Instruction::Sub;
				int_num = new Integer(1);
				rhs_value = int_num->codeGen(context);
			}
			else if (lhs_value->getType()->isDoubleTy())
			{
				instr = llvm::Instruction::FSub;
				double_num = new Double(1.0);
				rhs_value = double_num->codeGen(context);
			}
			else
			{
				printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el operador unario '--' no esta definido para este tipo de dato.\n");
				context.addError();
				return nullptr;
			}

			llvm::Value* result = llvm::BinaryOperator::Create(instr,lhs_value, rhs_value, "unarSub", context.currentBlock());
			new llvm::StoreInst(result, context.searchVariableAll(iden->getName()), false, context.currentBlock());
			return new llvm::LoadInst(context.searchVariableAll(iden->getName()), "", false, context.currentBlock());
		}
		printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el operador unario no esta definido\n");
		context.addError();
		return nullptr;
	}
}