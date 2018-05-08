#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include "expression.hpp"

namespace april
{
    class Boolean: public Expression
    {
        private:
            std::string name;

        public:
            Boolean(std::string name):name(name) {}
            virtual Symbol* codeGen(CodeGenContext&);
    };
}

#endif //BOOLEAN_HPP