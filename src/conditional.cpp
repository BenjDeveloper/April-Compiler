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
		context.pushBlock(true_block);
		llvm::Value* true_value = then_block.codeGen(context);
		
		if (true_value == nullptr)
		{
			std::cout << "fallo en el bloque then del condicional" << std::endl;
			exit(1);
		}

		if (context.currentBlock()->getTerminator() == nullptr)
		{
			std::cout << "le couleur" << std::endl;
			llvm::BranchInst::Create(merge_block, context.currentBlock());
			need_merge = true;
		}
		
		function->getBasicBlockList().push_back(false_block);
		context.pushBlock(false_block);
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
			context.pushBlock(merge_block);
			llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
		}

		return nullptr;
		//return merge_block;
		//---------------------------------------------------
		//std::cout << "creando if..." << std::endl; 
		//llvm::IRBuilder<> builder(context.currentBlock());
		//llvm::Value* expr_value = expr->codeGen(context);
		//llvm::Function* function = builder.GetInsertBlock()->getParent();

		//llvm::BasicBlock* block_true = llvm::BasicBlock::Create(llvm::getGlobalContext(), "then", function);
		//llvm::BasicBlock* block_false = nullptr;

		//if (has_else)
		//{
		//	std::cout << "contiene else" << std::endl;
		//	block_false = llvm::BasicBlock::Create(llvm::getGlobalContext(), "else", function);
		//}
		//builder.CreateCondBr(expr_value, block_true, block_false);
		//builder.SetInsertPoint(block_true);
		//  
		//context.pushBlock(block_true);
		//then_block.codeGen(context);
		//context.popBlock();

		//if (has_else)
		//{
		//	context.pushBlock(block_false);
		//	else_block.codeGen(context);
		//	context.popBlock();
		//}
		//return nullptr;
		//-----------------------------------------------------------
	}
}
