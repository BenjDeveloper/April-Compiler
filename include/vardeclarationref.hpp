#ifndef VAR_DECLARATION_REF
#define VAR_DECLARATION_REF

#include "identifier.hpp"
#include "expression.hpp"
#include "statement.hpp"

namespace april
{
	class VarDeclarationRef : public Statement
	{
	private:
		Identifier* id;
		Identifier* id_obj;
		Identifier* type;
		std::string type_name;
	public:
		VarDeclarationRef(Identifier* id, std::string type_name) :id(id), type(nullptr), id_obj(nullptr), type_name(type_name) { }
		VarDeclarationRef(Identifier* id, Identifier* type, Identifier* id_obj) :id(id), type(type), id_obj(id_obj) { }
		VarDeclarationRef(Identifier* id, Identifier* id_obj):id(id), type(nullptr), id_obj(id_obj) { }
		virtual llvm::Value* codeGen(CodeGenContext&);
		Type getType() { return Type::ref; }
	};
}

#endif //VAR_DECLARATION_REF