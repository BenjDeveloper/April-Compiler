#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <vector>
#include <fstream>

namespace april
{
    enum class Type
    {
        STRING,
        UNDEFINED,
        INTEGER,
        DOUBLE,
        BOOLEAN
    };

    union Value
    { 
        std::string* _sval;  
        long long _ival;
        double _dval;
        bool _bval;
    };

    class Symbol
    {
        public:
            std::string name;
            Type type;
            Value value;
            bool is_constant;
            bool is_variable;
        
        public:
            Symbol();
            bool operator!= (const Symbol&) const;
            bool operator== (const Symbol&) const;
            bool operator<= (const Symbol&) const;
            bool operator>= (const Symbol&) const;
            bool operator< (const Symbol&) const;
            bool operator> (const Symbol&) const;
            Symbol* operator+ (const Symbol&);
            Symbol* operator- (const Symbol&);
            Symbol* operator* (const Symbol&);
            Symbol* operator/ (const Symbol&);
            Symbol* operator= (const Symbol&);

            friend std::ostream& operator<< (std::ostream& out, const Symbol& sym);
    };
}

#endif //SYMBOL_HPP