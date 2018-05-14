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

    void CodeGenContext::loadFunction()
    {
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

    void CodeGenContext::popCurrentBlock()
    {
        Block* aux = current_block;
        if (aux != nullptr)
        {
            current_block = aux->prev;
            aux->prev = nullptr;
        }
    }

    void CodeGenContext::runCode(Block* block)
    {
        current_block = block;
        current_block->type_scope = BlockScope::FUNCTION;
        push_block(current_block);
        
        current_block->codeGen(*this);
        
        pop_block();
    }

    Symbol*& CodeGenContext::findIdentLocals(std::string name)
    {
        Block* aux = current_block;

        while (aux != nullptr)
        {
            for (Symbol*& symbol : aux->locals)
            {
                if (symbol->name == name)
                {
                    return symbol;
                }
            }
            aux = aux->prev;
        }
    }
    Symbol* CodeGenContext::existIdenLocals(std::string name)
    {
        Block* aux = current_block;

        while (aux != nullptr)
        {
            for (Symbol*& symbol : aux->locals)
            {
                if (symbol->name == name)
                {
                    return symbol;
                }
            }
            aux = aux->prev;
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
        
        else if (type == "list")
            return Type::LIST;

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

    void CodeGenContext::stopRootBlock()
    {
        Block* aux = current_block;
        Block* tmp = nullptr;
        while (aux != nullptr && aux->prev != nullptr)
        {
            aux->stop = true;
            tmp = aux;
            aux = aux->prev;
            delete tmp;
        }
        
        if (aux != nullptr)
            aux->stop = true;
    }

    void CodeGenContext::stopBreakBlock()
    {
        Block* aux = current_block;
        Block* tmp = nullptr;
        while (aux != nullptr && aux->prev != nullptr && aux->type_scope != BlockScope::FOR)
        {
            aux->stop = true;
            tmp = aux;
            aux = aux->prev;
            delete tmp;
        }
        
        if (aux != nullptr)
            aux->stop = true;
    }

    void CodeGenContext::printLocals()
    {
        Block* aux = current_block;

        while (aux != nullptr)
        {
            for (Symbol* s : aux->locals)
            {
                std::cout << "name: " << s->name << std::endl;
            }

            aux = aux->prev;
        }
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