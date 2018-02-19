#include "../include/scope.hpp"

namespace april
{
	llvm::Value* Scope::codeGen(CodeGenContext& context)
	{
		llvm::Function* funcion = context.currentBlock()->getParent();
		llvm::BasicBlock* bblock = llvm::BasicBlock::Create(context.getGlobalContext(), "scope", funcion);
		context.pushBlock(bblock);
		llvm::Value* block_value = block->codeGen(context);
		
		return block_value;
		//context.pushBlock(block);			
	}

}
