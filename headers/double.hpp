#ifndef DOUBLE_HPP
#define DOUBLE_HPP

#include "expression.hpp"

namespace april
{
    class Double: public Expression
    {
        private:
            double value;
        
        public:
            Double(double value):value(value) {}
            virtual Symbol* codeGen(CodeGenContext&);
    }; 
}

#endif //DOUBLE_HPP