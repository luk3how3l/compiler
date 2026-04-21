
#ifndef _TOKEN_H_
#define _TOKEN_H_

#pragma once

#include <iostream>
#include <string>
//#define int mum = 55; 



enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN,
	MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN, LESS_TOKEN, LESSEQUAL_TOKEN,
	GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,
	NOT_TOKEN,          // unary NOT
	OR_TOKEN, AND_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
	RCURLY_TOKEN, IF_TOKEN, WHILE_TOKEN,
	//NEw test
	REPEAT_TOKEN, PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN, ENDLINE_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, COMMENT_TOKEN,
	BAD_TOKEN, ENDFILE_TOKEN,
};


/* will be adding more token types later, such as:
 MODULUS, PLUS+EQUAL,
*/


// IMPORTANT: The list above and the list below MUST be kept in sync.
const std::string gTokenTypeNames[] = {
	// Reserved Words
	"VOID", "MAIN", "INT", "COUT",
	// Other Operators
	"INSERTION", "ASSIGNMENT", "PLUS",
	"MINUS", "TIMES", "DIVIDE", "LESS", "LESSEQUAL",
	"GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL",
	"NOT",          // unary NOT
	"OR", "AND",
	// Other Characters
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"IF", "WHILE",
	//test tokens
	"REPEAT", "PLUSEQUAL", "MINUSEQUAL", "ENDLINE",
	// Other Token Types
	"IDENTIFIER", "INTEGER", "COMMENT",
	"BAD", "ENDFILE",
};



class TokenClass{
private:
	TokenType mType;
	std::string mLexeme;
public:
	TokenClass(TokenType type, const std::string& lexeme);
	TokenType GetTokenType() const { return mType; }
	const std::string& GetTokenTypeName() const
	{
		return gTokenTypeNames[mType];
	}
	std::string GetLexeme() const { return mLexeme; }
	static const std::string& GetTokenTypeName(TokenType type)
	{
		return gTokenTypeNames[type];
	}
};

std::ostream& operator<<(std::ostream& out, const TokenClass& tc);



#endif 