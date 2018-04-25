#ifndef MSG_HPP
#define MSG_HPP


namespace april
{
	class Msg
	{
	public:
		static std::string Mtitle;
		static std::string Mcode;
		static std::string Mfile;
		static std::string Mline;
		static std::string Mmessage;

		static std::string M000; //999 errors

								 // [1-10] node -> statemente -> vardeclaration
		static std::string M001;
		static std::string M002;
		static std::string M003;
		static std::string M004;
		static std::string M005;

		// [11-20] node -> statemente -> vardeclarationdeduce
		static std::string M011;
		static std::string M012;
		static std::string M013;

		// [21-30] node -> expression -> Assignment
		static std::string M021;
		static std::string M022;
		static std::string M023;

		// [31-40] node -> expression -> AssigBioperator
		static std::string M031;
		static std::string M032;
		static std::string M033;
		static std::string M034;

		// [41-50] node -> expression -> BinaryOperator
		static std::string M041;

		// [51-60] node -> expression -> Block

		// [61-70] node -> expression -> Boolean

		// [71-80] node -> expression -> CodeGenContext

		// [81-90] node -> expression -> ComparasionOpe
		static std::string M081;
		static std::string M082;

		// [91-100] node -> expression -> Conditional
		static std::string M091;

		// [101-110] node -> expression -> Double

		// [111-120] node -> expression -> ExpressionStatement

		// [121-130] node -> expression -> ForLoop
		static std::string M121;
		static std::string M122;
		static std::string M123;

		// [131-140] node -> expression -> Function
		static std::string M131;
		static std::string M132;
		static std::string M133;

		// [141-150] node -> expression -> Identifier
		static std::string M141;

		// [151-160] node -> expression -> Integer

		// [161-170] node -> expression -> LogicOpe
		static std::string M161;
		static std::string M162;

		// [171-180] node -> expression -> MethodCall
		static std::string M171;
		static std::string M172;
		static std::string M173;
		static std::string M174;

		// [181-190] node -> expression -> nativefn

		// [191-200] node -> expression -> Return
		static std::string M191;

		// [201-210] node -> expression -> Scope

		// [211-220] node -> expression -> String

		// [221-230] node -> expression -> UnaryOpe
		static std::string M221;


	private:
		// Disallow creating an instance of this object
		Msg() {}
	};
}

#endif //MSG_HPP