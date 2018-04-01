#ifndef UNARYOPE_HPP
#define UNARYOPE_HPP

#include "expression.hpp"
#include "codegencontext.hpp"
#include "identifier.hpp"

namespace april
{
	class UnaryOpe: public Expression
	{
		private:
			int ope;
			Identifier* iden;

		public:
			UnaryOpe(Identifier* iden, int ope): iden(iden), ope(ope) {}
			~UnaryOpe() { }
			virtual llvm::Value* codeGen(CodeGenContext&);
			Type getType() { return Type::expression; }
	};
}

#endif //UNARYOPE_HPP