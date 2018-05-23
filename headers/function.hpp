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
            bool is_tmp;

        public:
            Function(Identifier* ident, VarList* args, Block* block): ident(ident), args(args), block(block), is_tmp(false) {}
            Function(Identifier* ident, VarList* args, Block* block, bool is_tmp): ident(ident), args(args), block(block), is_tmp(is_tmp) {}
            ~Function();
            virtual Symbol* codeGen(CodeGenContext&);
            Symbol* runCode(CodeGenContext&);
            VarList* getArgs() const { return args; }
            Identifier* getIdent() const { return ident; }
            Block* getBlock() const { return block; }
            std::vector<Symbol*>& getLocals() { return locals; }
            Symbol* existIdenLocals(std::string);
            std::string getName() const { return ident->getName(); }
            bool isTmp() const { return is_tmp; }
    };
}

#endif //FUNCTION_HPP