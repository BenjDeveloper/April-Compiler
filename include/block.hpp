#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include "statement.hpp"
#include "expression.hpp"


namespace april
{
    using StatementList = std::vector<Statement*>;
    
    class Block: public Expression
    {
        public:
            StatementList statements;
        
        public:
            Block() {}
            ~Block() 
			{
				std::cout << "Borrando declaraciones..." << std::endl;
				for (auto i: statements) { delete i; }
				statements.clear();
				std::cout << "declaraciones borradas..." << std::endl;
			}
			virtual llvm::Value* codeGen(CodeGenContext&);
            Type getType() { return Type::expression; }
    
	};
}

#endif //BLOCK_HPP
