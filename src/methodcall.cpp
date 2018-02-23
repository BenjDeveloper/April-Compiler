#include <iostream>
#include "../include/methodcall.hpp"
#include "../include/codegencontext.hpp"

//----------------------------
extern april::STRUCINFO* april_errors;

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
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la funcion no existe\n");
            context.addError();
            return nullptr;
        }

        std::vector<llvm::Value*> args;

        for (auto expr : *arguments)
        {
            args.push_back(expr->codeGen(context));
        }

        llvm::CallInst* call = llvm::CallInst::Create(fn, args, "", context.currentBlock());
        return call;
    }
}