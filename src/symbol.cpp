#include "../headers/symbol.hpp"
#include <fstream>


namespace april
{
    Symbol::Symbol()
    {
        
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
        } 
        else if (this->type == Type::INTEGER && sym.type == Type::DOUBLE)
             return this->value._ival > sym.value._dval;
        
        else if (this->type == Type::DOUBLE && sym.type == Type::INTEGER)
             return this->value._dval > sym.value._ival;

        return false;
    }

    Symbol* Symbol::operator+ (const Symbol& sym)
    {
        Symbol* tmp =nullptr;
        if ((this->type == Type::INTEGER || this->type == Type::DOUBLE) && (sym.type == Type::INTEGER || sym.type == Type::DOUBLE))
        {
            tmp = new Symbol{};
            bool is_double = is_double = (this->type == Type::DOUBLE)?(true):((sym.type == Type::DOUBLE)?(true):(false));
            tmp->type = (is_double)?(Type::DOUBLE):(Type::INTEGER);

            if (is_double) { tmp->value._dval = ((this->type == Type::DOUBLE)?(this->value._dval):(this->value._ival)) + ((sym.type == Type::DOUBLE)?(sym.value._dval):(sym.value._ival)); }
            else { tmp->value._ival = this->value._ival + sym.value._ival; }
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

            if (is_double) { tmp->value._dval = ((this->type == Type::DOUBLE)?(this->value._dval):(this->value._ival)) * ((sym.type == Type::DOUBLE)?(sym.value._dval):(sym.value._ival)); }
            else { tmp->value._ival = this->value._ival * sym.value._ival; }
        }
        return tmp;
    }

    Symbol* Symbol::operator/ (const Symbol& sym)
    {
        Symbol* tmp =nullptr;
        if ((this->type == Type::INTEGER || this->type == Type::DOUBLE) && (sym.type == Type::INTEGER || sym.type == Type::DOUBLE))
        {
            tmp = new Symbol{};
            bool is_double = is_double = (this->type == Type::DOUBLE)?(true):((sym.type == Type::DOUBLE)?(true):(false));
            tmp->type = (is_double)?(Type::DOUBLE):(Type::INTEGER);

            if (is_double) { tmp->value._dval = ((this->type == Type::DOUBLE)?(this->value._dval):(this->value._ival)) / ((sym.type == Type::DOUBLE)?(sym.value._dval):(sym.value._ival)); }
            else { tmp->value._ival = this->value._ival / sym.value._ival; }
        }
        return tmp;
    }


    std::ostream& operator<< (std::ostream& out, const Symbol& sym)
    {
        if (sym.type == Type::INTEGER)
            out << sym.value._ival;
        
        else if (sym.type == Type::DOUBLE)
            out << sym.value._dval;
        
        else if (sym.type == Type::BOOLEAN)
            out << sym.value._bval;

        return out;
    }

}