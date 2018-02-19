#include <iostream>
#include "../include/block.hpp"
#include "../include/codegencontext.hpp"
//----------------------------

namespace april
{
    llvm::Value* Block::codeGen(CodeGenContext& context)
    {

        std::cout << "**********************inicio del bloque**********************" << std::endl;
		llvm::Value* last = nullptr;
		
		for (auto s: statements)
		{	
			//std::cout << "-->generando instruccion<--" << std::endl;
			last = s->codeGen(context);

		}

		context.popBlock();
        std::cout << "**********************fin del bloque**********************\n" << std::endl;
        return last; 
    }
}
