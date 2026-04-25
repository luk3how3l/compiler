#include "Scanner.h"
#include "StateMachine.h"
#include <iostream>
#include <cstdlib>
#include "Debug.h"

// da constructor
ScannerClass::ScannerClass(const std::string& inputFileName)
{	
	MSG("Initializing ScannerClass object");
	mCurr_line_number = 1;
	//init that there was no first
	TokenType previousTokenType = BAD_TOKEN;
	//mHasPeeked = false;
	//mPeekedToken = BAD_TOKEN;

	mFin.open(inputFileName.c_str(), std::ios::binary);
	if (!mFin)
	{
		std::cerr << "Error opening input file " << inputFileName;
		std::exit(1);
	}
	else {
		//std::cout << "Successful opened da File!" << std::endl;
		MSG("Successful opened da File!" << inputFileName.c_str());
	}
}

// Destructor
ScannerClass::~ScannerClass()
{
	mFin.close();
}


TokenClass ScannerClass::GetNextToken()
{
	StateMachineClass stateMachine;
	std::string lexeme;
	MachineState currentState = START_STATE;
	TokenType previousTokenType = BAD_TOKEN;

	char c = mFin.get();

	// Skip whitespace BEFORE building token
	while (isspace(c))
	{
		if (c == '\n')
			mCurr_line_number++;

		c = mFin.get();
	}

	

	if (!mFin)
		return TokenClass(ENDFILE_TOKEN, "");

	do
	{
		lexeme += c;
		//MSG("Lexeme: >" << lexeme << "<");


		currentState = stateMachine.UpdateState(c, previousTokenType);
		
		if (currentState == COMMENT_STATE || currentState == LCOMMENT_STATE
			)
			// COMMENT_ENDSTATE    // keep consuming but don't build token
		{lexeme.clear();}

		if (currentState != CANTMOVE_STATE)
			c = mFin.get();

	} while (currentState != CANTMOVE_STATE);

	lexeme.pop_back();
	mFin.unget();   // put back char that broke token

	
	return TokenClass(previousTokenType, lexeme);
}

	

int ScannerClass::get_line_number() const {
	MSG("Line is on " << mCurr_line_number);
	return mCurr_line_number;
}


//assginemnt 6 PeekNextToken
TokenClass ScannerClass::PeekNextToken() {

	// 1. Save position
	std::streampos oldPosition = mFin.tellg();
	int oldLineNumber = mCurr_line_number;
	
	TokenClass tc = GetNextToken();
	if (!mFin) // if we triggered EOF, then seekg doesn't work,
		mFin.clear();// unless we first clear()

	//4 resrtore fi;e	
	mFin.seekg(oldPosition);

	//restore line num
	mCurr_line_number = oldLineNumber;

	
	//MSG("Peek aahhead func peeks: token is >" << tc.GetLexeme() << "<");
		
	return tc;
}



