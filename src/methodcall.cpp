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

        if ( id->getName() != "println" && (arguments->size() != fn->arg_size()))
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
        
        
		if (id->getName() != "println")
		{
			bool cond = false;
			llvm::Function::arg_iterator para_fn = fn->arg_begin();
			for (llvm::Value*& para : args)
			{   
				std::cout << "para_fn " << ((para_fn->getType()->isPointerTy()) ? (true) : (false)) << std::endl;
				std::cout << "para " << ((para->getType()->isPointerTy()) ? (true) : (false)) << std::endl;
				if (para_fn->getType()->isIntegerTy() && para->getType()->isDoubleTy())
				{
					cond = true;
				}
				else if (para_fn->getType()->isDoubleTy() && para->getType()->isIntegerTy())
				{
					para = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(para, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), para, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast", context.currentBlock());
				}
				else if (para->getType()->isPointerTy() && para_fn->getType()->isStructTy())
				{
					std::cout << "son punteros" << std::endl;
					//para = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(para, true, para_fn->getType(), true), para, para_fn->getType(), "cast", context.currentBlock());
					/////======================







				}
				if (cond)
				{
					printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los parametros no coinciden en la llamada a la funcion '"+id->getName()+"' \n");
					context.addError();
					return nullptr;
				}
				++para_fn;
			}
		}
        llvm::CallInst* call = llvm::CallInst::Create(fn, args, "", context.currentBlock());
		std::cout << "finallll" << std::endl;
        return call;
    }
}