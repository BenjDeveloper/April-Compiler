#include <iostream>
#include "../include/msg.hpp"

namespace april
{
	// # <- revisar descripcion 

	std::string Msg::Mtitle = " ******** FAILED COMPILATION ********";
	std::string Msg::Mcode = "  Code: ";
	std::string Msg::Mfile = "  File: ";
	std::string Msg::Mline = "  Line: ";
	std::string Msg::Mmessage = " Fault: ";

	std::string Msg::M000 = "Failure not supported.";

	// [1-10] node -> statemente -> vardeclaration
	std::string Msg::M001 = "Duplicate variable declaration.";
	std::string Msg::M002 = "Unsupported data type.";
	std::string Msg::M003 = "The assignment value has not been declared";  //#  PANDICORNIO
	std::string Msg::M004 = "Bad assignment of a variable type 'int' to 'double'";
	std::string Msg::M005 = "Assignment of unsupported types.";
	
	// [11-20] node -> statemente -> vardeclarationdeduce
	std::string Msg::M011 = Msg::M001;
	std::string Msg::M012 = "The variable could not be initialized because the expression do not declared.";
	std::string Msg::M013 = "The assignment to the variable is empty.";
	
	// [21-30] node -> expression -> Assignment
	std::string Msg::M021 = "The variable has not been declared in the assignment.";
	std::string Msg::M022 = "The expression is incorrect in the assignment.";
	std::string Msg::M023 = "Bad assignment of a variable type";
	
	// [31-40] node -> expression -> AssigBioperator
	std::string Msg::M031 = "Null assignment.";
	std::string Msg::M032 = "The variable has not been declared.";
	std::string Msg::M033 = "Evaluating the expression.";
	std::string Msg::M034 = ".";                                           //#  PANDICORNIO
	
	// [41-50] node -> expression -> BinaryOperator
	std::string Msg::M041 = "Evaluating the expression in the binary operation.";

	// [51-60] node -> expression -> Block

	// [61-70] node -> expression -> Boolean

	// [71-80] node -> expression -> CodeGenContext

	// [81-90] node -> expression -> ComparasionOpe
	std::string Msg::M081 = "when evaluating the expression in the comparison.";
	std::string Msg::M082 = "unknown operator.";

	// [91-100] node -> expression -> Conditional
	std::string Msg::M091 = "the block 'then' is empty.";

	// [101-110] node -> expression -> Double

	// [111-120] node -> expression -> ExpressionStatement

	// [121-130] node -> expression -> ForLoop
	std::string Msg::M121 = "missing 'then' block implementation in the for.";
	std::string Msg::M122 = "failure evaluating the conditional expression of the 'for'.";
	std::string Msg::M123 = "failure the evaluation block 'for'.";

	// [131-140] node -> expression -> Function
	std::string Msg::M131 = "the function was already defined.";
	std::string Msg::M132 = "when the function is being created.";
	std::string Msg::M133 = "the body of the function is empty.";

	// [141-150] node -> expression -> Identifier
	std::string Msg::M141 = Msg::M032;

	// [151-160] node -> expression -> Integer

	// [161-170] node -> expression -> LogicOpe
	std::string Msg::M161 = "the operand has to be of the 'integer' type.";
	std::string Msg::M162 = "the unary operator is not defined.";

	// [171-180] node -> expression -> MethodCall
	std::string Msg::M171 = "the function does not exist.";
	std::string Msg::M172 = "Parameter numbers do not match the call to the function.";
	std::string Msg::M173 = "The parameters do not match in the call to the function.";
	std::string Msg::M174 = "The parameter(s) of function have not been declared.";

	// [181-190] node -> expression -> nativefn

	// [191-200] node -> expression -> Return
	std::string Msg::M191 = "type of return different in function.";

	// [201-210] node -> expression -> Scope

	// [211-220] node -> expression -> String

	// [221-230] node -> expression -> UnaryOpe
	std::string Msg::M221 = "the unary operator is not defined.";
	
}
  