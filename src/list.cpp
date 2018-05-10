#include "../headers/list.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    List::~List()
    {
        for (Expression* expr : *expressions)
        {
            delete expr;
            expr = nullptr;
        }
    }

    Symbol* List::codeGen(CodeGenContext& context)
    {
        std::cout << "size list: " << expressions->size() << std::endl;
        Symbol* sym = new Symbol{};
        sym->type = Type::LIST;
        Symbol* aux = sym;

        for (Expression* expr : *expressions)
        {
            Symbol* tmp = expr->codeGen(context);
            
            if (tmp->type == Type::LIST)
            {
                aux->prox = new Symbol{};
                aux = aux->prox;
                aux->down = tmp;
                std::cout << ">> down <<" << std::endl; 
            }
            else
            {
                aux->prox = tmp;
                std::cout << ">> NO down <<" << std::endl; 
                aux = aux->prox;
            }
        }

        //std::cout << "creacion de list" << std::endl;
        
        aux = sym;
        int cont = 0;

        //aux = aux->down;
        aux = aux->prox;    
        while (aux != nullptr)
        {
            cont++;
            aux = aux->prox;
        }
        std::cout << "size: " << cont << std::endl;

        return sym;
    }
}