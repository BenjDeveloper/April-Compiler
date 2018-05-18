#include "../headers/return.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Return::~Return()
    {
        // if (expr != nullptr)
        // {
        //     delete expr;
        //     expr = nullptr;
        // }
    }

    Symbol* Return::codeGen(CodeGenContext& context)
    {
        // std::cout << ">> ini return <<" << std::endl;
        Symbol* sym_expr = expr->codeGen(context);
        
        if (sym_expr == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: expresion nula.\n");
            context.addError();
            return nullptr;
        }

        if (sym_expr->type == Type::UNDEFINED)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+sym_expr->name+"' no esta definida.\n");
            context.addError();
            return nullptr;
        }
        context.stopRootBlock();
        
        return sym_expr;
    }
}