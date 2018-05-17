#include "../headers/methodhandleIo.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    MethodHandleIo::~MethodHandleIo()
    {

    }

    Symbol* MethodHandleIo::codeGen(CodeGenContext& context)
    {
        Expression* expr_arg = nullptr;
        Symbol* sym_arg = nullptr;

        if (ident_method->getName() == "input")
        {
            if (args->size() == 0)
                return io::input();
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: este metodo no requiere entrada de parametros.\n");
                context.addError();
                return nullptr;
            }
        }

        if (args->size() == 0)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no han declarado ningun parametros.\n");
            context.addError();
            return nullptr;
        }


        if (ident_method->getName() == "print")
            io::_print();

        for(Expression* expr_arg: *args)
        {
            sym_arg = expr_arg->codeGen(context);
            if (sym_arg->is_variable)
                sym_arg = context.findIdentLocals(sym_arg->name);
                
            if (sym_arg == nullptr)
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: en el pase de parametros.\n");
                context.addError();
                return nullptr;
            }

            if (sym_arg->type == Type::BOOLEAN || sym_arg->type == Type::LIST || sym_arg->type == Type::LIST_DOWN || sym_arg->type == Type::UNDEFINED)
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no se puede convertir el tipo de dato del parametro.\n");
                context.addError();
                return nullptr;
            }
 
            if (ident_method->getName() == "println")
            {
                io::println(sym_arg);
            } 
            else if (ident_method->getName() == "print")
            {
                io::print(sym_arg);
            }
            else
            {
                printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el nombre '"+ident_method->getName()+"' no esta definida.\n");
                context.addError();
                return nullptr;
            }
        }
        return nullptr;
    }
}