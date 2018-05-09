#ifndef BREAK_HPP
#define BREAK_HPP

#include "statement.hpp"

namespace april
{
    class Break: public Statement
    {
        public:
            Break() {}
            Symbol* codeGen(CodeGenContext&);
    };
}

#endif //BREAK_HPP