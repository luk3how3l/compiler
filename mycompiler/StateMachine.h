#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_


//#pragma once
#include "Debug.h"
#include "Token.h"

//all states of DFA (nodes thenself)
enum MachineState {
	START_STATE, IDENTIFIER_STATE, INTEGER_STATE, CANTMOVE_STATE,
	ENDFILE_STATE, EQUAL_STATE,EOF_STATE, PLUS_STATE,
	// {					==				!
	LCURLYBRACE_STATE, EQUAL_EQUAL_STATE, NOT_STATE,
	LPARATHESIS_STATE, SEMICOLON_STATE, LESS_EQUAL_STATE,
	//ADD MINUS, TIMES FIVID LESS, LESS THAN. GREATER, T=GREATER THAN, EQUAL , NOT EQUAL
	MINUS_STATE, LESS_STATE, GREATER_STATE, GREATER_EQUAL_STATE,
	NOT_EQUAL_STATE, TIMES_STATE, DIVIDE_STATE,
	INSERTION_STATE, RPARATHESIS_STATE, RCURLYBRACE_STATE,
	RSLASH_STATE, COMMENT_STATE, STAR_STATE, LCOMMENT_STATE,
	COMMENT_STAR_STATE, OR_ALMOST_STATE, AND_ALMOST_STATE,
	OR_STATE, AND_STATE, COMMENT_END_STATE,
	PLUSEQUAL_STATE, MINUSEQUAL_STATE,

	LAST_STATE
};

//all edges of an DFA
enum CharacterType {
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, BAD_CHAR,
	ENDFILE_CHAR, RCURLYBRACE_CHAR, LCURLYBRACE_CHAR, SEMICOLON_CHAR,
	//eof			}					{				;
	EQUAL_CHAR,										AHH_CHAR,
	//	=			<				>					!

	//ADD MINUS, TIMES FIVID LESS, LESS THAN. GREATER, T=GREATER THAN, EQUAL , NOT EQUAL
	MINUS_CHAR, LESS_CHAR, GREATER_CHAR, TIMES_CHAR, DIVIDE_CHAR,
	// -			<			>			*			/
	LPARATHESIS_CHAR, RPARATHESIS_CHAR, RSLASH_CHAR, STAR_CHAR,
	// (					)				/			*
	NEWLINE_CHAR, RET_CHAR, DASH_CHAR, AND_CHAR, OR_CHAR, COMMA_CHAR,
	// \n			\r ??		-			&		|		,


	LAST_CHAR
};

//declare the StateMachineClass
class StateMachineClass
{
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType&
		previousTokenType);

private:
	MachineState mCurrentState;

	// The matrix of legal moves:
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

	// Which end-machine-states correspond to which token types.
	// (non end states correspond to the BAD_TOKEN token type)
	TokenType mCorrespondingTokenTypes[LAST_STATE];
};


#endif