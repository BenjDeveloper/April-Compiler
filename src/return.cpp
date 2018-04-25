#include "../include/return.hpp"
#include "../include/codegencontext.hpp"
#include "../include/errors.hpp"

//----------------------------
// Errors :: [191-200] node -> expression -> Return
extern april::STRUCINFO* april_errors;

namespace april
{
    llvm::Value* Return::codeGen(CodeGenContext& context)
    {
        llvm::Value* expr_value = nullptr;
        if (expr != nullptr)
        {
            //llvm::Value* expr_value = expr->codeGen(context);
            expr_value = expr->codeGen(context);
            if (expr_value == nullptr) { return nullptr; }
            //context.getCurrentFunctionType()

            llvm::Type* expr_type = expr_value->getType();
            llvm::Type* ret_func_type = context.getCurrentFunctionType()->getReturnType();
            bool error_type = false;
            if (expr_type->isIntegerTy() && ret_func_type->isIntegerTy())
            {
                if (expr_type->getIntegerBitWidth() > ret_func_type->getIntegerBitWidth())
                {
                    error_type = true; 
                }
                else if (expr_type->getIntegerBitWidth() < ret_func_type->getIntegerBitWidth())
                {
                    llvm::Type* new_type = llvm::Type::getIntNTy(context.getGlobalContext(), ret_func_type->getIntegerBitWidth());
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, new_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, new_type, "cast", context.currentBlock());   
                }
            }
            else if (expr_type->isFloatingPointTy() && ret_func_type->isFloatingPointTy())
            {
                if (expr_type->getPrimitiveSizeInBits() > ret_func_type->getPrimitiveSizeInBits())
                {
                    error_type = true;
                }
                else if (expr_type->getPrimitiveSizeInBits() < ret_func_type->getPrimitiveSizeInBits())
                {
                    auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, ret_func_type, true);
                    expr_value = llvm::CastInst::Create(cast_instr, expr_value, ret_func_type, "cast", context.currentBlock()); 
                }
            }
            else if (expr_type->isIntegerTy() && ret_func_type->isFloatingPointTy())
            {
                auto cast_instr = llvm::CastInst::getCastOpcode(expr_value, true, ret_func_type, true);
                expr_value = llvm::CastInst::Create(cast_instr, expr_value, ret_func_type, "cast", context.currentBlock());
            }
            else if (expr_type->isFloatingPointTy() && ret_func_type->isIntegerTy())
            {
                error_type = true;
            }

            if (error_type)
            {
				return Errors::call(context, 191, april_errors->file_name, april_errors->line, "");
            }

            
            llvm::ReturnInst::Create(context.getGlobalContext(), expr_value, context.currentBlock());            
            return expr_value;
        }
        else
        {
            llvm::ReturnInst::Create(context.getGlobalContext(), 0, context.currentBlock());
        }
        return nullptr;
    }
}