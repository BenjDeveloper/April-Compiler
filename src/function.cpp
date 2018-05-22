#include "../headers/function.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Function::~Function()
    {
        if (is_tmp && last != nullptr)
        {
            delete last;
        }

        if (is_tmp)
        {
            for (Symbol* s : locals)
            {
                delete s;
                s = nullptr;
            }
        }

        if (!is_tmp && ident != nullptr)
        {
            delete ident;
            ident = nullptr;
        }

        if (!is_tmp && block != nullptr)
        {
            delete block;
            block = nullptr;
        }

        if (!is_tmp)
        {
            for (VarDeclaration* arg : *args)
            {
                delete arg;
                args = nullptr;
            }
        }        
        
    }

    Symbol* Function::codeGen(CodeGenContext& context)
    {
        
        if (context.existFunction(ident->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la funcion '"+ident->getName()+"' ya existe.\n");
            context.addError();
            return nullptr;
        }
        
        if (!context.existFunction(ident->getName()))
            context.addFunction(ident->getName(), this);

        last = new Symbol{};
        return last;
    }

    Symbol* Function::runCode(CodeGenContext& context)
    {
        // std::cout << ">> ini fn: " << ident->getName() << " <<" << std::endl;
        Block* tmp_block = context.getCurrentBlock();
        std::vector<Symbol*> tmp_locals = context.getCurrentBlock()->locals;
        block->type_scope = BlockScope::FUNCTION;
        context.push_block(block);
        context.getCurrentBlock()->locals = locals;
        last = block->codeGen(context); //recorre las declaraciones

        // for (Symbol* s : context.getCurrentBlock()->locals)
        //      delete s;
        
        context.pop_block();
        context.setCurrentBlock(tmp_block);
        context.getCurrentBlock()->locals = tmp_locals;
        
        for (Symbol* s : locals)
            delete s;
        locals.clear();

        block->stop = false;
        // std::cout << ">> fin fn: " << ident->getName() << " <<" << std::endl;
        return last;
    }

    Symbol* Function::existIdenLocals(std::string name)
    {
        for (Symbol*& symbol : locals)
            if (symbol->name == name)
                return symbol;
        
        return nullptr;
    }
}