#include <iostream>
#include "../include/exprstatement.hpp"
#include "../include/codegencontext.hpp"

//----------------------------

namespace april
{
    llvm::Value* ExpressionStatement::codeGen(CodeGenContext& context)
    {
        // std::cout << "codigo generado para la expresion" << std::endl;
        return expression->codeGen(context);
    }
}
