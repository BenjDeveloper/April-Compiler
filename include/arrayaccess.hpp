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
		Expression* expr = nullptr;
		long long index = 0;

	public:
		ArrayAccess(Identifier* id, long long index) : id(id), index(index) {}
		ArrayAccess(Expression* expr, long long index) : expr(expr), index(index) {}
		virtual llvm::Value* codeGen(CodeGenContext& context);
		Type getType() { return Type::expression; }
	};
}

#endif //ARRAY_ACCESS_HPP