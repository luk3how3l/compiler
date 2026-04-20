#include "Parser.h"

ParserClass::~ParserClass() {}

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* Tabla) {
	//ScannerClass thing;
	mScanner = scanner;
	mSymTable = Tabla;
}

// Verify that the next token in the input file is of the same type
// that the parser expects.
TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = mScanner->GetNextToken();
	if (currentToken.GetTokenType() != expectedType)
	{
		std::cerr << "Error in ParserClass::Match. " << std::endl;
		std::cerr << "Expected token type " <<
			TokenClass::GetTokenTypeName(expectedType) <<
			", but got type " << currentToken.GetTokenTypeName() << std::endl;
		//exit(1);
		throw std::runtime_error("Parser error");
	}
	MSG("\tSuccessfully matched Token Type: " <<
		currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
		currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}

ExpressionNode* ParserClass::Relational()
{
	ExpressionNode* current = PlusMinus();

	// Handle the optional tail:
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN)
	{
		Match(tt);
		current = new LessNode(current,PlusMinus());
	}
	else if (tt == LESSEQUAL_TOKEN)
	{
		Match(tt);
		current = new LessEqualNode(current, PlusMinus());

	}
	else if (tt == GREATER_TOKEN)
	{
		Match(tt);
		current = new GreaterNode(current, PlusMinus());

	}
	else if (tt == GREATEREQUAL_TOKEN)
	{
		Match(tt);
		current = new GreaterEqualNode(current, PlusMinus());
	}
	else if (tt == EQUAL_TOKEN)
	{
		Match(tt);
		current = new EqualNode(current, PlusMinus());
	}
	else if (tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
		current = new NotEqualNode(current, PlusMinus());
	}
	// Now handle logical ANDs (higher than OR)
	while (mScanner->PeekNextToken().GetTokenType() == AND_TOKEN)
	{
		Match(AND_TOKEN);
		ExpressionNode* right = Relational();
		current = new AndNode(current, right);
	}

	// Finally handle logical ORs (lowest precedence)
	while (mScanner->PeekNextToken().GetTokenType() == OR_TOKEN)
	{
		Match(OR_TOKEN);
		ExpressionNode* right = Relational();
		current = new OrNode(current, right);
	}

	return current;
}

ExpressionNode* ParserClass::PlusMinus()
{
	ExpressionNode* current = TimesDivide();

	while (true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == PLUS_TOKEN)
		{
			Match(tt);
			current = new PlusNode(current, TimesDivide());
		}
		else if (tt == MINUS_TOKEN)
		{
			Match(tt);
			current = new MinusNode(current, TimesDivide());
		}
		else
		{
			return current;
		}
	}
}
ExpressionNode* ParserClass::TimesDivide() {
	ExpressionNode* current = Factor();
	while (true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == TIMES_TOKEN)
		{
			Match(tt);
			current = new TimesNode(current, Factor());
		}
		else if (tt == DIVIDE_TOKEN)
		{
			Match(tt);
			current = new DivideNode(current, Factor());

		}
		else
		{
			return current;
		}
	}
 }

ExpressionNode* ParserClass::Factor()
{
	TokenType tt = mScanner->PeekNextToken().GetTokenType();

	if (tt == IDENTIFIER_TOKEN)
	{
		TokenClass t = Match(IDENTIFIER_TOKEN);
		return new IdentifierNode(t.GetLexeme(), mSymTable);
	}

	else if (tt == INTEGER_TOKEN)
	{
		TokenClass t = Match(INTEGER_TOKEN);
		int v = atoi(t.GetLexeme().c_str());
		return new IntegerNode(v);
	}

	else if (tt == LPAREN_TOKEN)
	{
		Match(LPAREN_TOKEN);
		ExpressionNode* expr = Relational();
		Match(RPAREN_TOKEN);
		return expr;
	}

	std::cerr << "Parser error in Factor\n";
	//exit(1);
	throw std::runtime_error("Parser error");
}

