#include <vector>
#include <string>
#include <fstream>
#include "llvm/Transforms/Utils/Cloning.h"
#include "../include/function.hpp"
#include "../include/codegencontext.hpp"
#include "../include/assignment.hpp"
#include "../include/arrayaccess.hpp"
#include "../include/array.hpp"
#include "../include/identifier.hpp"

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
			std::cout << "TYPE: " << var->getIdentOfVarType().getName() << std::endl;
			if (context.map_struct_type.find(var->getIdentOfVarType().getName()) != context.map_struct_type.end())
			{
				ty = context.map_struct_type[var->getIdentOfVarType().getName()]->getAllocatedType();
				ty = llvm::PointerType::get(ty, 0);
			}
			else
				ty = context.typeOf(var->getIdentOfVarType());

			args_type.push_back(ty);
		} 
		std::cout << "POMPOM" << std::endl;
        if (context.typeOf(*type) == nullptr)
        {   
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede crear la funcion '"+id->name+"'\n");
            context.addError();
            return nullptr;
        }

		llvm::FunctionType* fn_type = fn_type = llvm::FunctionType::get(context.typeOf(*type), args_type, false);
        
		std::string fn_name = id->getName();
      
		if (type->getName() == "var")
            fn_name += "_del";

        llvm::Function* function = llvm::Function::Create(fn_type, llvm::GlobalValue::InternalLinkage, fn_name.c_str(), context.getModule());
        llvm::BasicBlock* bblock = llvm::BasicBlock::Create(context.getGlobalContext(), "entry", function, 0);
        context.pushBlock(bblock, fn_type, ScopeType::Function);

		std::cout << "BEFORE" << std::endl;
        llvm::Function::arg_iterator actual_args = function->arg_begin();
		for (auto var : *args)
        {
			std::cout << "var: " << var->getVarName() << std::endl;
            llvm::AllocaInst* alloc = llvm::dyn_cast<llvm::AllocaInst>(var->codeGen(context));
			std::string val_name = var->getVarName();
			
			if (alloc != nullptr)
			{
				if (alloc->getAllocatedType()->isPointerTy())
					val_name += "_addr";

				actual_args->setName(val_name);
				if (var->getVarTypeName() != "list" && !(context.map_struct_type.find(var->getVarTypeName()) != context.map_struct_type.end()))
				{
					std::cout << "LOLOL" << std::endl;
					new llvm::StoreInst(&(*actual_args), alloc, context.currentBlock());
				}
			}
			++actual_args;
        }
		std::cout << "AFTER" << std::endl;

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

		if (context.currentBlock()->getTerminator() == nullptr) 
		{
			if (type->getName() != "void" && !last_type->isVoidTy()) 
			{
				llvm::ReturnInst::Create(context.getGlobalContext(), block_value, context.currentBlock());
			}
			else 
			{
				llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
			}
		}
        context.popBlock();
        return function;
    }
}

