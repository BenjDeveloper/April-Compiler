#include "../headers/not.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* Not::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);

        if (sym_expr->type != Type::BOOLEAN)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipo de dato no booleano.\n");
            context.addError();
            return nullptr;
        }
        Symbol* tmp = new Symbol{};
        tmp->type = sym_expr->type;
        tmp->is_constant = sym_expr->is_constant;
        tmp->is_variable = false;
        tmp->value._bval = !sym_expr->value._bval; 

        return tmp;
    }
}