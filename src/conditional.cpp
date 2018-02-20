#include <iostream>
#include "../include/conditional.hpp"


namespace april
{
	llvm::Value* Conditional::codeGen(CodeGenContext& context)
	{
		llvm::Value* expr_value = expr->codeGen(context);
		
		llvm::Function* function = context.currentBlock()->getParent();
		llvm::BasicBlock* true_block = llvm::BasicBlock::Create(context.getGlobalContext(), "then", function);
		llvm::BasicBlock* false_block = llvm::BasicBlock::Create(context.getGlobalContext(), "else");
		llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(context.getGlobalContext(), "merge");
		llvm::BranchInst::Create(true_block, false_block , expr_value, context.currentBlock());
		
		bool need_merge = false;
		
		context.setCurrentBlock(true_block);
		llvm::Value* true_value = then_block.codeGen(context);		

		if (true_value == nullptr)
		{
			std::cout << "fallo en el bloque then..." << std::endl;
			exit(1);
		}

		if (context.currentBlock()->getTerminator() == nullptr)
		{
			std::cout << "le couleur" << std::endl;
			llvm::BranchInst::Create(merge_block, context.currentBlock());
			need_merge = true;
		}
		
		
		function->getBasicBlockList().push_back(false_block);
		context.setCurrentBlock(false_block);
		llvm::Value* false_value = nullptr;
		if (has_else)
		{
			false_value = else_block.codeGen(context);
		}
		
		if (context.currentBlock()->getTerminator() == nullptr)
		{
			std::cout << "Femme" << std::endl;
			llvm::BranchInst::Create(merge_block, context.currentBlock());
			need_merge = true;
		}
		
		if (need_merge)
		{
			function->getBasicBlockList().push_back(merge_block);
			context.setCurrentBlock(merge_block);
		}

		return merge_block;
	}
}
