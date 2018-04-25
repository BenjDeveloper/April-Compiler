#include "../include/arrayaddelement.hpp"
#include "../include/codegencontext.hpp"
#include "../include/arrayaccess.hpp"
#include "../include/array.hpp"
#include "../include/assignment.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* ArrayAddElement::codeGen(CodeGenContext& context)
	{
		ExpressionList members;
		llvm::AllocaInst* var = context.searchVariable(ident->getName());


		auto var_type = var->getAllocatedType();
		auto var_struct_type = var_type->getContainedType(0);
		auto count = var_struct_type->getNumContainedTypes();

		for (decltype(count) i = 0; i < count; ++i)
		{
			members.push_back(new ArrayAccess{ ident, i });
		}
		members.push_back(expr);

		Array* array = new Array{ &members };
		llvm::Value* array_value = array->codeGen(context);

		context.locals().erase(ident->name);
		llvm::AllocaInst* alloc = new llvm::AllocaInst(array_value->getType(), ident->getName().c_str(), context.currentBlock());
		context.locals()[ident->getName()] = alloc;
		context.map_struct_type[ident->getName()] = alloc;
		new llvm::StoreInst(array_value, context.locals()[ident->getName()], false, context.currentBlock());
		return alloc;
		
		//-----------------------------------

		/*ExpressionList members;
		llvm::AllocaInst* var = context.searchVariable(ident->getName());
		

		auto var_type = var->getAllocatedType();
		auto var_struct_type = var_type->getContainedType(0);
		auto count = var_struct_type->getNumContainedTypes();
		
		for (decltype(count) i = 0; i < count; ++i)
		{
			members.push_back(new ArrayAccess{ ident, i });
		}
		members.push_back(expr);

		Array* array = new Array{&members};
		llvm::Value* array_value = array->codeGen(context);
		
		context.locals().erase(ident->name);
		llvm::AllocaInst* alloc = new llvm::AllocaInst(array_value->getType(), ident->getName().c_str(), context.currentBlock());
		context.locals()[ident->name] = alloc;
		new llvm::StoreInst(array_value, context.locals()[ident->getName()], false, context.currentBlock());
		return alloc;*/
	}
}