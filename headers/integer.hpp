#ifndef INTEGER_HPP
#define INTEGER_HPP

#include "expression.hpp"

namespace april
{
    class Integer: public Expression
    {
        private:
            long long value;
        
        public:
            Integer(long long value):value(value) {}
            virtual Symbol* codeGen(CodeGenContext&);
    }; 
}

#endif //INTEGER_HPP