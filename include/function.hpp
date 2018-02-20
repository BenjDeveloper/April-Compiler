#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "statement.hpp"
#include "identifier.hpp"
#include "block.hpp"

namespace april
{
    class Function: public Statement
    {
        private:
            Identifier* type;
            Identifier* id;
            VarList* args;
            Block* block;

        public:
            Function(Identifier* type, Identifier* id, VarList* args, Block* block): type(type), id(id), args(args), block(block) {} 
            Function(Identifier* id, VarList* args, Block* block): type(new Idetifier("var")), id(id), args(args), block(block) {} 
            ~Function();
            llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::function; }
    };
}

#endif //FUNCTION_HPP