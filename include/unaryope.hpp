#ifndef UNARYOPE_HPP
#define UNARYOPE_HPP

#include "expression.hpp"
#include "codegencontext.hpp"


namespace april
{
	class UnaryOpe: public Expression
	{
		private:
			int operation;
			Expression& rhs;

		public:
			UnaryOpe(int operation, Expression& rhs): operation(operation), rhs(rhs) {}
			virtual llvm::Value* codeGen(CodeGenContext&);
			Type getType() { return Type::expression; }
	};
}

#endif //UNARYOPE_HPP
