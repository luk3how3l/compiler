#include "Token.h"
#include <iostream>
#include <cstdlib> 
#include "Debug.h"


static void CheckTokenTypeNames()
{
    //safety of pulling from the cout
    const int enumCount = ENDFILE_TOKEN + 1;
    const int nameCount = sizeof(gTokenTypeNames) / sizeof(gTokenTypeNames[0]);

    if (enumCount != nameCount)
    {
        MSG("Current enum count: " << enumCount << " and Current name count: "<< nameCount);
        std::cerr << "TOKEN ERROR: TokenType enum and gTokenTypeNames are out of sync!"
            << std::endl;
        exit(1);
    }
}


// Constructor
TokenClass::TokenClass(TokenType type, const std::string& lexeme)
    : mType(type), mLexeme(lexeme)
{
    CheckTokenTypeNames();

    // Only identifiers can be
    // checked for reserved words:
    //MSG("Current Token: " << mType);

    if (mType == IDENTIFIER_TOKEN)
    {
        if (mLexeme == "void")
            mType = VOID_TOKEN;
        else if (mLexeme == "main")
            mType = MAIN_TOKEN;
        else if (mLexeme == "int")
            mType = INT_TOKEN;
        else if (mLexeme == "if")
            mType = IF_TOKEN;
        else if (mLexeme == "while")
            mType = WHILE_TOKEN;
        else if (mLexeme == "cout")
            mType = COUT_TOKEN;
        //add below to prep for test
        else if (mLexeme == "or")
            mType = OR_TOKEN;
        else if (mLexeme == "and")
            mType = AND_TOKEN;

        //else if (mLexeme == "!=")  //not need lol should put in DFA logic 
            //mType = NOTEQUAL_TOKEN;
    }
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& out, const TokenClass& tc)
{
    out << tc.GetTokenTypeName() << " \"" << tc.GetLexeme() << "\"";
    return out;
}
