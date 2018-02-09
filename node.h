#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <stack>

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

namespace april
{
    class CodeGenContext;
    
    using StatementList = std::vector<class Statement*>;
    using ExpressionList = std::vector<class Expression*>;
    using VariableList = std::vector<class VariableDeclaration*>;    

    class Node
    {
        public:
            virtual ~Node() {}
            virtual llvm::Value* codeGen(CodeGenContext& context) { return NULL; }

    };

    class Expression: public Node 
    {
    };

    class Statement: public Node
    {
    };

    class Integer: public Expression
    {
        public:
            long long value;
            Integer(long long value):value(value) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };    

    class Double: public Expression
    {
        public:
            double value;
            Double(double value): value(value) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };

    class Identifier: public Expression
    {
        public:
            std::string name;
            Identifier(const std::string& name): name(name) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };

    class String: public Expression
    {
        public:
            std::string value;
            String(std::string value): value(value)  {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };

    class BinaryOperator: public Expression
    {
        private:
            int op;
            Expression& lhs;
            Expression& rhs;
            
        public:
            BinaryOperator(Expression& lhs, int op, Expression& rhs): lhs(lhs), rhs(rhs), op(op) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };

    class Assignment: public Expression
    {
        public:
            Identifier& lhs;
            Expression& rhs;
            Assignment(Identifier& lhs, Expression& rhs):lhs(lhs), rhs(rhs) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };

    class Block: public Expression
    {
        public:
            StatementList statements;
            Block() {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };

    class VariableDeclaration: public Statement
    {
        private:
            const Identifier& type;
            Identifier& id;
            Expression* assignmentExpr;
        
        public:
            VariableDeclaration(const Identifier& type, Identifier& id): type(type), id(id) { assignmentExpr = nullptr; } 
            VariableDeclaration(const Identifier& type, Identifier& id, Expression* assignmentExpr): type(type), id(id), assignmentExpr(assignmentExpr) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };

    class ExpressionStatement: public Statement
    {
        private:
            Expression& expression;
        
        public:
            ExpressionStatement(Expression& expression): expression(expression) {}
            llvm::Value* codeGen(CodeGenContext& context);
    };

    class MethodCall: public Expression
    {
        private:
            const Identifier& id;
            ExpressionList arguments;
        
        public:
            MethodCall(const Identifier& id, ExpressionList& arguments): id(id), arguments(arguments) {}
            MethodCall(const Identifier& id): id(id) {}
            virtual llvm::Value* codeGen(CodeGenContext& context);
    };
}


#endif //NODE_H