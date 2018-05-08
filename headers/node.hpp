#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include "symbol.hpp"

namespace april
{
    class CodeGenContext;
    using ExpressionList = std::vector<class Expression*>;
    using VarList = std::vector<class VarDeclaration*>;

    typedef struct STRUCINFO
    {
        int line;
        std::string file_name;
    } STRUCINFO;

    class Node
    {
        public:
            virtual Symbol* codeGen(CodeGenContext&) = 0;
            static void printError(std::string msg)
            {
                std::cerr << msg.c_str() << std::endl;
            }
    };
}

#endif //NODE_HPP