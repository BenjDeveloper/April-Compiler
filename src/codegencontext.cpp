#include "../headers/codegencontext.hpp"

namespace april
{
    CodeGenContext::CodeGenContext()
    {
        current_block = nullptr;
        errors = 0;
    }

    Symbol* CodeGenContext::runCode(Block* block)
    {
        current_block = block;
        Symbol* symbol = current_block->codeGen(*this);
        return symbol;
    }

    Symbol* CodeGenContext::findIdentLocals(std::string name)
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

        return Type::UNDEFINED;
    }
}