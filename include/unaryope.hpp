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
			int operation;
			Expression* hs;
			Identifier* ident;

		public:
			UnaryOpe(int operation, Expression* hs, Identifier* ident): operation(operation), hs(hs), ident(ident) {}
			~UnaryOpe() 
			{ 
				// if (hs != nullptr) { delete hs; } 
				// if (ident != nullptr) { delete ident; } 
			}
			virtual llvm::Value* codeGen(CodeGenContext&);
			Type getType() { return Type::expression; }
	};
}

#endif //UNARYOPE_HPP