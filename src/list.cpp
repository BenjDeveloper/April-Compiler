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
        Symbol* sym = new Symbol{};
        sym->type = Type::LIST;
        Symbol* aux = sym;

        for (Expression* expr : *expressions)
        {
            Symbol* tmp = expr->codeGen(context);
            Symbol* _new = new Symbol{};
            _new->name = "";
            _new->type = tmp->type;
            _new->value = tmp->value;
            _new->is_constant = true;
            _new->is_variable = false;

            if (tmp->type == Type::LIST)
            {
                _new->prox = tmp->prox;
                _new->down = tmp->down;
            }

            if (tmp->type == Type::LIST)
            {
                aux->prox = new Symbol{};
                aux = aux->prox;
                aux->down = _new;
            }
            else
            {
                aux->prox = _new;
                aux = aux->prox;
            }
        }

        // aux = sym;
        // int cont = 0;
        // aux = aux->prox;    

        // while (aux != nullptr)
        // {
        //     cont++;
        //     aux = aux->prox;
        // }
        //std::cout << "size: " << cont << std::endl;
        return sym;
    }
}