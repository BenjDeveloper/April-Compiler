#include "../headers/codegencontext.hpp"

namespace april
{
    CodeGenContext::CodeGenContext()
    {
        current_block = nullptr;
        errors = 0;
    }

    void CodeGenContext::push_block(Block* block)
    {
        stack_block.push(block);
        current_block = block;
    }

    void CodeGenContext::pop_block()
    {
        stack_block.pop();
        if (!stack_block.empty())
            current_block = stack_block.top();
        else
            current_block = nullptr;
    }

    void CodeGenContext::setCurrentBlock(Block* block)
    {
        current_block = block;
    }

    void CodeGenContext::runCode(Block* block)
    {
        current_block = block;
        push_block(current_block);
        
        current_block->codeGen(*this);
        pop_block();
    }

    Symbol*& CodeGenContext::findIdentLocals(std::string name)
    {
        for (Symbol*& symbol : this->current_block->locals)
            if (symbol->name == name)
            {
                return symbol;
            }
    }

    Symbol* CodeGenContext::existIdenLocals(std::string name)
    {
        for (Symbol*& symbol : this->current_block->locals)
            if (symbol->name == name)
            {
                return symbol;
            }
        
        return nullptr;
    }

    Type CodeGenContext::typeOf(std::string type)
    {
        if (type == "int")
            return Type::INTEGER;

        else if (type == "double")
            return Type::DOUBLE;

        else if (type == "bool")
            return Type::BOOLEAN;

        return Type::UNDEFINED;
    }
}