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
            last = stmt->codeGen(context);
        
        return last;
    }
}