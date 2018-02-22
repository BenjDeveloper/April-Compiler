#include <vector>
#include <string>
#include "llvm/Transforms/Utils/Cloning.h"
#include "../include/function.hpp"
#include "../include/codegencontext.hpp"

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
        std::vector<llvm::Type*> args_type;

        for (auto var : *args)
        {
            llvm::Type* ty = context.typeOf(var->getIdentOfVarType());
            if (ty->isIntegerTy())
            {
                std::cout << "la variable es de tipo integer" << std::endl;
            }
            else 
            {
                std::cout << "la variable  NO es de tipo integer\n" << std::endl;
            }
            args_type.push_back(ty);
        } 

        llvm::FunctionType* fn_type = llvm::FunctionType::get(context.typeOf(*type), args_type, false);
        std::string fn_name = id->getName();
        if (type->getName() == "var")
        {
            fn_name += "_del";
        }

        llvm::Function* function = llvm::Function::Create(fn_type, llvm::GlobalValue::InternalLinkage, fn_name.c_str(), context.getModule());
        llvm::BasicBlock* bblock = llvm::BasicBlock::Create(context.getGlobalContext(), "entry", function, 0);
        context.pushBlock(bblock);
        // context.pushBlock(bblock, ScopeType::FunctionDeclaration);

        llvm::Function::arg_iterator actual_args = function->arg_begin();

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
        auto block_value = block->codeGen(context);
        if (block_value == nullptr)
        {
            std::cout << "Error, el cuerpo de la funcion esta vacio!!" << std::endl;
            exit(1);
        }

        auto re_ty = block_value->getType();

        if (type->getName() == "void")
        {
            if (context.currentBlock()->getTerminator() == nullptr)
            {
                llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
            }
        }

        if (context.currentBlock()->getTerminator() == nullptr)
        {
            if (type->getName() == "var" && !re_ty->isVoidTy())
            {
                llvm::ReturnInst::Create(context.getGlobalContext(), block_value, context.currentBlock());
            }
            else 
            {
                llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
            }
        }

        if (type->getName() == "var")
        {
            if (re_ty->isLabelTy() || re_ty->isMetadataTy())
            {
                context.popBlock();
                std::cout << "Error, la funcion retorna un tipo de dato no soportado!!!" << std::endl;
                exit(1);
            }

            llvm::FunctionType* fn_type_new = llvm::FunctionType::get(block_value->getType(), args_type, false);
            std::string fn_name_new = id->getName();

            llvm::Function* fn_new = llvm::Function::Create(fn_type_new, llvm::GlobalValue::InternalLinkage, fn_name_new.c_str(), context.getModule());

            llvm::ValueToValueMapTy v_map;
            llvm::Function::arg_iterator dest_i = fn_new->arg_begin();

            for (llvm::Function::const_arg_iterator J = function->arg_begin(); J != function->arg_end(); ++J)
            {
                dest_i->setName(J->getName());
                v_map[&*J] = &*dest_i++;
            }

            llvm::SmallVector<llvm::ReturnInst*, 8> Returns;
            llvm::CloneFunctionInto(fn_new, function, v_map, false, Returns);

            function->eraseFromParent();

            function = fn_new;
        }

        context.popBlock();
        return function;
    }
}