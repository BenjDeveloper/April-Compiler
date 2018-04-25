#include <iostream>
#include "../include/methodcall.hpp"
#include "../include/codegencontext.hpp"
#include "../include/arrayaccess.hpp"
#include "../include/array.hpp"
#include "../include/errors.hpp"

//----------------------------
// Errors :: [171-180] node -> expression -> MethodCall
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
			return Errors::call(context, 171, april_errors->file_name, april_errors->line, id->getName());
        }

        if ( id->getName() != "_println" && id->getName() != "str_compare" && id->getName() != "str_concat"  && (arguments->size() != fn->arg_size()))
        {
			return Errors::call(context, 172, april_errors->file_name, april_errors->line, id->getName());
        }
        
        std::vector<llvm::Value*> args;
		
        for (Expression* expr : *arguments)
        {
			llvm::Value* expr_value = expr->codeGen(context);
			if (expr_value == nullptr)
			{
				return Errors::call(context, 174, april_errors->file_name, april_errors->line, id->getName());
			}
			args.push_back(expr_value);
		}
        
		int cont = 0;
		if (id->getName() != "_println" && id->getName() != "str_compare" && id->getName() != "str_concat")
		{
			bool cond = false;
			llvm::Function::arg_iterator para_fn = fn->arg_begin();
			for (llvm::Value*& para : args)
			{   
				if (para_fn->getType()->isDoubleTy() && para->getType()->isIntegerTy())
				{
					para = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(para, true, llvm::Type::getDoubleTy(context.getGlobalContext()), true), para, llvm::Type::getDoubleTy(context.getGlobalContext()), "cast", context.currentBlock());
				}
				else if (para_fn->getType() != para->getType())
				{
					return Errors::call(context, 173, april_errors->file_name, april_errors->line, id->getName());
				}

				++para_fn;
				cont++;
			}
		}
        llvm::CallInst* call = llvm::CallInst::Create(fn, args, "", context.currentBlock());
		return call;
    }
}