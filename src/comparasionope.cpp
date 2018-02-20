#include <iostream>
#include "../include/comparasionope.hpp"
#include "../include/vardeclaration.hpp"
#include "../parser.h"

namespace april
{
	llvm::Value* ComparasionOpe::codeGen(CodeGenContext& context)
	{
		llvm::Value* lhs_value = lhs.codeGen(context);
		llvm::Value* rhs_value = rhs.codeGen(context);
		
		if (lhs_value->getType() != rhs_value->getType())
		{
			auto cinst = llvm::CastInst::getCastOpcode(rhs_value, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true);	
			rhs_value = llvm::CastInst::Create(cinst, rhs_value, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast", context.currentBlock());
			cinst =  llvm::CastInst::getCastOpcode(lhs_value, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true);	
			lhs_value = llvm::CastInst::Create(cinst, lhs_value, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast", context.currentBlock());
		}

		bool isDouble = rhs_value->getType() == llvm::Type::getDoubleTy(context.getGlobalContext());
		llvm::Instruction::OtherOps oinst = (isDouble)?(llvm::Instruction::FCmp):(llvm::Instruction::ICmp);
		llvm::CmpInst::Predicate predicate;
		
		switch(operation)
		{
			case TCOMGE:
				predicate = (isDouble)?(llvm::CmpInst::FCMP_OGE):(llvm::CmpInst::ICMP_SGE);
				break;
			
			case TCOMGT:
				predicate = (isDouble)?(llvm::CmpInst::FCMP_OGT):(llvm::CmpInst::ICMP_SGT);
				break;
			
			case TCOMLT:
				predicate = (isDouble)?(llvm::CmpInst::FCMP_OLT):(llvm::CmpInst::ICMP_SLT);
				break;
			
			case TCOMLE:
				predicate = (isDouble)?(llvm::CmpInst::FCMP_OLE):(llvm::CmpInst::ICMP_SLE);
				break;

			case TCOMEQ:
				predicate = (isDouble)?(llvm::CmpInst::FCMP_OEQ):(llvm::CmpInst::ICMP_EQ);
				break;

			case TCOMNE:
				predicate = (isDouble)?(llvm::CmpInst::FCMP_ONE):(llvm::CmpInst::ICMP_NE);
				break;

			default:
				std::cout << "Operador no reconocido" << std::endl;
				return nullptr;
		}

		return llvm::CmpInst::Create(oinst, predicate, lhs_value, rhs_value, "cmotmo", context.currentBlock());
	}
}
