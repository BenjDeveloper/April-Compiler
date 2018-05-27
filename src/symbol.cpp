#include "../headers/symbol.hpp"
#include <fstream>


namespace april
{
    Symbol::Symbol()
    {
        in_list = false;
        prox = nullptr;
        down = nullptr;
    }

    bool Symbol::operator!= (const Symbol& sym) const
    {
        if (this->type == sym.type ) 
        {
            if (this->type == Type::INTEGER)
                return this->value._ival != sym.value._ival;

            else if (this->type == Type::DOUBLE)
                return this->value._dval != sym.value._dval;

            else if (this->type == Type::BOOLEAN)
                return this->value._bval != sym.value._bval;

            else if (this->type == Type::STRING)
                return *(this->value._sval) != *(sym.value._sval);
        }  
        return true;
    }

    bool Symbol::operator== (const Symbol& sym) const
    {
        if (this->type == sym.type ) 
        {
            if (this->type == Type::INTEGER)
                return this->value._ival == sym.value._ival;

            else if (this->type == Type::DOUBLE)
                return this->value._dval == sym.value._dval;

            else if (this->type == Type::BOOLEAN)
                return this->value._bval == sym.value._bval;
            
            else if (this->type == Type::STRING)
                return *(this->value._sval) == *(sym.value._sval);
        }  
        
        return false;
    }

    bool Symbol::operator<= (const Symbol& sym) const
    {
        if (this->type == sym.type ) 
        {
            if (this->type == Type::INTEGER)
                return this->value._ival <= sym.value._ival;

            else if (this->type == Type::DOUBLE)
                return this->value._dval <= sym.value._dval;

            else if (this->type == Type::BOOLEAN)
                return this->value._bval <= sym.value._bval;
            
            else if (this->type == Type::STRING)
                return *(this->value._sval) <= *(sym.value._sval);
        } 
        else if (this->type == Type::INTEGER && sym.type == Type::DOUBLE)
             return this->value._ival <= sym.value._dval;
        
        else if (this->type == Type::DOUBLE && sym.type == Type::INTEGER)
             return this->value._dval <= sym.value._ival;

        return false;
    }

    bool Symbol::operator>= (const Symbol& sym) const
    {
        if (this->type == sym.type ) 
        {
            if (this->type == Type::INTEGER)
                return this->value._ival >= sym.value._ival;

            else if (this->type == Type::DOUBLE)
                return this->value._dval >= sym.value._dval;

            else if (this->type == Type::BOOLEAN)
                return this->value._bval >= sym.value._bval;
            
            else if (this->type == Type::STRING)
                return *(this->value._sval) >= *(sym.value._sval);
        } 
        else if (this->type == Type::INTEGER && sym.type == Type::DOUBLE)
             return this->value._ival >= sym.value._dval;
        
        else if (this->type == Type::DOUBLE && sym.type == Type::INTEGER)
             return this->value._dval >= sym.value._ival;

        return false;
    }

    bool Symbol::operator< (const Symbol& sym) const
    {
        if (this->type == sym.type ) 
        {
            if (this->type == Type::INTEGER)
                return this->value._ival < sym.value._ival;

            else if (this->type == Type::DOUBLE)
                return this->value._dval < sym.value._dval;

            else if (this->type == Type::BOOLEAN)
                return this->value._bval < sym.value._bval;
            
            else if (this->type == Type::STRING)
                return *(this->value._sval) < *(sym.value._sval);
        } 
        else if (this->type == Type::INTEGER && sym.type == Type::DOUBLE)
             return this->value._ival < sym.value._dval;
        
        else if (this->type == Type::DOUBLE && sym.type == Type::INTEGER)
             return this->value._dval < sym.value._ival;

        return false;
    }

    bool Symbol::operator> (const Symbol& sym) const
    {
        if (this->type == sym.type ) 
        {
            if (this->type == Type::INTEGER)
                return this->value._ival > sym.value._ival;

            else if (this->type == Type::DOUBLE)
                return this->value._dval > sym.value._dval;

            else if (this->type == Type::BOOLEAN)
                return this->value._bval > sym.value._bval;

            else if (this->type == Type::STRING)
                return *(this->value._sval) > *(sym.value._sval);
        } 
        else if (this->type == Type::INTEGER && sym.type == Type::DOUBLE)
             return this->value._ival > sym.value._dval;
        
        else if (this->type == Type::DOUBLE && sym.type == Type::INTEGER)
             return this->value._dval > sym.value._ival;

        return false;
    }

