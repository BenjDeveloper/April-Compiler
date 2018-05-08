#include <vector>
#include "../headers/if.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    If::~If()
    {
        if (_then != nullptr)
        {
            delete _then;
            _then = nullptr;
        }

        if (_else != nullptr)
        {
            delete _else;
            _else = nullptr;
        }
    }

    Symbol* If::codeGen (CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
        Symbol* result = nullptr;
        if (sym_expr->type != Type::BOOLEAN)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la expresion no es un boolean.\n");
            context.addError();
            return nullptr;
        }
    
        if (sym_expr->value._bval == true)
        {
            _then->prev = context.getCurrentBlock();
            context.setCurrentBlock(_then);

            result = _then->codeGen(context);
            context.popCurrentBlock();
        }
        else if (_else != nullptr) 
        {
            _else->prev = context.getCurrentBlock();
            context.setCurrentBlock(_else);

            result = _else->codeGen(context);
            context.popCurrentBlock();
        }

        // if (result == nullptr)
        //     std::cout << "result es NULO (IF)" << std::endl;
        // else
        //     std::cout << "result (IF): " << *result << std::endl;

        return result;
    }
}