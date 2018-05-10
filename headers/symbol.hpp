#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <vector>
#include <fstream>

namespace april
{
    enum class Type
    {
        UNDEFINED,
        INTEGER,
        DOUBLE,
        BOOLEAN,
        STRING,
        LIST
    };

    union Value
    {
        long long _ival;
        double _dval;
        bool _bval;
        std::string* _str;
        std::vector<class Symbol*>* _list;
    };

    class Symbol
    {
        public:
            std::string name;
            Type type;
            Value value;
            bool is_constant;
            bool is_variable;
            Symbol* prox;
            Symbol* down;

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
            void operator= (const Symbol&);
            bool operator&& (const Symbol&);
            bool operator|| (const Symbol&);

            std::string getType();
            friend std::ostream& operator<< (std::ostream& out, const Symbol& sym);
    };
}

#endif //SYMBOL_HPP