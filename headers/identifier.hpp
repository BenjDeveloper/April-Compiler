#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include "expression.hpp"

namespace april
{
    class Identifier: public Expression
    {
        private:
            std::string name;
        
        public:
            Identifier(std::string name):name(name) {}
            virtual Symbol* codeGen(CodeGenContext&);
            std::string getName() { return name; }
    };
}

#endif //IDENTIFIER_HPP