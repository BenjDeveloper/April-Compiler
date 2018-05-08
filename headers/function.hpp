#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "statement.hpp"
#include "identifier.hpp"
#include "block.hpp"
#include "vardeclaration.hpp"

namespace april
{
    class Function: public Statement 
    {
        private:
            Identifier* ident;
            VarList* args;
            Block* block;
            Symbol* last;
            std::vector<Symbol*> locals;

        public:
            Function(Identifier* ident, VarList* args, Block* block): ident(ident), args(args), block(block) {}
            ~Function();
            virtual Symbol* codeGen(CodeGenContext&);
            Symbol* runCode(CodeGenContext&);
            VarList*& getArgs() { return args; }
            std::vector<Symbol*>& getLocals() { return locals; }
            Symbol* existIdenLocals(std::string);
    };
}

#endif //FUNCTION_HPP