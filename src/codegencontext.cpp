#include <iostream>
#include <typeinfo>
#include <memory>

#include "../include/codegencontext.hpp"
#include "../include/identifier.hpp"
#include "../include/nativefn.hpp"

#include "llvm/Transforms/IPO/PassManagerBuilder.h"

extern april::STRUCINFO* april_errors;
extern bool existMainFunction;

namespace april
{
    static const std::string name_main = "_Pandicorn&KenshinUrashima";
	

    CodeGenContext::CodeGenContext()
    {
        errors = 0;
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();
        module = new llvm::Module("april", llvmContext);
    }

    void CodeGenContext::pushBlock(llvm::BasicBlock* block, llvm::FunctionType* fn)
    {
        blocks.push_front(new CodeGenBlock(block));
        stackFunctionType.push(fn);    
    }

    void CodeGenContext::popBlock()
    {
		if (blocks.size() > 0)
		{
			CodeGenBlock* top = blocks.front();
        	blocks.pop_front();
        	delete top;
		}
        if (stackFunctionType.size() > 0) { stackFunctionType.pop(); } 
    }

    llvm::AllocaInst* CodeGenContext::searchVariable(std::string name)
    {
        std::map<std::string, llvm::AllocaInst*>& variables = locals();

        if (variables.find(name) != variables.end())
        {
            return variables[name];
        }
        return nullptr;
    }

    llvm::Type* CodeGenContext::typeOf(const Identifier& id)
    {
        return this->typeOf(id.getName());
    }

    llvm::Type* CodeGenContext::typeOf(const std::string name)
    {
        if (name.compare("bool") == 0)
        {
            return llvm::Type::getInt1Ty(getGlobalContext());
        }
        else if (name.compare("int") == 0)
        {
            return llvm::Type::getInt32Ty(getGlobalContext());
        }
        else if (name.compare("double") == 0)
        {
            return llvm::Type::getDoubleTy(getGlobalContext());
        }
        else if (name.compare("string") == 0)
        {
            return llvm::Type::getInt8PtrTy(getGlobalContext());
        }
		else if (name.compare("array") == 0)
		{
			return llvm::Type::getVoidTy(getGlobalContext());
		}
        else if (name.compare("void") == 0)
        {
            return llvm::Type::getVoidTy(getGlobalContext());
        }
        Block::printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipo de dato '"+ name +"' no existe");
        addError();
        return nullptr;
        // return llvm::Tyspe::getVoidTy(getGlobalContext());
    }

