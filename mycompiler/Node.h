#pragma once
#include <vector>
#include "Symbol.h"
#include "Instructions.h"
#include <string.h>
#include <iostream>

class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;
class OrNode;
class AndNode; 
class insertionNode;



class Node
{
public:
	virtual ~Node() = default;  // virtual destructor
	virtual void Code(InstructionsClass &machineCode)=0;
	
};          //gonna use abstract base class like fruit. we eat apples not fruit

class StatementNode : public Node {
public:
	StatementNode();
	virtual ~StatementNode();
	virtual void Interpret() = 0;

}; //abstract

class StartNode : public Node
{
public:
	StartNode(ProgramNode* program);
	virtual ~StartNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);

private:
	ProgramNode* mProgramNode;
};

//3
class ProgramNode :public Node //-> VOID MAIN LPAREN RPAREN <Block>
{ 
public:
	ProgramNode(BlockNode* daBlock);
	virtual ~ProgramNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
	//constructor for blockNOde..
private:
	BlockNode* mDaBlock;
};

//4
class BlockNode :public StatementNode {
public:
	BlockNode(StatementGroupNode* SGNode);
	virtual ~BlockNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
	
private:
	StatementGroupNode* mSGNode;


}; //LCURLY <StatementGroup> RCURLY


class StatementGroupNode :public Node {
public:
	StatementGroupNode();
	virtual ~StatementGroupNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
	void AddStatement(StatementNode* ptrStatenode);
	
private:
	std::vector<StatementNode*> mListStatementNode;
}; //-> empty




class DeclarationStatementNode :public StatementNode {
public:
	DeclarationStatementNode(IdentifierNode* IdNode);
	virtual ~DeclarationStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	IdentifierNode* mIDNode;
};



class AssignmentStatementNode :public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode* IDnode, ExpressionNode* Expressnode);
	virtual ~AssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	IdentifierNode* mIDNODE;
	ExpressionNode* mEXPRESSNODE;
};

class CoutStatementNode :public StatementNode {
public:
	CoutStatementNode (ExpressionNode* ExpressNode);
	virtual ~CoutStatementNode();
	void Code(InstructionsClass &machinecode);
	void Interpret();

private:
	ExpressionNode* mEXPRESSNODE;
};



//different tpye of product
// not pull from node?? 
class ExpressionNode :public Node {
public:
	virtual ~ExpressionNode();
	virtual int Evaluate() = 0;
	virtual void Code(InstructionsClass &machineCode) override;

	virtual void CodeEvaluate(InstructionsClass &machineCode)= 0;

private:

}; //-> identifier or integer or expression + expression

class IntegerNode :public ExpressionNode {
public:
	IntegerNode(int number);
	virtual int Evaluate() override;
	void CodeEvaluate(InstructionsClass &machineCode);

private:
	int mNumber;
}; //-> int

class IdentifierNode :public ExpressionNode {
public:
	IdentifierNode(const std::string& label, SymbolTableClass* table);
	virtual ~IdentifierNode() = default;
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	virtual int Evaluate() override;
	void CodeEvaluate(InstructionsClass &machineCode);
private:
	SymbolTableClass* mTable;
	std::string mLabel;
}; //-> identifier

class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
	virtual ~BinaryOperatorNode();
	virtual void CodeEvaluate(InstructionsClass &machineCode) = 0;

protected:
	//2 Expresssionnodes
	ExpressionNode* mLeft;
	ExpressionNode* mRight;
};

 // Interpreter test
class WhileStatementNode : public StatementNode
{
public:
	WhileStatementNode(ExpressionNode* cond, StatementNode* stmt);
	virtual ~WhileStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);

private:
	ExpressionNode* mCondition;
	StatementNode* mStatement;
};

class IfStatementNode : public StatementNode
{
public:
	IfStatementNode(ExpressionNode* cond, StatementNode* stmt);
	virtual ~IfStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);

private:
	ExpressionNode* mCondition;
	StatementNode* mStatement;
};
class CoutNode : public StatementNode
{
public:
	CoutNode(ExpressionNode* expr);
	virtual void Interpret() override;
	//void Code(InstructionsClass &machinecode);

private:
	ExpressionNode* mExpr;
	//list of expression nodes
	std::vector<ExpressionNode*> mListExpressionNode;
	//try to print an integer and then a space
};


class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};


class PlusEqualNode : public BinaryOperatorNode {
public:
	PlusEqualNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;

};

class MinusNode : public BinaryOperatorNode
{
public:
	MinusNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

class MinusEqualNode : public BinaryOperatorNode {
public:
	MinusEqualNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;

};


class TimesNode : public BinaryOperatorNode
{
public:
	TimesNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};


class DivideNode : public BinaryOperatorNode
{
public:
	DivideNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

class LessNode : public BinaryOperatorNode
{
public:
	LessNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

class LessEqualNode : public BinaryOperatorNode
{
public:
	LessEqualNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

class GreaterNode : public BinaryOperatorNode
{
public:
	GreaterNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

class GreaterEqualNode : public BinaryOperatorNode
{
public:
	GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

class EqualNode : public BinaryOperatorNode
{
public:
	EqualNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

class NotEqualNode : public BinaryOperatorNode
{
public:
	NotEqualNode(ExpressionNode* left, ExpressionNode* right);
	virtual int Evaluate() override;
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
};

/*
class InsertionNode : public BinaryOperatorNode
{
public:
	InsertionNode(ExpressionNode* left, ExpressionNode* right);
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
	virtual int Evaluate() override;
};
*/

class OrNode : public BinaryOperatorNode
{
public:
	OrNode(ExpressionNode* left, ExpressionNode* right);
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
	virtual int Evaluate() override;
};

class AndNode : public BinaryOperatorNode
{
public:
	AndNode(ExpressionNode* left, ExpressionNode* right);
	virtual void CodeEvaluate(InstructionsClass &machineCode) override;
	virtual int Evaluate() override;
};

//void CodeAndExecute(std::string inputFile);
//class EndNode : public Node; 

int treetest();
int testtree2();
int testtree3();

