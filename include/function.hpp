#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <regex>
#include "statement.hpp"
#include "identifier.hpp"
#include "block.hpp"
#include "vardeclaration.hpp"

extern bool existMainFunction;

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
            bool exist_main = false;

        public:
            Function(Identifier* type, Identifier* id, VarList* args, Block* block): type(type), id(id), args(args), block(block) 
            {
                std::regex re ("main\\.?[0-9]*");
                if (!existMainFunction && regex_match(id->getName(), re))
                {
                    existMainFunction = true;
                }
                else if (existMainFunction && regex_match(id->getName(), re))
                {
                    exist_main = true;
                }
            } 
            ~Function();
            llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::function; }
    };
}

#endif //FUNCTION_HPP