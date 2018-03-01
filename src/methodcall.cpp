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
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la funcion '"+id->getName()+"' no existe\n");
            context.addError();
            return nullptr;
        }

        if ((id->getName() != "println" && id->getName() != "print") && (arguments->size() != fn->arg_size()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los numeros de parametros no coinciden en la llamada a la funcion '"+id->getName()+"' \n");
            context.addError();
            return nullptr;
        }
        
        std::vector<llvm::Value*> args;

        for (auto expr : *arguments)
        {
            args.push_back(expr->codeGen(context));
        }
        
        if (id->getName() != "println" && id->getName() != "print")
        {
            bool cond = false;
            llvm::Function::arg_iterator actual_args = fn->arg_begin();
            for (auto para : args)
            {   
                if (actual_args->getType()->isIntegerTy() && para->getType()->isIntegerTy())
                {
                    cond = (actual_args->getType()->getIntegerBitWidth() < para->getType()->getIntegerBitWidth())?(true):(false);
                }
                else if(actual_args->getType()->isFloatingPointTy() && para->getType()->isFloatingPointTy())
                {
                    cond = (actual_args->getType()->getPrimitiveSizeInBits() < para->getType()->getPrimitiveSizeInBits())?(true):(false);
                }   
                else if (actual_args->getType()->isIntegerTy() && para->getType()->isFloatingPointTy())
                {
                    cond = true;
                }
                  
                if (cond)
                {
                    printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los parametros no coinciden en la llamada a la funcion '"+id->getName()+"' \n");
                    context.addError();
                    return nullptr;
                }
                ++actual_args;
            }
        }
        
        llvm::CallInst* call = llvm::CallInst::Create(fn, args, "", context.currentBlock());
        return call;
    }
}