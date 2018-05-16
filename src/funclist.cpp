#include "../headers/funclist.hpp"
#include <regex>

namespace april
{
    namespace list
    {
        Symbol* size(Symbol* root)
        {
            Symbol* aux = root->prox;
            int cont = 0;
            while (aux != nullptr)
            {
                aux = aux->prox;
                cont += 1;
            }

            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::INTEGER;
            tmp->value._ival = cont;
            tmp->is_constant = true;
            tmp->is_variable = false;

            return tmp;
        }

        Symbol* append(Symbol* root, Symbol* sym)
        {
            Symbol* aux = root;

            while (aux->prox != nullptr)
                aux = aux->prox;

            aux->prox = new Symbol{};
            aux = aux->prox;
            if (sym->type != Type::LIST)
            {
                aux->name = "";
                aux->type = sym->type;
                aux->value = sym->value;
                aux->is_constant = true;
                aux->is_variable = false;
                aux->in_list = true;
            }
            else
            {
                aux->type = Type::LIST_DOWN;
                aux->in_list = true;
                Symbol* node = sym;
                aux->down = clone(node);
            }

            return root;
        }

        Symbol* clone (Symbol* node)
        {
            Symbol* result = new Symbol{};
            Symbol* itera = result;
            
            while (node != nullptr)
            {
                itera->name = "";
                itera->type = node->type;
                itera->value = node->value;
                itera->is_constant = true;
                itera->is_variable = false;
                itera->in_list = true;
               
                if (node->type == Type::LIST_DOWN)
                    itera->down = clone(node->down);
                else
                    itera->value = node->value;
                
                node = node->prox;
                if (node != nullptr)
                {
                    itera->prox = new Symbol{};
                    itera = itera->prox;
                }
            }

            return result;
        }


        Symbol* index(Symbol* root, Symbol* sym)
        {
            Symbol* aux = root->prox;
            int cont = 0;
            bool exist = false;
            while ( aux != nullptr)
            {
                if ((*aux == *sym) == true)
                {
                    exist = true;
                    break;
                }
                cont += 1;
                aux = aux->prox;
            }
        
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::INTEGER;
            tmp->value._ival = (exist)?(cont):(-1);
            tmp->is_constant = true;
            tmp->is_variable = false;
            return tmp;
        }  

        Symbol* remove(Symbol* root, Symbol* sym)
        {
            Symbol* aux = root;
            
            while ( aux != nullptr && aux->prox != nullptr)
            {
                if ((*aux->prox == *sym) == true)
                {
                    Symbol* tmp = aux->prox;
                    aux->prox = tmp->prox;
                    delete tmp;
                    break;
                }
                aux = aux->prox;
            }

            return root;
        } 
    }

    
    namespace string
    {
        Symbol* size(Symbol* root)
        {
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::INTEGER;
            tmp->value._ival = root->value._sval->length();
            tmp->is_constant = true;
            tmp->is_variable = false;
            return tmp;
        }

        bool isNumber(Symbol* element)
        {
            std::regex re("[0-9]+(\\.[0-9]+)?");

            if (regex_match(*(element->value._sval), re))
                return true;

            return false;
        }  
    } 

    namespace cast 
    {
        Symbol* toDouble(Symbol* element)
        {
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::DOUBLE;
            tmp->is_constant = true;
            tmp->is_variable = false;

            if (element->type == Type::DOUBLE)
                tmp->value._dval = element->value._dval;
             
            else if (element->type == Type::INTEGER)
                tmp->value._dval = double(element->value._ival);    
            
            else if (element->type == Type::STRING)
                tmp->value._dval = double(std::atof(element->value._sval->c_str()));
            
            return tmp;
        }

        Symbol* toInt(Symbol* element){} //CHIAVE

        Symbol* toString(Symbol* element){} //CHIAVE
    }
}