#include <vector>
#include "../include/function.hpp"

namespace april
{
    Function::~Function()
    {
        for (auto i : *args) { delete i; }

        delete type;
        delete id;
        delete args;
        delete block;
    }

    llvm::Value* Function::codeGen(CodeGenContext& context)
    {
        
    }
}