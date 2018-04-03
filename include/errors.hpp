#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "node.hpp"
#include "msg.hpp"

namespace april
{
	class Errors: public Node
	{
	public:
		static llvm::Value* call(CodeGenContext& context ,int errorNumber, std::string file, int line, std::string name);
		 
	private:
		Errors() {}
	};
}

#endif //ERRORS_HPP