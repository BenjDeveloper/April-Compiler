#include "../headers/block.hpp"

namespace april
{
    Block::~Block()
    {
        for (Statement*& stmt: statements)
            if (stmt != nullptr)
                delete stmt;
    }

    Symbol* Block::codeGen(CodeGenContext& context)
    {
        Symbol* last = nullptr;
        for (Statement*& stmt: statements)
        {
            if (!stop)
                last = stmt->codeGen(context);
            else
                break;
        }
        //stop = false;
        return last;
    }
}