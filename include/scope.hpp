#ifndef SCOPE_HPP
#define SCOPE_HPP
#include <iostream>
#include "statement.hpp"
#include "block.hpp"
#include "codegencontext.hpp"

namespace april
{
	class Scope: public Statement
	{
		private:
			Block* block;

		public:
			Scope(Block* block): block(block) {}
			~Scope() { delete block; }

			virtual llvm::Value* codeGen(CodeGenContext&);			
	};
}

#endif //SCOPE_HPP
