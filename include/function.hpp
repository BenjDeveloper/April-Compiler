#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "statement.hpp"
#include "identifier.hpp"
#include "block.hpp"
#include "vardeclaration.hpp"

namespace april
{
    using VarList = std::vector<class VariableDeclaration*>;
    
    class Function: public Statement
    {
        private:
            Identifier* type;
            Identifier* id;
            VarList* args;
            Block* block;

        public:
            Function(Identifier* type, Identifier* id, VarList* args, Block* block): type(type), id(id), args(args), block(block) {} 
            Function(Identifier* id, VarList* args, Block* block): type(new Identifier("var")), id(id), args(args), block(block) {} 
            ~Function();
            llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::function; }
    };
}

#endif //FUNCTION_HPP