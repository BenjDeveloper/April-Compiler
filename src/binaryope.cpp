#include "../headers/binaryope.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* BinaryOpe::codeGen(CodeGenContext& context)
    {
        Symbol* value_left = left->codeGen(context);
        Symbol* value_right = right->codeGen(context);

        // std::cout << "left: " << value_left->value._ival << std::endl;

        Symbol* tmp = new Symbol{};

        if ((Type::STRING == value_left->type) && (Type::STRING == value_right->type) && (ope != OPE::PLUS))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los datos tipo string no poseen un manejo logico con ese operador.\n");
            context.addError();
            return nullptr;
        }
        else if((Type::STRING != value_left->type && Type::STRING == value_right->type) || (Type::STRING == value_left->type && Type::STRING != value_right->type) )
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipos de datos inoperables.\n");
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
                if ((value_right->type == Type::INTEGER && value_right->value._ival == 0) || (value_right->type == Type::DOUBLE && value_right->value._dval == 0))
                {
                    printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede dividir por cero.\n");
                    context.addError();
                    return nullptr;
                }
                tmp = *value_left / *value_right;
                break;
            
            case OPE::MOD:
                if (value_left->type != Type::INTEGER || value_right->type != Type::INTEGER || value_right->value._ival == 0)
                {
                    printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el operador '%'  los operandos deben ser tipo 'int' y != 0 .\n");
                    context.addError();
                    return nullptr;
                }
                tmp = *value_left % *value_right;
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
        
        tmp->name = "_"+std::to_string(context.getCurrentBlock()->cont_tmp);
        context.getCurrentBlock()->cont_tmp += 1;
        context.getCurrentBlock()->locals.push_back(tmp);

        return tmp;
    }
}