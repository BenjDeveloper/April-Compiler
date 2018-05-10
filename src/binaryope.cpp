#include "../headers/binaryope.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* BinaryOpe::codeGen(CodeGenContext& context)
    {
        Symbol* value_left = left->codeGen(context);
        Symbol* value_right = right->codeGen(context);
        Symbol* tmp = new Symbol{};

        if ((Type::STRING == value_left->type) && (Type::STRING == value_right->type) && ( ope != OPE::PLUS ))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los datos tipo string no poseen un manejo logico con ese operador.\n");
            context.addError();
            return nullptr;
        }
       
        switch (ope)
        {
            case OPE::PLUS:
                tmp = *value_left + *value_right;
                break;
            
            case OPE::MIN:
                tmp = *value_left - *value_right;
                break;
            
            case OPE::MUL:
                tmp = *value_left * *value_right;
                break;
            
            case OPE::DIV:
                tmp = *value_left / *value_right;
                break;
            
            case OPE::AND:
                tmp->value._bval = *value_left && *value_right;
                tmp->type = Type::BOOLEAN;
                break;
            
            case OPE::OR:
                tmp->value._bval = *value_left || *value_right;
                tmp->type = Type::BOOLEAN;
                break;
        }
        return tmp;
    }
}