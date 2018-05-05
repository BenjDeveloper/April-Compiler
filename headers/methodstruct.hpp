#ifndef METHOD_STRUCT_HPP
#define METHOD_STRUCT_HPP

#include <string>
#include <vector>
#include "identifier.hpp"
#include "expression.hpp"

namespace april
{
    class MethodStruct : public Expression
    {
        private:
            Identifier* ident;
            Identifier* method;
            ExpressionList* args;
            std::vector<Symbol*> methods;

        public:
            MethodStruct();
            Symbol* codeGen(CodeGenContext&);
            Identifier* getIdent(){return ident;}
            Identifier* getMethod(){return method;}
            ExpressionList* getArgs(){return args;}
            std::vector<Symbol*> getMethods(){return methods;}
            Symbol* findMethods(std::string);
            void call();
    };
}

#endif //METHOD_STRUCT_HPP