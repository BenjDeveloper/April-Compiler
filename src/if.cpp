#include <vector>
#include "../headers/if.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    If::~If()
    {
        std::cout << "destructo IF" << std::endl;
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
        // std::cout << "ini if: " <<sym_expr->value._bval << std::endl;
        if (sym_expr->value._bval == true)
        {
            //  std::cout << "_then..." << std::endl;
            _then->type_scope = BlockScope::IF;

            _then->prev = context.getCurrentBlock();
            context.setCurrentBlock(_then);
        
            result = _then->codeGen(context); 
            
            context.popCurrentBlock();
        }
        else if (_else != nullptr) 
        {
            _else->type_scope = BlockScope::IF;
            _else->prev = context.getCurrentBlock();
            context.setCurrentBlock(_else);

            result = _else->codeGen(context);
            context.popCurrentBlock();
        }

        // if (result == nullptr)
        //     std::cout << "result es NULO (IF)" << std::endl;
        // else
        //     std::cout << "result (IF): " << *result << std::endl;
        // std::cout << "fin if" << std::endl;
        
        return result;
    }
}