#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include "statement.hpp"
#include "expression.hpp"

namespace april
{
    using StatementList = std::vector<Statement*>;
    
    class Block: public Expression
    {
        public:
            StatementList statements;
        
        public:
            Block() {}
            virtual llvm::Value* codeGen(april::CodeGenContext&);
            Type getType() { return Type::expression; }
    };
}

#endif //BLOCK_HPP