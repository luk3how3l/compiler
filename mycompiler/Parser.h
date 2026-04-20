#pragma once
#include "Symbol.h"
#include "Token.h"
#include "Scanner.h"
#include "Node.h"

class ParserClass {
public:
	ParserClass(ScannerClass* scanner, SymbolTableClass* Tabla);
	virtual ~ParserClass();
	StartNode* Start();

private:
	//I need an interpret method 
	TokenClass Match(TokenType expectedType);
	
	ProgramNode* Program();
	BlockNode* Block();
	StatementGroupNode* StatementGroup();
	StatementNode* Statement();
	DeclarationStatementNode* DeclarationStatement();
	AssignmentStatementNode* AssignmentStatement();
	CoutStatementNode* CoutStatement();

	ExpressionNode* Relational();
	ExpressionNode* TimesDivide(); 
	ExpressionNode* PlusMinus();
	ExpressionNode* Factor();
	IfStatementNode* IfStatement();
	WhileStatementNode* WhileStatement();

	ScannerClass* mScanner;
	SymbolTableClass* mSymTable;
};

struct ParserTest
{
    std::string name;
    std::string code;
    bool shouldPass;
};

extern std::vector<ParserTest> tests;