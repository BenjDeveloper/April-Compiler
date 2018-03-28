#include "../include/assignmentarray.hpp"
#include "../include/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	llvm::Value* AssignmentArray::codeGen(CodeGenContext& context)
	{
		llvm::Value* left_code = left_expr->codeGen(context);
		if (left_code == nullptr)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: al generar la expresion del arreglo.\n");
			context.addError();
			return nullptr;
		}

		llvm::Value* right_code = right_expr->codeGen(context);
		if (right_code == nullptr)
		{
			printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: al asignar la expresion al arreglo.\n");
			context.addError();
			return nullptr;
		}
		
		return new llvm::StoreInst(right_code, left_expr->_ptr, context.currentBlock());
	}
}