#include <iostream>
#include <typeinfo>
#include <memory>

#include "../include/codegencontext.hpp"
#include "../include/identifier.hpp"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

extern "C" void print(char* str, ...);
extern "C" void println(char* str, ...);
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
        if ((name.compare("int1") == 0) || (name.compare("bool") == 0))
        {
            return llvm::Type::getInt1Ty(getGlobalContext());
        }
        else if (name.compare("int8") == 0)
        {
            return llvm::Type::getInt8Ty(getGlobalContext());
        }
        else if (name.compare("int16") == 0)
        {
            return llvm::Type::getInt16Ty(getGlobalContext());
        }
        else if ((name.compare("int32") == 0) || (name.compare("int") == 0))
        {
            return llvm::Type::getInt32Ty(getGlobalContext());
        }
        else if (name.compare("int64") == 0)
        {
            return llvm::Type::getInt64Ty(getGlobalContext());
        }
        else if (name.compare("float") == 0)
        {
            return llvm::Type::getFloatTy(getGlobalContext());
        }
        else if (name.compare("double") == 0)
        {
            return llvm::Type::getDoubleTy(getGlobalContext());
        }
        else if (name.compare("string") == 0)
        {
            return llvm::Type::getInt8PtrTy(getGlobalContext());
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
        // std::cout << "existMainFunction--> " << existMainFunction << std::endl;
        if (!existMainFunction)
        {
            std::cout << "Falta la funcion 'main'" << std::endl; 
            return false;
        }
        std::cout << "*******************Generando codigo*******************" << std::endl;
        
		std::vector<llvm::Type*> argTypes;
        llvm::FunctionType* ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()), llvm::makeArrayRef(argTypes), false);
        mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage, name_main, module);
        llvm::BasicBlock* bblock = llvm::BasicBlock::Create(llvm::getGlobalContext(), name_main, mainFunction, 0);
        setupBuildFn();
        pushBlock(bblock);
        
        

        root.codeGen(*this);
        if (errors) 
        { 
            std::cout << "Compilacion con errores..." << std::endl; 
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


    void CodeGenContext::valOperator(llvm::Value* left_value , llvm::Value* right_value)
    {
        if (left_value->getType()->isIntegerTy() && right_value->getType()->isFloatingPointTy())
        {
            left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(left_value, true, right_value->getType(), true) , left_value, right_value->getType(), "cast", currentBlock() );
        }
        else if (left_value->getType()->isFloatingPointTy() && right_value->getType()->isIntegerTy())
        {
            left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode(right_value, true, left_value->getType(), true) , right_value, left_value->getType(), "cast", currentBlock() );
        }
        else if (left_value->getType()->isIntegerTy() && right_value->getType()->isIntegerTy())
        {
            if ( left_value->getType()->getIntegerBitWidth() < right_value->getType()->getIntegerBitWidth())
            {
                left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( left_value, true, right_value->getType(), true ), left_value, right_value->getType(), "cast", currentBlock() );   
            }
            else if  ( left_value->getType()->getIntegerBitWidth() > right_value->getType()->getIntegerBitWidth())
            {
                right_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( right_value, true, left_value->getType(), true ), right_value, left_value->getType(), "cast", currentBlock() );
            }
        }
        else if (left_value->getType()->isFloatingPointTy() && right_value->getType()->isFloatingPointTy())
        {
            if (right_value->getType()->isDoubleTy())
            {
                left_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( left_value, true, right_value->getType(), true ), left_value, right_value->getType(), "cast", currentBlock() ); 
            }
            else if  (left_value->getType()->isDoubleTy())
            {
                right_value = llvm::CastInst::Create( llvm::CastInst::getCastOpcode( right_value, true, left_value->getType(), true ), right_value, left_value->getType(), "cast", currentBlock() );
            }
        }
    }

}
