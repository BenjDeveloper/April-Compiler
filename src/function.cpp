#include <vector>
#include <string>
#include "llvm/Transforms/Utils/Cloning.h"
#include "../include/function.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"

extern april::STRUCINFO* april_errors;

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
        bool ban = false;
		//std::cout << "Inicio funcion: " << id->getName() << std::endl;

        std::regex re (id->getName()+"\\.?[0-9]*");
        for (std::string& n : context.namesFunctions) { if (regex_match(n, re)) { ban = true; } }

        if (ban == true)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la funcion '"+id->name+"' ya fue definida");
            context.addError();
            return nullptr;
        }
        context.namesFunctions.push_back(id->getName());

        std::vector<llvm::Type*> args_type;
		llvm::Type* ty = nullptr;
        for (auto var : *args)
        {
			
			ty = context.typeOf(var->getIdentOfVarType());
			args_type.push_back(ty);
        } 

        if (context.typeOf(*type) == nullptr)
        {   
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede crear la funcion '"+id->name+"'\n");
            context.addError();
            return nullptr;
        }

        llvm::FunctionType* fn_type = llvm::FunctionType::get(context.typeOf(*type), args_type, false);
        std::string fn_name = id->getName();
        if (type->getName() == "var")
        {
            fn_name += "_del";
        }

        llvm::Function* function = llvm::Function::Create(fn_type, llvm::GlobalValue::InternalLinkage, fn_name.c_str(), context.getModule());
        llvm::BasicBlock* bblock = llvm::BasicBlock::Create(context.getGlobalContext(), "entry", function, 0);
        context.pushBlock(bblock, fn_type);


		//std::cout << "uno function!: " << std::endl;
        llvm::Function::arg_iterator actual_args = function->arg_begin();
        for (auto var : *args)
        {
			//std::cout << "fn: " << id->getName() << "; para: " << var->getVarName() << "; ref: " << var->isRef() << std::endl;
            llvm::AllocaInst* alloca = llvm::dyn_cast<llvm::AllocaInst>(var->codeGen(context));
			std::string val_name = var->getVarName();
			if (alloca != nullptr)
			{
                if (alloca->getAllocatedType()->isPointerTy())
                {
                    val_name += "_addr";
                }
                actual_args->setName(val_name);
				new llvm::StoreInst(&(*actual_args), alloca, context.currentBlock());
			}
			++actual_args;
        }
		//std::cout << "dos function!: " << std::endl;

        // genera el cuerpo de la funcion
        llvm::Value* block_value = block->codeGen(context);
        if (block_value == nullptr)
        {
            if (context.typeOf(*type)->isVoidTy())
            {
                llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
                context.popBlock();
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el cuerpo de la funcion esta vacio\n");
                context.addError();
            }
            return nullptr;
        }
        
        llvm::Type* last_type = block_value->getType();
        llvm::Type* func_type = context.typeOf(*type);
        
        if (type->getName() == "void")
        {
            if (context.currentBlock()->getTerminator() == nullptr)
            {
                llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
            }
        }

		if (context.currentBlock()->getTerminator() == nullptr) {
			if (type->getName() != "void" && !last_type->isVoidTy()) {
				llvm::ReturnInst::Create(context.getGlobalContext(), block_value, context.currentBlock());
			}
			else {
				llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
			}
		}

		//if (type->getName() != "void")
		//{
		//	// Now create the a new function (the real one) since we know the return type now.
		//	llvm::FunctionType *ftypeNew = llvm::FunctionType::get(block_value->getType(), args_type, false);
		//	std::string functionNameNew = id->getName();
		//	

		//	llvm::Function *functionNew = llvm::Function::Create(ftypeNew, llvm::GlobalValue::InternalLinkage, functionNameNew, context.getModule());

		//	// Create a value map for all arguments to be mapped to the new function.
		//	llvm::ValueToValueMapTy VMap;
		//	llvm::Function::arg_iterator DestI = functionNew->arg_begin();

		//	for (llvm::Function::const_arg_iterator J = function->arg_begin(); J != function->arg_end(); ++J) {
		//		DestI->setName(J->getName()); // Copy name of argument to the argument of the new function.
		//		VMap[&*J] = &*DestI++; // Map the value 
		//	}

		//	// Clone the function to the new (real) function w/ the correct return type.
		//	llvm::SmallVector<llvm::ReturnInst*, 8> Returns;  // Ignore returns cloned.
		//	CloneFunctionInto(functionNew, function, VMap, false, Returns);

		//	// Remove the old one.
		//	function->eraseFromParent();

		//	function = functionNew;
		//}

        context.popBlock();
		//std::cout << "Fin funcion" << std::endl;

        return function;
    }
}