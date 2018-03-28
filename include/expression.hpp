#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "node.hpp"

namespace april
{
    class Expression: public Node 
    {
	public:
		llvm::Instruction* _ptr = nullptr; //puntero de acceso en la asignacion de variables dentro de un arreglo
	};
}

#endif //EXPRESSION_HPP