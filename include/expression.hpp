#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "node.hpp"

namespace april
{
    class Expression: public Node 
    {
	public:
		llvm::Instruction* _ptr = nullptr; //puntero de acceso en la asignacion de variables dentro de un arreglo
		llvm::Type* _expr_ref_type = nullptr;
		bool __is_struct;
		long long* __int_value = nullptr;
	};
}

#endif //EXPRESSION_HPP