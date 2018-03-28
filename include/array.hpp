#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
	class Array : public Expression
	{
	private:
		ExpressionList* exprs;
	
	public:
		Array() {}
		Array(ExpressionList* exprs) :exprs(exprs) {}
		~Array() {}
		virtual llvm::Value* codeGen(CodeGenContext& context);
		ExpressionList* getExprs() { return exprs; }
		Type getType() { return Type::array; }
	};
}

#endif //ARRAY_HPP
