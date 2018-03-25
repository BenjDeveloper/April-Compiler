#include <vector>
#include <string>
#include "llvm/Transforms/Utils/Cloning.h"
#include "../include/function.hpp"
#include "../include/codegencontext.hpp"

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
        for (auto var : *args)
        {
            llvm::Type* ty = context.typeOf(var->getIdentOfVarType());
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
        // context.pushBlock(bblock, ScopeType::FunctionDeclaration);

        llvm::Function::arg_iterator actual_args = function->arg_begin();
        // std::cout << "fn args_size: " << function->arg_size() << std::endl;
        // std::cout << "args_size: " << args_type.size() << std::endl;

        for (auto var : *args)
        {
            llvm::AllocaInst* alloca = llvm::dyn_cast<llvm::AllocaInst>(var->codeGen(context));
            std::string val_name = var->getVarName();

            if (alloca)
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

        // if (context.currentBlock()->getTerminator() == nullptr)
        // {
        //     if (type->getName() == "var" && !last_type->isVoidTy())
        //     {
        //         llvm::ReturnInst::Create(context.getGlobalContext(), block_value, context.currentBlock());
        //     }
        //     else 
        //     {
        //         llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
        //     }
        // }

        // if (type->getName() == "var")
        // {
        //     std::cout << "entro aqui!" << std::endl;
        //     if (last_type->isLabelTy() || last_type->isMetadataTy())
        //     {
        //         context.popBlock();
        //         printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la funcion retorna un tipo de dato no soportado\n");
        //         context.addError();
        //         return nullptr;
        //     }

        //     llvm::FunctionType* fn_type_new = llvm::FunctionType::get(block_value->getType(), args_type, false);
        //     std::string fn_name_new = id->getName();

        //     llvm::Function* fn_new = llvm::Function::Create(fn_type_new, llvm::GlobalValue::InternalLinkage, fn_name_new.c_str(), context.getModule());

        //     llvm::ValueToValueMapTy v_map;
        //     llvm::Function::arg_iterator dest_i = fn_new->arg_begin();

        //     for (llvm::Function::const_arg_iterator J = function->arg_begin(); J != function->arg_end(); ++J)
        //     {
        //         dest_i->setName(J->getName());
        //         v_map[&*J] = &*dest_i++;
        //     }

        //     llvm::SmallVector<llvm::ReturnInst*, 8> Returns;
        //     llvm::CloneFunctionInto(fn_new, function, v_map, false, Returns);

        //     function->eraseFromParent();

        //     function = fn_new;
        // }
        context.popBlock();
        return function;
    }
}