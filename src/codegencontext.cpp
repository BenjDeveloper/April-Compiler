#include "../headers/codegencontext.hpp"

namespace april
{
    CodeGenContext::CodeGenContext()
    {
        current_block = nullptr;
        errors = 0;
        listMethods = loadMethod("len");
    }

    Symbol* CodeGenContext::runCode(Block* block)
    {
        current_block = block;
        Symbol* symbol = current_block->codeGen(*this);
        //std::cout << "result: " << ((symbol->type == Type::INTEGER)?(symbol->value._ival):(symbol->value._dval)) << std::endl;
        return symbol;
    }

    Symbol* CodeGenContext::findIdentLocals(std::string name)
    {
        for (Symbol*& symbol : this->current_block->locals)
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