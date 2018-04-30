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
		mainblock = nullptr;
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

	llvm::AllocaInst* CodeGenContext::searchVariableAll(std::string name)
	{
		llvm::AllocaInst* result_variable = nullptr;

		result_variable = searchGlobalVariable(name);
		if (result_variable)
		{
			std::cout << "searchGlobalVariable(name);" << name << std::endl;
			return result_variable;
		}

		result_variable = searchVariable(name);
		if (result_variable)
		{
			std::cout<< "searchVariable(name);" << name << std::endl;
			return result_variable;
		}
		
		std::cout << "nullptr;" << std::endl;
		return result_variable;
	}

	llvm::AllocaInst* CodeGenContext::searchGlobalVariable(std::string name)
	{
		std::map<std::string, llvm::AllocaInst*>& variables = this->global;

		if (variables.find(name) != variables.end())
		{
			return variables[name];
		}
		return nullptr;
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
		mainblock = bblock;
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
		std::vector<llvm::Type *> argTypesInt8Ptr(1, llvm::Type::getInt8PtrTy(llvmContext));
		llvm::FunctionType * ft = nullptr;
		llvm::Function * f = nullptr;
		llvm::Function::arg_iterator i;
		int num_arg = 1;
		llvm::ArrayRef<llvm::Type*> args;

		//-----------------------------------------------------------------------------------
		//                                      LIB IN-OUT                                   
		//-----------------------------------------------------------------------------------
		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), argTypesInt8Ptr, true);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_print", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("format_str"); }

		//-----------------------------------------------------------------------------------
		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), argTypesInt8Ptr, true);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_println", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("format_str"); }

		//-----------------------------------------------------------------------------------
		std::vector<llvm::Type*> arg_iprintln;
		arg_iprintln.push_back(llvm::Type::getInt8PtrTy(llvmContext));
		arg_iprintln.push_back(llvm::Type::getInt32Ty(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), arg_iprintln, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_iprintln", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("var"); }

		//-----------------------------------------------------------------------------------
		std::vector<llvm::Type*> arg_iprintln2;
		arg_iprintln2.push_back(llvm::Type::getInt32Ty(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), arg_iprintln2, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_iprintln2", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("var"); }

		//-----------------------------------------------------------------------------------
		std::vector<llvm::Type*> arg_dprintln;
		arg_dprintln.push_back(llvm::Type::getInt8PtrTy(llvmContext));
		arg_dprintln.push_back(llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), arg_dprintln, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_dprintln", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("var"); }

		//-----------------------------------------------------------------------------------
		std::vector<llvm::Type*> arg_dprintln2;
		arg_dprintln2.push_back(llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), arg_dprintln2, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_dprintln2", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("var"); }

		//-----------------------------------------------------------------------------------
		std::vector<llvm::Type*> arg_sprintln;
		arg_sprintln.push_back(llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), arg_sprintln, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_sprintln", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("var"); }

		//-----------------------------------------------------------------------------------
		std::vector<llvm::Type*> Varg_sprint;
		Varg_sprint.push_back(llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getVoidTy(llvmContext), Varg_sprint, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_sprint", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("var"); }

		//-----------------------------------------------------------------------------------
		ft = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvmContext), args, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_input", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("var"); }

		//-----------------------------------------------------------------------------------
		//                                      LIB STRING                                   
		//----------------------------------------------------------------------------------- 
		num_arg = 2;
		std::vector<llvm::Type*> argCompare(num_arg, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), argCompare, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_strcompare", getModule());
		llvm::Function::arg_iterator arg_compare = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_compare->setName("_arg" + std::to_string(i));
			++arg_compare;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 2;
		std::vector<llvm::Type*> argConcat(num_arg, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvmContext), argConcat, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_strconcat", getModule());
		llvm::Function::arg_iterator arg_concat = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_concat->setName("_arg" + std::to_string(i));
			++arg_concat;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 2;
		std::vector<llvm::Type*> argCopy(num_arg, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvmContext), argCopy, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_strcopy", getModule());
		llvm::Function::arg_iterator arg_copy = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_copy->setName("_arg" + std::to_string(i));
			++arg_copy;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> argLength(num_arg, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), argLength, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_strlength", getModule());
		llvm::Function::arg_iterator arg_length = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_length->setName("_arg" + std::to_string(i));
			++arg_length;
		}

		//-----------------------------------------------------------------------------------
		//                                      LIB CONSTANT                                  
		//----------------------------------------------------------------------------------- 
		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), args, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_pi", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("_var_constPi"); }
		//-----------------------------------------------------------------------------------

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), args, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_e", getModule());
		i = f->arg_begin();
		if (i != f->arg_end()) { i->setName("_var_constE"); }


		//-----------------------------------------------------------------------------------
		//                                      LIB CAST                                  
		//----------------------------------------------------------------------------------- 
		num_arg = 1;
		std::vector<llvm::Type*> argf_str(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvmContext), argf_str, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_dstr", getModule());
		llvm::Function::arg_iterator arg_f_str = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_f_str->setName("_arg" + std::to_string(i));
			++arg_f_str;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> argi_str(num_arg, llvm::Type::getInt32Ty(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvmContext), argi_str, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_istr", getModule());
		llvm::Function::arg_iterator arg_i_str = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_i_str->setName("_arg" + std::to_string(i));
			++arg_i_str;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_sint(num_arg, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), Varg_sint, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_sint", getModule());
		llvm::Function::arg_iterator arg_sint = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_sint->setName("_arg" + std::to_string(i));
			++arg_sint;
		}

		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_sdou(num_arg, llvm::Type::getInt8PtrTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_sdou, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_sdou", getModule());
		llvm::Function::arg_iterator arg_sdou = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_sdou->setName("_arg" + std::to_string(i));
			++arg_sdou;
		}


		//-----------------------------------------------------------------------------------
		//                                      LIB MATH                                  
		//----------------------------------------------------------------------------------- 
		num_arg = 2;
		std::vector<llvm::Type*> Varg_imod(num_arg, llvm::Type::getInt32Ty(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), Varg_imod, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_imod", getModule());
		llvm::Function::arg_iterator arg_imod = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_imod->setName("_arg" + std::to_string(i));
			++arg_imod;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 2;
		std::vector<llvm::Type*> Varg_dmod(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_dmod, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_dmod", getModule());
		llvm::Function::arg_iterator arg_dmod = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_dmod->setName("_arg" + std::to_string(i));
			++arg_dmod;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_sqrt(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_sqrt, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_sqrt", getModule());
		llvm::Function::arg_iterator arg_sqrt = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_sqrt->setName("_arg" + std::to_string(i));
			++arg_sqrt;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_sin(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_sin, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_sin", getModule());
		llvm::Function::arg_iterator arg_sin = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_sin->setName("_arg" + std::to_string(i));
			++arg_sin;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_cos(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_cos, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_cos", getModule());
		llvm::Function::arg_iterator arg_cos = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_cos->setName("_arg" + std::to_string(i));
			++arg_cos;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_tan(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_tan, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_tan", getModule());
		llvm::Function::arg_iterator arg_tan = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_tan->setName("_arg" + std::to_string(i));
			++arg_tan;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_log(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_log, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_log", getModule());
		llvm::Function::arg_iterator arg_log = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_log->setName("_arg" + std::to_string(i));
			++arg_log;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 2;
		std::vector<llvm::Type*> Varg_irand(num_arg, llvm::Type::getInt32Ty(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), Varg_irand, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_irand", getModule());
		llvm::Function::arg_iterator arg_irand = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_irand->setName("_arg" + std::to_string(i));
			++arg_irand;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 1;
		std::vector<llvm::Type*> Varg_abs(num_arg, llvm::Type::getInt32Ty(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvmContext), Varg_abs, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_abs", getModule());
		llvm::Function::arg_iterator arg_abs = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_abs->setName("_arg" + std::to_string(i));
			++arg_abs;
		}
		//-----------------------------------------------------------------------------------
		num_arg = 2;
		std::vector<llvm::Type*> Varg_pow(num_arg, llvm::Type::getDoubleTy(llvmContext));

		ft = llvm::FunctionType::get(llvm::Type::getDoubleTy(llvmContext), Varg_pow, false);
		f = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "_pow", getModule());
		llvm::Function::arg_iterator arg_pow = f->arg_begin();
		for (int i = 0; i < num_arg; i++)
		{
			arg_pow->setName("_arg" + std::to_string(i));
			++arg_pow;
		}

		//-----------------------------------------------------------------------------------
		//                                      LIB HANDLE FILE                                  
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
