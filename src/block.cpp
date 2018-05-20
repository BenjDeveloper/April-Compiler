#include "../headers/block.hpp"
#include "../headers/codegencontext.hpp"


namespace april
{
    Block::~Block()
    {
        // std::cout << "---->> destructor block" << std::endl;
        for (Statement*& stmt: statements)
            if (stmt != nullptr)
                delete stmt;
        
        for (Symbol* sym : locals)
            if (sym != nullptr)
                delete sym;
    }

    Symbol* Block::codeGen(CodeGenContext& context)
    {
        // std::cout << ">> ini block <<" << std::endl;
        Symbol* last = new Symbol{};
        
        for (Statement*& stmt: statements)
        {
            if (!stop)
            {
                last = stmt->codeGen(context);
                if (last == nullptr)
                    return nullptr;
            }
            else
                break;
        }

        
        if (type_scope != BlockScope::FOR)
            stop = false;
        // if (last == nullptr)
        //     std::cout << ">> fin block(NULLPTR)<<" << std::endl;
        // else
        // std::cout << ">> fin block(" << *last <<  " )<< " << std::endl;

        return last;
    }
}