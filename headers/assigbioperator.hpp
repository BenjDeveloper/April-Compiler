#ifndef ASSIGBIOPERATOR_HPP
#define ASSIGBIOPERATOR_HPP

#include "expression.hpp"
#include "identifier.hpp"
#include "binaryope.hpp"

namespace april
{
    class AssigBioperator: public Expression
    {
        private:
            Identifier* ident;
            Expression* expr;
            OPE ope;

        public:
            AssigBioperator(Identifier* ident, OPE ope, Expression* expr): ident(ident), ope(ope), expr(expr) {}
            Symbol* codeGen(CodeGenContext&);
    };
}

#endif //ASSIGBIOPERATOR_HPP