    Symbol* Symbol::operator+ (Symbol& sym)
    {
        Symbol* tmp = new Symbol{};
        if ((this->type == Type::INTEGER || this->type == Type::DOUBLE) && (sym.type == Type::INTEGER || sym.type == Type::DOUBLE))
        {
            
            bool is_double = is_double = (this->type == Type::DOUBLE)?(true):((sym.type == Type::DOUBLE)?(true):(false));
            tmp->type = (is_double)?(Type::DOUBLE):(Type::INTEGER);
            tmp->is_variable = false; 
            
            if (is_double) { tmp->value._dval = ((this->type == Type::DOUBLE)?(this->value._dval):(this->value._ival)) + ((sym.type == Type::DOUBLE)?(sym.value._dval):(sym.value._ival)); }
            else { tmp->value._ival = this->value._ival + sym.value._ival; }
        }
        else if (this->type == Type::STRING)
        {
            std::string str1 = *(this->value._sval);
            std::string str2 = sym.value._sval->c_str();
            std::string str3 = str1 + str2;
            std::string* str4 = new std::string(str3);
            tmp->name = "";
            tmp->type = Type::STRING;
            tmp->value._sval = str4;
            tmp->is_constant = true;
            tmp->is_variable= false;
            //std::cout <<"Symbol - > "<< *tmp << std::endl;
        }
                
        return tmp;
    }

    Symbol* Symbol::operator- (const Symbol& sym)
    {
        Symbol* tmp =nullptr;
        if ((this->type == Type::INTEGER || this->type == Type::DOUBLE) && (sym.type == Type::INTEGER || sym.type == Type::DOUBLE))
        {
            tmp = new Symbol{};
            bool is_double = is_double = (this->type == Type::DOUBLE)?(true):((sym.type == Type::DOUBLE)?(true):(false));
            tmp->type = (is_double)?(Type::DOUBLE):(Type::INTEGER);
            tmp->is_variable = false; 

            if (is_double) { tmp->value._dval = ((this->type == Type::DOUBLE)?(this->value._dval):(this->value._ival)) - ((sym.type == Type::DOUBLE)?(sym.value._dval):(sym.value._ival)); }
            else { tmp->value._ival = this->value._ival - sym.value._ival; }
        }
        return tmp;
    }

    Symbol* Symbol::operator* (const Symbol& sym)
    {
        Symbol* tmp =nullptr;
        if ((this->type == Type::INTEGER || this->type == Type::DOUBLE) && (sym.type == Type::INTEGER || sym.type == Type::DOUBLE))
        {
            tmp = new Symbol{};
            bool is_double = is_double = (this->type == Type::DOUBLE)?(true):((sym.type == Type::DOUBLE)?(true):(false));
            tmp->type = (is_double)?(Type::DOUBLE):(Type::INTEGER);
            tmp->is_variable = false; 

            if (is_double) { tmp->value._dval = ((this->type == Type::DOUBLE)?(this->value._dval):(this->value._ival)) * ((sym.type == Type::DOUBLE)?(sym.value._dval):(sym.value._ival)); }
            else { tmp->value._ival = this->value._ival * sym.value._ival; }
        }
        return tmp;
    }

    Symbol* Symbol::operator/ (const Symbol& sym)
    {
        Symbol* tmp = nullptr;
        if ((this->type == Type::INTEGER || this->type == Type::DOUBLE) && (sym.type == Type::INTEGER || sym.type == Type::DOUBLE))
        {
            tmp = new Symbol{};
            tmp->type = Type::DOUBLE;
            tmp->is_variable = false; 
            tmp->value._dval = ((this->type == Type::DOUBLE)?(this->value._dval):(this->value._ival)) / ((sym.type == Type::DOUBLE)?(sym.value._dval):(sym.value._ival));
        }
        return tmp;
    }

    Symbol* Symbol::operator% (const Symbol& sym)
    {
        Symbol* tmp = nullptr;
        if (type == Type::INTEGER && sym.type == Type::INTEGER && sym.value._ival != 0)
        {
            tmp = new Symbol{};
            tmp->type = Type::INTEGER;
            tmp->is_variable = false; 
            tmp->value._ival = value._ival % sym.value._ival;
        }
        return tmp;
    }

    bool Symbol::operator&& (const Symbol& sym)
    {
        if (this->type == sym.type && this->type == Type::BOOLEAN)
        {
            return this->value._bval && sym.value._bval;
        }

        return false;
    }

    bool Symbol::operator|| (const Symbol& sym)
    {
        if (this->type == sym.type && this->type == Type::BOOLEAN)
        {
            return this->value._bval || sym.value._bval;
        }

        return false;
    }

    void Symbol::operator= (const Symbol& sym)
    {
        this->name = sym.name;
        this->type = sym.type;
        this->value = sym.value;
        this->is_constant = sym.is_constant;
        this->is_variable = sym.is_variable;
        this->prox = sym.prox;
        this->down = sym.down;
    }

    std::string Symbol::getType()
    {
        if (type == Type::INTEGER)
            return "integer";
        
        else if (type == Type::DOUBLE)
            return "double";
        
        else if (type == Type::BOOLEAN)
            return "boolean";
        
        else if (type == Type::UNDEFINED)
            return "undefined";
    }
    
    std::ostream& operator<< (std::ostream& out, const Symbol& sym)
    {
        if (sym.type == Type::INTEGER)
            out << sym.value._ival;
        
        else if (sym.type == Type::DOUBLE)
            out << sym.value._dval;
        
        else if (sym.type == Type::BOOLEAN)
            out << sym.value._bval;
        
        else if (sym.type == Type::STRING)
            out << sym.value._sval->c_str();
        
        return out;
    }
}