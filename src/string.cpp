#include <iostream>
#include "../include/string.hpp"
#include "../include/codegencontext.hpp"

//----------------------------
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/ManagedStatic.h"

namespace april
{
    llvm::Value* String::codeGen(CodeGenContext& context)
    {
        // std::cout << "creando string: " << value << std::endl;
        llvm::ArrayType* array_type = llvm::ArrayType::get(llvm::IntegerType::get(context.getGlobalContext(), 8), value.size()+1);
        llvm::GlobalVariable* gvar = new llvm::GlobalVariable(*context.getModule(), array_type, true, llvm::GlobalValue::PrivateLinkage, 0, ".str");
        
        gvar->setAlignment(1);
        llvm::Constant* const_array = llvm::ConstantDataArray::getString(context.getGlobalContext(), value); 
        gvar->setInitializer(const_array);
        std::vector<llvm::Constant*> const_ptr_8_indices;
        llvm::ConstantInt* const_int = llvm::ConstantInt::get(context.getGlobalContext(), llvm::APInt(64, llvm::StringRef("0"), 10));
        const_ptr_8_indices.push_back(const_int);
        const_ptr_8_indices.push_back(const_int);
        llvm::Constant* const_ptr_8 = llvm::ConstantExpr::getGetElementPtr(array_type, gvar, const_ptr_8_indices);
        return const_ptr_8;
        // return llvm::ConstantFP::get(llvm::Type::getLabelTy(llvm::getGlobalContext()), value);
    }
}