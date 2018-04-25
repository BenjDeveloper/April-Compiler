#ifndef ARRAY_ACCESS_HPP
#define ARRAY_ACCESS_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
	class ArrayAccess : public Expression
	{
	private:
		Identifier* id = nullptr;
		Expression* expr_index = nullptr;
		Expression* expr = nullptr;
		long long _index = 0;

	public:
		ArrayAccess(Identifier* id, Expression* expr_index) : id(id), expr_index(expr_index) {}
		ArrayAccess(Expression* expr, Expression* expr_index) : expr(expr), expr_index(expr_index) {}
		ArrayAccess(Identifier* id, long long _index) : id(id), _index(_index) {}
		ArrayAccess(Expression* expr, long long _index) : expr(expr), _index(_index) {}
		virtual llvm::Value* codeGen(CodeGenContext& context);
		Type getType() { return Type::expression; }
	};
}

#endif //ARRAY_ACCESS_HPP