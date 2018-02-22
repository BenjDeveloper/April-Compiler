#include <iostream>
#include "../include/block.hpp"
#include "../include/codegencontext.hpp"
//----------------------------

namespace april
{
    llvm::Value* Block::codeGen(CodeGenContext& context)
    {

        // std::cout << "**********************inicio del bloque**********************" << std::endl;
		llvm::Value* last = nullptr;
		
		for (auto s: statements)
		{	
			last = s->codeGen(context);
		}
        // std::cout << "**********************fin del bloque**********************" << std::endl;
		return last; 
    }
}
