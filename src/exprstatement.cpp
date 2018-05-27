#include "../headers/exprstatement.hpp"

namespace april
{
    ExprStatement::~ExprStatement()
    {
        
    }
    
    Symbol* ExprStatement::codeGen(CodeGenContext& context)
    {
        Symbol* symbol = expr->codeGen(context);
        return symbol;
    }
}