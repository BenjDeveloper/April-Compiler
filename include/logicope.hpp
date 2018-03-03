#ifndef LOGICOPE_HPP
#define LOGICOPE_HPP

#include "expression.hpp"
#include "codegencontext.hpp"

namespace april
{
	class LogicOpe: public Expression
	{
		private:
			int operation;
			Expression* hs;

		public:
			LogicOpe(int operation, Expression* hs): operation(operation), hs(hs){}
			~LogicOpe() 
			{ 
				if (hs != nullptr) { delete hs; } 
			}
			virtual llvm::Value* codeGen(CodeGenContext&);
			Type getType() { return Type::expression; }
	};
}

#endif //LOGICOPE_HPP