#include <typeinfo>
#include <memory>
#include "node.h"
#include "codegen.h"
#include "parser.h"

#include "llvm/Transforms/IPO/PassManagerBuilder.h"

extern "C" void print(char* str, ...);
extern "C" void println(char* str, ...);

namespace april
{
    static llvm::Type* typeOf(const Identifier& type)
    {
        if (type.name.compare("int") == 0)
        {
            return llvm::Type::getInt64Ty(llvm::getGlobalContext());
        }
        else if (type.name.compare("float") == 0)
        {
            return llvm::Type::getDoubleTy(llvm::getGlobalContext());            
        }
        else if (type.name.compare("string") == 0)
        {
            return llvm::Type::getInt8PtrTy(llvm::getGlobalContext());
        }
        
        std::cout << ">>> Error no existe tipo: "<< type.name << " <<<" << std::endl;
        exit(1);
        return llvm::Type::getVoidTy(llvm::getGlobalContext());
    }

    void CodeGenContext::generateCode(Block& root)
    {
        std::cout << "*******************Generando codigo*******************" << std::endl;

        std::vector<llvm::Type*> argTypes;
        llvm::FunctionType* ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()), llvm::makeArrayRef(argTypes), false);
        mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::InternalLinkage, "main", module);
        llvm::BasicBlock* bblock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", mainFunction, 0);
        setupBuildFn();
        pushBlock(bblock);
        root.codeGen(*this);
        llvm::ReturnInst::Create(llvm::getGlobalContext(), bblock);
        popBlock();

        std::cout << "*******************Codigo generado*******************" << std::endl;
        module->dump();
        
        
        optimize();
        std::cout << "*******************Codigo Optimizado*******************" << std::endl;
        module->dump();
        std::cout << "*****************//Codigo Optimizado*******************" << std::endl;
        
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
        if( i != f->arg_end() )
            i->setName("format_str");
            
    }

    llvm::GenericValue CodeGenContext::runCode()
    {
        std::cout << "\n*******************Corriendo codigo*******************" << std::endl;
        std::string err;
        llvm::ExecutionEngine* ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
        assert(ee);
        ee->finalizeObject();
        std::vector<llvm::GenericValue> noargs;
        llvm::GenericValue v = ee->runFunction(mainFunction, noargs);
        delete ee;
        std::cout << "*******************Codigo corrido*******************" << std::endl;
        return v;
    }

    llvm::Value* Integer::codeGen(CodeGenContext& context)
    {
        std::cout << "Integer creado: " << value << std::endl;
        return llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvm::getGlobalContext()), value, true);
    }

    llvm::Value* Double::codeGen(CodeGenContext& context)
    {
        std::cout << "Double creado: " << value << std::endl;
        return llvm::ConstantFP::get(llvm::Type::getFloatTy(llvm::getGlobalContext()), value);
    }

    llvm::Value* Identifier::codeGen(CodeGenContext& context)
    {
        std::cout << "Identificador creado: " << name << std::endl;

        if (context.locals().find(name) == context.locals().end())
        {
            std::cout << "la variable no ha sido declarada" << std::endl;
            return NULL;
        }

        return new llvm::LoadInst(context.locals()[name], "", false, context.currentBlock());
    }

    llvm::Value* String::codeGen(CodeGenContext& context)
    {
        std::cout << "creando string: " << value << std::endl;
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

    llvm::Value* BinaryOperator::codeGen(CodeGenContext& context)
    {
        std::cout << "creando operacion binaria: " << op << std::endl;
        llvm::Instruction::BinaryOps instr;

        switch(op)
        {
            case TPLUS: 
                std::cout << "sumando :)" << std::endl;
                return llvm::BinaryOperator::Create(llvm::Instruction::Add, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
            case TMIN: 
                return llvm::BinaryOperator::Create(llvm::Instruction::Sub, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
            case TMUL: 
                return llvm::BinaryOperator::Create(llvm::Instruction::Mul, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
            case TDIV: 
                return llvm::BinaryOperator::Create(llvm::Instruction::SDiv, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
        }

        return NULL;
    }

    llvm::Value* Assignment::codeGen(CodeGenContext& context)
    {
        std::cout << "Creando asignacion para: " << lhs.name << std::endl;
        if (context.locals().find(lhs.name) == context.locals().end())
        {
            std::cerr << "la variable no ha sido declarada: " << lhs.name << std::endl;
            return NULL;
        }
        
        return new llvm::StoreInst(rhs.codeGen(context), context.locals()[lhs.name], false, context.currentBlock());
    }


    llvm::Value* Block::codeGen(CodeGenContext& context)
    {
        StatementList::const_iterator it;

        llvm::Value* last = NULL;

        for (it = statements.begin(); it != statements.end(); it++)
        {
            std::cout << "creando instruccion..." << std::endl;
            last = (**it).codeGen(context);
        }

        std::cout << "instruccion creada..." << std::endl;
        return last; 
    }

    llvm::Value* VariableDeclaration::codeGen(CodeGenContext& context)
    {
        std::cout << "Creating variable declaration " << type.name << ", " << id.name << std::endl;
        llvm::AllocaInst* alloc = new llvm::AllocaInst(typeOf(type), id.name.c_str(), context.currentBlock());
        context.locals()[id.name] = alloc;
        if (assignmentExpr != nullptr)
        {   
            Assignment assn(id, *assignmentExpr);
            assn.codeGen(context);
        }

        return alloc;
    }

    llvm::Value* ExpressionStatement::codeGen(CodeGenContext& context)
    {
        std::cout << "codigo generado para la expresion" << std::endl;
        return expression.codeGen(context);
    }

    llvm::Value* MethodCall::codeGen(CodeGenContext& context)
    {
        llvm::Function* fn = context.getModule()->getFunction(id.name.c_str());
        if (fn == nullptr)
        {
            std::cout << "Error: la funcion no existe" << std::endl;
            return nullptr;
        }

        std::vector<llvm::Value*> args;
        ExpressionList::const_iterator it;

        for (it = arguments.begin(); it != arguments.end(); it++) { args.push_back((**it).codeGen(context)); }

        llvm::CallInst *call = llvm::CallInst::Create(fn, llvm::makeArrayRef(args), "", context.currentBlock());
        std::cout << "la llamada al metodo: " << id.name << " fue generada!" << std::endl;
        return call;
    }
}