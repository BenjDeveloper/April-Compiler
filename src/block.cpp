#include <iostream>
#include "../include/block.hpp"

//----------------------------

namespace april
{
    llvm::Value* Block::codeGen(CodeGenContext& context)
    {
        StatementList::const_iterator it;

        llvm::Value* last = NULL;

        for (it = statements.begin(); it != statements.end(); it++)
        {
            std::cout << "creando instruccion..." << std::endl;
            last = (**it).codeGen(context);
        }

        std::cout << "instruccion creada..." << std::endl;
        return last; 
    }
}