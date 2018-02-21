#include <iostream>
#include "../include/methodcall.hpp"
#include "../include/codegencontext.hpp"

//----------------------------

namespace april
{
    MethodCall::~MethodCall()
    {
        for (auto i : *arguments)
        {
            delete i;
        }
        arguments->clear();
        delete arguments;
        delete id;
    }

    llvm::Value* MethodCall::codeGen(CodeGenContext& context)
    {

        std::string fn_name = id->getName();

        llvm::Function* fn = context.getModule()->getFunction(fn_name.c_str());
        if (fn == nullptr)
        {
            std::cout << "Error: la funcion no existe" << std::endl;
            return nullptr;
        }

        std::vector<llvm::Value*> args;

        for (auto expr : *arguments)
        {
            args.push_back(expr->codeGen(context));
        }

        // ExpressionList::const_iterator it;
        // for (it = arguments->begin(); it != arguments->end(); it++) 
        // { 
        //     args.push_back((**it).codeGen(context)); 
        // }

        // llvm::CallInst *call = llvm::CallInst::Create(fn, llvm::makeArrayRef(args), "", context.currentBlock());
        llvm::CallInst* call = llvm::CallInst::Create(fn, args, "", context.currentBlock());
        std::cout << "la llamada al metodo: " << id->name << " fue generada!" << std::endl;
        return call;
    }
}