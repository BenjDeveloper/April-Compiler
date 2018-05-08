#include "../headers/block.hpp"

namespace april
{
    Block::~Block()
    {
        for (Statement*& stmt: statements)
            delete stmt;
    }

    Symbol* Block::codeGen(CodeGenContext& context)
    {
        Symbol* last = nullptr;
        for (Statement*& stmt: statements)
        {
            if (stop)
            {
                std::cout << "adios" << std::endl;
                break;
            }
            last = stmt->codeGen(context);
            
        }
        
        std::cout << "fin del bloque" << std::endl;
        stop = false;
        return last;
    }
}