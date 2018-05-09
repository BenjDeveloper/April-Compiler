#include "../headers/codegencontext.hpp"

namespace april
{
    CodeGenContext::CodeGenContext()
    {
        current_block = nullptr;
        errors = 0;
        listMethods = loadMethod("len");
        scope_type = Scope::BLOCK;
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
        for (Symbol*& symbol : current_block->locals)
            if (symbol->name == name)
                return symbol;
        
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

        else if (type == "string")
            return Type::STRING;

        return Type::UNDEFINED;
    }

    bool CodeGenContext::existFunction(std::string name)
    {
        if (functions.find(name) != functions.end())
            return true;
        
        return false;
    }

    bool CodeGenContext::deleteIdentLocals(std::string name)
    {
        
        for (Symbol*& s : current_block->locals)
        {
            if (s->name == name)
            {
                delete s;
                return true;
            }
        }
        
        return false;
    }

    bool CodeGenContext::findMethods(std::string name)
    {
        for (std::string method : this->listMethods)
            if (method == name)
                return true;

        return false;
    }
    
    std::vector<std::string> CodeGenContext::loadMethod(std::string name)
    {
        this->listMethods.push_back(name);
        return listMethods;
    }

}