	bool CodeGenContext::generateCode(Block& root)
    {
        if (!existMainFunction)
        {
            std::cout << "Falta la funcion 'main'" << std::endl; 
            return false;
        }
        
        std::cout << "*******************Generando codigo*******************" << std::endl;
		std::vector<llvm::Type*> argTypes;
		//llvm::FunctionType* ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()), llvm::makeArrayRef(argTypes), false);
		llvm::FunctionType* ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), argTypes, false);
		mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage, name_main, module);
		//mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage, name_main, getModule());
		//llvm::BasicBlock* bblock = llvm::BasicBlock::Create(llvm::getGlobalContext(), name_main, mainFunction, 0);
		llvm::BasicBlock* bblock = llvm::BasicBlock::Create(llvmContext, "entry", mainFunction, 0);
		setupBuildFn();
		pushBlock(bblock, nullptr);
		llvm::Value* result = root.codeGen(*this);

		if (errors) 
        { 
            // std::cout << "Compilacion con errores..." << std::endl; 
            return false;
        }
        //-----------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------
        std::string fn_main = "main";
        std::vector<llvm::Value*> args_prueba;
        llvm::Function* fn = getModule()->getFunction(fn_main.c_str());
        llvm::CallInst* call = llvm::CallInst::Create(fn, args_prueba, "", currentBlock());
        //-----------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------
        if (currentBlock()->getTerminator() == nullptr)
        {
            llvm::ReturnInst::Create(getGlobalContext(), 0, currentBlock());
        }
        popBlock();

		std::cout << "verificando construccion... " << std::endl;

		if (llvm::verifyModule(*getModule()))
		{
			std::cout << "Error al construir la funcion! " << std::endl;
			module->dump();
			return false;
		}

		std::cout << "hecho... :)" << std::endl;

        std::cout << "*******************Codigo generado*******************" << std::endl;
        module->dump();


        // optimize();
        // std::cout << "*******************Codigo Optimizado*******************" << std::endl;
        // module->dump();
        return true;
    }

    void CodeGenContext::optimize()
    {
        llvm::legacy::FunctionPassManager fmp(getModule());
        llvm::PassManagerBuilder builder;
        builder.OptLevel = 3;
        builder.populateFunctionPassManager(fmp);

        for (auto& fn: getModule()->getFunctionList())
        {
            fmp.run(fn);
        }

        fmp.run(*mainFunction);

    }

    //arreglar esta funcion
	//#define MAKE_LLVM_EXTERNAL_NAME(a) #a
    void CodeGenContext::setupBuildFn()
    {
        auto intType = llvm::Type::getInt32Ty(llvmContext);
        std::vector<llvm::Type *>argTypesInt8Ptr(1, llvm::Type::getInt8PtrTy(llvmContext));

        llvm::FunctionType * ft = nullptr;
        llvm::Function * f = nullptr;
        llvm::Function::arg_iterator i;

		//-----------------------------------------------------------------------------------
		//std::vector<llvm::Type*> args;
		llvm::ArrayRef<llvm::Type*> args;
		
		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), args, false);
		//f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, MAKE_LLVM_EXTERNAL_NAME(saludos), getModule());
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "saludos", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("prueba"); }
		//-----------------------------------------------------------------------------------

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), argTypesInt8Ptr, true);
		//f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, MAKE_LLVM_EXTERNAL_NAME(print), getModule());
		f = llvm::Function::Create( ft, llvm::Function::ExternalLinkage, "print", getModule());
        i = f->arg_begin();
        if( i != f->arg_end() ) { i->setName("format_str"); }

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), argTypesInt8Ptr, true);
		//f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, MAKE_LLVM_EXTERNAL_NAME(println), getModule());
		f = llvm::Function::Create( ft, llvm::Function::ExternalLinkage, "println", getModule());
        i = f->arg_begin();
        if( i != f->arg_end() ) { i->setName("format_str"); }
    }

    llvm::GenericValue CodeGenContext::runCode()
    {
        std::cout << "\n*******************Corriendo codigo*******************" << std::endl;
        std::string err;
		llvm::ExecutionEngine* ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).setErrorStr(&err).setEngineKind(llvm::EngineKind::JIT).create();
		assert(ee);
		assert(mainFunction);

        ee->finalizeObject();

		std::vector<llvm::GenericValue> noargs;
        llvm::GenericValue v = ee->runFunction(mainFunction, noargs);
		delete ee;
        std::cout << "*******************Codigo corrido*******************" << std::endl;
        return v;
    }

    void CodeGenContext::valOperator(llvm::Value*& left_value , llvm::Value*& right_value)
    {
		if (left_value->getType()->isIntegerTy() && right_value->getType()->isDoubleTy())
		{
			left_value = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(left_value, true, llvm::Type::getDoubleTy(getGlobalContext()), true), left_value, llvm::Type::getDoubleTy(getGlobalContext()), "cast_double", currentBlock());
		}
		else if (left_value->getType()->isDoubleTy() && right_value->getType()->isIntegerTy())
		{
			right_value = llvm::CastInst::Create(llvm::CastInst::getCastOpcode(right_value, true, llvm::Type::getDoubleTy(getGlobalContext()), true), right_value, llvm::Type::getDoubleTy(getGlobalContext()), "cast_double", currentBlock());
		}
    }

}
