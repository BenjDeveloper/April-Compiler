#include "../headers/methodstruct.hpp"
#include "../headers/methodhandlelist.hpp"
#include "../headers/methodhandlestring.hpp"
#include "../headers/methodhandlefile.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* MethodStruct::codeGen(CodeGenContext& context)
    {   
        if (ident_var == nullptr && expr_var == nullptr)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: ident y expr no definidos.\n");
            context.addError();
            return nullptr;
        }

        if (ident_var != nullptr && !context.existIdenLocals(ident_var->getName()))
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la variable '"+ident_var->getName()+"' no esta definida.\n");
            context.addError();
            return nullptr;
        }

        Symbol* sym_expr = nullptr;
        if (ident_var != nullptr)
            sym_expr = context.findIdentLocals(ident_var->getName());
        else
            sym_expr = expr_var->codeGen(context);

        Symbol* tmp = nullptr;
        if (sym_expr->type == Type::LIST)
        {
            MethodHandleList* methodhandlelist = new MethodHandleList(sym_expr, ident_method, args);
            tmp = methodhandlelist->codeGen(context);
        }
        else if (sym_expr->type == Type::STRING)
        {
            MethodHandleString* methodhandlestring = new MethodHandleString(sym_expr, ident_method, args);
            tmp = methodhandlestring->codeGen(context);
        }
        else if (sym_expr->type == Type::FILE)
        {
            MethodHandleFile* methodhandlefile = new MethodHandleFile(sym_expr, ident_method, args);
            tmp = methodhandlefile->codeGen(context);
        }
        else
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: no existe el metodo dentro del tipo de dato.\n");
            context.addError();
            return nullptr;
        }

        return tmp;
    }
}