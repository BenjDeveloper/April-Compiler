#include <iostream>
#include "../include/methodcall.hpp"
#include "../include/codegencontext.hpp"

//----------------------------

namespace april
{
      llvm::Value* MethodCall::codeGen(CodeGenContext& context)
    {
        llvm::Function* fn = context.getModule()->getFunction(id.name.c_str());
        if (fn == nullptr)
        {
            std::cout << "Error: la funcion no existe" << std::endl;
            return nullptr;
        }

        std::vector<llvm::Value*> args;
        ExpressionList::const_iterator it;

        for (it = arguments.begin(); it != arguments.end(); it++) { args.push_back((**it).codeGen(context)); }

        llvm::CallInst *call = llvm::CallInst::Create(fn, llvm::makeArrayRef(args), "", context.currentBlock());
        std::cout << "la llamada al metodo: " << id.name << " fue generada!" << std::endl;
        return call;
    }
}