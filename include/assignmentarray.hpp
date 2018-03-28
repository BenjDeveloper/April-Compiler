#ifndef ASSIGNMENT_ARRAY
#define ASSIGNMENT_ARRAY

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
	class AssignmentArray : public Expression
	{
	private:
		Expression * left_expr = nullptr;
		Expression* right_expr = nullptr;
		
	public:
		AssignmentArray(Expression* left_expr, Expression* right_expr):left_expr(left_expr), right_expr(right_expr) { }
		~AssignmentArray() { }
		virtual llvm::Value* codeGen(CodeGenContext& context);
		Type getType() { return Type::expression; }
	};
}

#endif //ASSIGNMENT_ARRAY