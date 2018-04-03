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

        if ( id->getName() != "println" && id->getName() != "str_compare" && id->getName() != "str_concat"  && (arguments->size() != fn->arg_size()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los numeros de parametros no coinciden en la llamada a la funcion '"+id->getName()+"' \n");
            context.addError();
            return nullptr;
        }
        
        std::vector<llvm::Value*> args;
		//-------------------
		if (arguments->size() && arguments->front()->getType() == Type::identifier) {
			Identifier* ident = (Identifier*) *(arguments->begin());
			// Check if it is a var of class type...
			llvm::AllocaInst* alloca = context.searchVariable(ident->getName());
			if (alloca != nullptr) {
				if (alloca->getType()->getElementType()->isStructTy()) {
					std::cout << "method call es una estructura!!!!" << std::endl;
					args.push_back(alloca);
					delete ident;
					arguments->erase(begin(*arguments));
				}
			}
		}
		//-------------------
        for (auto expr : *arguments)
        {
			/*if (context.func_args_refs[id->getName()][cont]) { args.push_back(context.locals()[id.name]) }
			else {  }*/
			args.push_back(expr->codeGen(context));
		}
        
		int cont = 0;
		if (id->getName() != "println" && id->getName() != "str_compare" && id->getName() != "str_concat")
		{
			bool cond = false;
			llvm::Function::arg_iterator para_fn = fn->arg_begin();
			for (llvm::Value*& para : args)
			{   
				if (para_fn->getType()->isIntegerTy() && para->getType()->isDoubleTy())
				{
					cond = true;
				}
				else if (para_fn->getType()->isDoubleTy() && para->getType()->isIntegerTy())
				{
					para = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(para, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), para, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast", context.currentBlock());
				}
				
				if (cond)
				{
					printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: los parametros no coinciden en la llamada a la funcion '"+id->getName()+"' \n");
					context.addError();
					return nullptr;
				}
				++para_fn;
				cont++;
			}
		}
        llvm::CallInst* call = llvm::CallInst::Create(fn, args, "", context.currentBlock());
        return call;
    }
}