#ifndef COMPARASION_OPE_HPP
#define COMPARASION_OPE_HPP

#include "expression.hpp"
#include "codegencontext.hpp"

namespace april
{

	class ComparasionOpe: public Expression
	{
		private:
			int operation;
			Expression& lhs;
			Expression& rhs;

		public:
			ComparasionOpe(Expression& lhs, int operation, Expression& rhs): lhs(lhs), operation(operation), rhs(rhs) {}
			virtual llvm::Value* codeGen(CodeGenContext&);
			int getOperation() { return operation; }
			Expression& getLHS() { return lhs; }
			Expression& getRHS() { return rhs; }
			Type getType() { return Type::expression; }
	};

}

#endif //COMPARASION_OPE_HPP
