#include "../headers/exprstatement.hpp"

namespace april
{
    Symbol* ExprStatement::codeGen(CodeGenContext& context)
    {
        Symbol* symbol = expr->codeGen(context);
        return symbol;
    }
}