//there are 3 layers 
// relationals  (lowest :(  )
// +-     (after)
// times / divides (highest proirity)
// 
//you got banch of branch to check.
// check if plus then if plus or equal or what it is. 

StartNode* ParserClass::Start()
{
	ProgramNode* pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode* sn = new StartNode(pn);
	return sn;
}


ProgramNode* ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode* blon = Block();
	//helo ret
	ProgramNode* pron = new ProgramNode(blon);
	return pron;
}

BlockNode* ParserClass::Block() {
	Match(LCURLY_TOKEN);
	StatementGroupNode* Gay = StatementGroup();
	Match(RCURLY_TOKEN);

	BlockNode* blon = new BlockNode(Gay);
	return blon;

}
StatementGroupNode* ParserClass::StatementGroup() {
	
	StatementGroupNode* group = new StatementGroupNode();
	
	//check if there something
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	
	while (tt == INT_TOKEN ||
		tt == IDENTIFIER_TOKEN ||
		tt == COUT_TOKEN ||
		tt == LCURLY_TOKEN||
		tt == IF_TOKEN ||
		tt == WHILE_TOKEN
		)
	{
		StatementNode* s = Statement();
		group->AddStatement(s);
		tt = mScanner->PeekNextToken().GetTokenType();
	}
	
	return group;
}


StatementNode* ParserClass::Statement() {
	TokenType tt = mScanner->PeekNextToken().GetTokenType();

	if (tt == INT_TOKEN)
	{
		return DeclarationStatement();
	}
	else if (tt == IDENTIFIER_TOKEN)
	{
		return AssignmentStatement();
	}
	if (tt == IF_TOKEN)
	{
		return IfStatement();
	}
	else if (tt == WHILE_TOKEN)
	{
		return WhileStatement();
	}
	else if (tt == COUT_TOKEN)
	{
		return CoutStatement();
	}
	else if (tt == LCURLY_TOKEN)
	{
		return Block();
	}
	else
	{
		std::cerr << "Parser error: unexpected token "
			<< mScanner->PeekNextToken().GetTokenTypeName()
			<< std::endl;
		//return death
		//exit(1); //do want to have an hard exit.
		throw std::runtime_error("Parser error");
		//return nullptr;
	}

}

DeclarationStatementNode* ParserClass::DeclarationStatement()
{
	Match(INT_TOKEN);
	TokenClass id = Match(IDENTIFIER_TOKEN);
	Match(SEMICOLON_TOKEN);

	mSymTable->AddEntry(id.GetLexeme());

	IdentifierNode* idNode =
		new IdentifierNode(id.GetLexeme(), mSymTable);

	return new DeclarationStatementNode(idNode);
}

AssignmentStatementNode* ParserClass::AssignmentStatement(){
	TokenClass id = Match(IDENTIFIER_TOKEN);

	Match(ASSIGNMENT_TOKEN);
	ExpressionNode* expr = Relational();
	Match(SEMICOLON_TOKEN);


	IdentifierNode* idNode =
		new IdentifierNode(id.GetLexeme(), mSymTable);

	return new AssignmentStatementNode(idNode, expr);
}

CoutStatementNode* ParserClass::CoutStatement()
{
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	ExpressionNode* expr = Relational();

	Match(SEMICOLON_TOKEN);

	return new CoutStatementNode(expr);
}

IfStatementNode* ParserClass::IfStatement()
{
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);

	//expresssion
	ExpressionNode* condition = Relational();

	Match(RPAREN_TOKEN);

	StatementNode* stmt = Statement();

	return new IfStatementNode(condition, stmt);
}

WhileStatementNode* ParserClass::WhileStatement()
{
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);

	ExpressionNode* condition = Relational();

	Match(RPAREN_TOKEN);

	StatementNode* stmt = Statement();

	return new WhileStatementNode(condition, stmt);
}






