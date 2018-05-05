#include "../headers/boolean.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* Boolean::codeGen(CodeGenContext& context)
    {
        if (name != "false" && name != "true")
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de dato '"+name+"' no esta definido dentro de boolean.\n");
            context.addError();
            return nullptr;
        }

        Symbol* tmp = new Symbol{};
        tmp->name = "";
        tmp->type = Type::BOOLEAN;
        
        if (name == "true")
            tmp->value._bval = true;
        else if(name == "false")
            tmp->value._bval = false;
        
        tmp->is_constant = true;
        tmp->is_variable = false;
        
        return tmp;       
    }
}