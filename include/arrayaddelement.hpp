#ifndef ARRAY_ADD_ELEMENT_HPP
#define ARRAY_ADD_ELEMENT_HPP

#include "expression.hpp"
#include "identifier.hpp"
#include "statement.hpp"

namespace april
{
	class ArrayAddElement : public Statement
	{
	private:
		Expression * expr;
		Identifier* ident;

	public:
		ArrayAddElement(Identifier* ident, Expression* expr):ident(ident), expr(expr) { }
		~ArrayAddElement() {}
		virtual llvm::Value* codeGen(CodeGenContext&);
		Type getType() { return Type::expression; } //corregir a lista
	};
}

#endif //ARRAY_ADD_ELEMENT_HPP