#ifndef CONDITIONAL_HPP
#define CONDITIONAL_HPP

#include "statement.hpp"
#include "comparasionope.hpp"
#include "block.hpp"
#include "expression.hpp"

namespace april
{
	class Conditional: public Statement
	{
		private:
			Expression* expr;
			Block& then_block;
			Block else_block;
			bool has_else;

		public:
			Conditional(Expression* expr, Block& then_block): expr(expr), then_block(then_block), has_else(false) {}
			Conditional(Expression* expr, Block& then_block, Block& else_block): expr(expr), then_block(then_block), else_block(else_block), has_else(true) {}
			~Conditional() { }
			virtual llvm::Value* codeGen(CodeGenContext&);
			Type getType() { return Type::expression; }
	};
}


#endif //CONDITIONAL_HPP
