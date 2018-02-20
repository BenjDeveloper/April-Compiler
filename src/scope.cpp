#include "../include/scope.hpp"

namespace april
{
	llvm::Value* Scope::codeGen(CodeGenContext& context)
	{
		llvm::Function* funcion = context.currentBlock()->getParent();
		llvm::BasicBlock* bblock = llvm::BasicBlock::Create(context.getGlobalContext(), "scope", funcion);
		llvm::BranchInst::Create(bblock, context.currentBlock());
		context.pushBlock(bblock);
		llvm::Value* block_value = block->codeGen(context);
		
		if (context.currentBlock()->getTerminator() == nullptr)
		{
			llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
		}

		context.popBlock();
		return nullptr;
	}

}
