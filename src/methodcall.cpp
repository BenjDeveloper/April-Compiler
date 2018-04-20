#include <iostream>
#include "../include/methodcall.hpp"
#include "../include/codegencontext.hpp"
#include "../include/arrayaccess.hpp"
#include "../include/array.hpp"
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
		
        for (Expression* expr : *arguments)
        {
			llvm::Value* val_expr = expr->codeGen(context);
			/*if (val_expr->getType()->isPointerTy() && expr->__is_struct)
			{
				std::cout << "es una estructura bitches: " << ((expr->__is_struct) ? (1) : (0)) << std::endl;
				auto c = val_expr->getType()->getContainedType(0);
				std::cout << "cantidad: " << c->getNumContainedTypes() << std::endl;
			}*/
			args.push_back(val_expr);
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
				else if (para_fn->getType()->isPointerTy())
				{
					para = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(para, true, para_fn->getType(), true), para, para_fn->getType(), "cast", context.currentBlock());
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