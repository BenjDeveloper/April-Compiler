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
    static const std::string name_main = "_Pandicorn&Kenshin";

    CodeGenContext::CodeGenContext()
    {
		scope = ScopeType::Block;
        errors = 0;
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();
        module = new llvm::Module("april", llvmContext);
    }

    void CodeGenContext::pushBlock(llvm::BasicBlock* block, llvm::FunctionType* fn, ScopeType scope)
    {
        blocks.push_front(new CodeGenBlock(block));
        stackFunctionType.push(fn);    
		this->scope = scope;
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
		else if (name.compare("void") == 0)
        {
            return llvm::Type::getVoidTy(getGlobalContext());
        }
		else if (name.compare("list") == 0)
		{
			std::vector<llvm::Type*> typeList;
			llvm::StructType* _array = llvm::StructType::create(getGlobalContext(), llvm::makeArrayRef(typeList), "list");
			return _array;
		}
		else
		{
			if (map_struct_type.find(name) != map_struct_type.end())
			{
				std::cout << "entra aqui!!: " << name << std::endl;
				llvm::AllocaInst* alloc = map_struct_type[name];
				return alloc->getAllocatedType();
			}
		}

        Block::printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: tipo de dato '"+ name +"' no existe");
        addError();
        return nullptr;
    }

	bool CodeGenContext::generateCode(Block& root)
    {
        /*if (!existMainFunction)
        {
            std::cout << "Falta la funcion 'main'" << std::endl; 
            return false;
        }*/
        
        std::cout << "*******************Generando codigo*******************" << std::endl;
		std::vector<llvm::Type*> argTypes;
		llvm::FunctionType* ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), argTypes, false);
		mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage, name_main, module);
		llvm::BasicBlock* bblock = llvm::BasicBlock::Create(llvmContext, "entry", mainFunction, 0);
		setupBuildFn();
		pushBlock(bblock, nullptr, ScopeType::Block);
		llvm::Value* result = root.codeGen(*this);

		if (errors) { return false; }
        
		//-----------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------
        /*std::string fn_main = "main";
        std::vector<llvm::Value*> args_prueba;
        llvm::Function* fn = getModule()->getFunction(fn_main.c_str());
        llvm::CallInst* call = llvm::CallInst::Create(fn, args_prueba, "", currentBlock());*/
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

		//-----------------------------------------------------------------------------------
		//std::vector<llvm::Type*> args;
		std::vector<llvm::Type*> para(1, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), para, true);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "str_compare", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("_var_p"); }

		//-----------------------------------------------------------------------------------
		//std::vector<llvm::Type*> args;
		std::vector<llvm::Type*> argConcat(1, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvmContext), argConcat, true);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "str_concat", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("_var_concat"); }
		//-----------------------------------------------------------------------------------
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

	void CodeGenContext::renameVariable(std::string oldVarName, std::string newVarName)
	{
		ValueNames& names = locals();
		if (names.find(oldVarName) != names.end()) {
			auto value = names[oldVarName];
			names.erase(oldVarName);
			names[newVarName] = value;

			std::map<std::string, std::string>& typeMap = blocks.front()->getTypeMap();
			if (typeMap.count(oldVarName)) {
				auto value = typeMap[oldVarName];
				typeMap.erase(oldVarName);
				typeMap[newVarName] = value;
			}
		}
	}

	std::string CodeGenContext::getType(std::string varName)
	{
		if (blocks.front()->getTypeMap().find(varName) != blocks.front()->getTypeMap().end())
			return blocks.front()->getTypeMap()[varName];

		return std::string("");
	}

	void CodeGenContext::deleteVariable(std::string varName)
	{
		ValueNames& names = locals();
		auto& typeMap = blocks.front()->getTypeMap();
		if (names.find(varName) != names.end())
		{
			names.erase(varName);
			if (typeMap.count(varName))
			{
				typeMap.erase(varName);
			}
		}
	}
}
