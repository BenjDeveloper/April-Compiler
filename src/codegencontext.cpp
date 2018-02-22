#include <iostream>
#include <typeinfo>
#include <memory>

#include "../include/codegencontext.hpp"
#include "../include/identifier.hpp"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

extern "C" void print(char* str, ...);
extern "C" void println(char* str, ...);

namespace april
{
    static const std::string name_main = "_pandicorn&kenshin";

    CodeGenContext::CodeGenContext()
    {
        errors = 0;
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();
        module = new llvm::Module(name_main, llvmContext);
    }

    void CodeGenContext::pushBlock(llvm::BasicBlock* block)
    {
		// std::cout << ">>> pushBlock <<<" << std::endl;
        blocks.push_front(new CodeGenBlock(block));
    }

    void CodeGenContext::popBlock()
    {
		if (blocks.size() > 0)
		{
			// std::cout << "<<< popBlock >>>" << std::endl;
			CodeGenBlock* top = blocks.front();
        	blocks.pop_front();
        	delete top;
		}
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
        if (name.compare("int") == 0)
        {
            return llvm::Type::getInt64Ty(getGlobalContext());
        }
        else if (name.compare("float") == 0)
        {
            return llvm::Type::getDoubleTy(getGlobalContext());
        }
        else if (name.compare("string") == 0)
        {
            return llvm::Type::getInt8PtrTy(getGlobalContext());
        }
        else if (name.compare("bool") == 0)
        {
            return llvm::Type::getInt1Ty(getGlobalContext());
        }
        else if (name.compare("void") == 0)
        {
            return llvm::Type::getVoidTy(getGlobalContext());
        }
        return llvm::Type::getVoidTy(getGlobalContext());
    }

	bool CodeGenContext::generateCode(Block& root)
    {
        std::cout << "*******************Generando codigo*******************" << std::endl;
        //----

		// std::cout << "programBlock.size(): " << root.statements.size() << std::endl;

		//----
		std::vector<llvm::Type*> argTypes;
        llvm::FunctionType* ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()), llvm::makeArrayRef(argTypes), false);
        mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage, name_main, module);
        llvm::BasicBlock* bblock = llvm::BasicBlock::Create(llvm::getGlobalContext(), name_main, mainFunction, 0);
        setupBuildFn();
        pushBlock(bblock);
        root.codeGen(*this);
        if (errors) 
        { 
            std::cout << "Compilation con errores. Abortando..." << std::endl; 
            return false;
        }

        if (currentBlock()->getTerminator() == nullptr)
        {
            llvm::ReturnInst::Create(getGlobalContext(), 0, currentBlock());
        }

        popBlock();

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
    void CodeGenContext::setupBuildFn()
    {
        auto intType = llvm::Type::getInt64Ty(llvm::getGlobalContext());
        std::vector<llvm::Type *>argTypesInt8Ptr(1, llvm::Type::getInt8PtrTy(llvm::getGlobalContext()));
        llvm::FunctionType * ft = nullptr;
        llvm::Function * f = nullptr;
        llvm::Function::arg_iterator i;

        ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()),argTypesInt8Ptr, true);
        f = llvm::Function::Create( ft, llvm::Function::ExternalLinkage, "print", getModule() );
        i = f->arg_begin();
        if( i != f->arg_end() ) { i->setName("format_str"); }
        ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()),argTypesInt8Ptr, true);
        f = llvm::Function::Create( ft, llvm::Function::ExternalLinkage, "println",getModule());
        i = f->arg_begin();
        if( i != f->arg_end() ) { i->setName("format_str");}

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
}
