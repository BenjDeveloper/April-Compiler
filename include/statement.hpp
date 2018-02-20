#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "expression.hpp"

namespace april
{
    class Statement: public Expression
    {
        Type getType() { return Type::expression; }
	};
}

#endif //STATEMENT_HPP
