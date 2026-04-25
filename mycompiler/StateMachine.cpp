#include "StateMachine.h"

// Constructor
StateMachineClass::StateMachineClass()
{
    // Start in the start state
    mCurrentState = START_STATE;

    // Initialize all moves to CANTMOVE_STATE
    for (int i = 0; i < LAST_STATE; i++)
    {
        for (int j = 0; j < LAST_CHAR; j++)
        {
            mLegalMoves[i][j] = CANTMOVE_STATE;
        }
    }

    // Legitimate DFA transitions

    //identifier
    mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;

    mLegalMoves[IDENTIFIER_STATE][WHITESPACE_CHAR] = CANTMOVE_STATE;
    mLegalMoves[IDENTIFIER_STATE][NEWLINE_CHAR] = CANTMOVE_STATE;

    //integer
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
    //white space
    mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;
    //;
    mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
   
    //<
    mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
    mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
    mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESS_EQUAL_STATE;

    //equal state = =
    mLegalMoves[START_STATE][EQUAL_CHAR] = EQUAL_STATE;
    mLegalMoves[EQUAL_STATE][EQUAL_CHAR] = EQUAL_EQUAL_STATE;
    //not equal state ! =

    mLegalMoves[START_STATE][AHH_CHAR] = NOT_STATE;
    mLegalMoves[NOT_STATE][EQUAL_CHAR] = NOT_EQUAL_STATE;
     
    // show not an !x == 12 or somethign
    //mLegalMoves[NOT_STATE][LETTER_CHAR] = NOT_EQUAL_STATE;
    //times
    mLegalMoves[START_STATE][STAR_CHAR] = TIMES_STATE;
    
    //minus -
    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
    mLegalMoves[MINUS_STATE][EQUAL_CHAR] = MINUSEQUAL_STATE;

    // >
    mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
    mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATER_EQUAL_STATE;
    // +
    mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PLUSEQUAL_STATE;

   // extra {} () endfile 
    mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
    mLegalMoves[START_STATE][LCURLYBRACE_CHAR] = LCURLYBRACE_STATE;
    mLegalMoves[START_STATE][RCURLYBRACE_CHAR] = RCURLYBRACE_STATE;
    mLegalMoves[START_STATE][LPARATHESIS_CHAR] = LPARATHESIS_STATE;
    mLegalMoves[START_STATE][RPARATHESIS_CHAR] = RPARATHESIS_STATE;


    /*
    RSLASH -- * --> COMMENT
    COMMENT -- ANY --> COMMENT
    COMMENT -- * --> COMMENT_STAR
    COMMENT_STAR -- / --> COMMENT_END
    COMMENT_STAR -- * --> COMMENT_STAR
    COMMENT_STAR -- other --> COMMENT
    */
    // Enters Comment state if /* and only jumps out if 
    // enter block comment
    mLegalMoves[RSLASH_STATE][STAR_CHAR] = COMMENT_STATE;

    // COMMENT absorbs EVERYTHING by default
    for (int c = 0; c < LAST_CHAR; c++)
    {
        mLegalMoves[COMMENT_STATE][c] = COMMENT_STATE;
    }

    // but '*' may end comment
    mLegalMoves[COMMENT_STATE][STAR_CHAR] = COMMENT_STAR_STATE;

    // COMMENT_STAR logic
    for (int c = 0; c < LAST_CHAR; c++)
    {
        mLegalMoves[COMMENT_STAR_STATE][c] = COMMENT_STATE;
    }

    // stay in STAR if multiple *
    mLegalMoves[COMMENT_STAR_STATE][STAR_CHAR] = COMMENT_STAR_STATE;

    // exit on */
    mLegalMoves[COMMENT_STAR_STATE][RSLASH_CHAR] = COMMENT_END_STATE;

    /*
    START -- / --> RSLASH
RSLASH -- / --> LCOMMENT
LCOMMENT -- ANYTHING --> LCOMMENT
LCOMMENT -- \n --> START
    */
    // slash entry
    mLegalMoves[START_STATE][RSLASH_CHAR] = RSLASH_STATE;

    // detect //
    mLegalMoves[RSLASH_STATE][RSLASH_CHAR] = LCOMMENT_STATE;

    // absorb EVERYTHING in COMMENT
    for (int c = 0; c < LAST_CHAR; c++)
    {
        mLegalMoves[LCOMMENT_STATE][c] = LCOMMENT_STATE;
    }

    // exit on newline or EOF
    mLegalMoves[LCOMMENT_STATE][NEWLINE_CHAR] = START_STATE;
    mLegalMoves[LCOMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
    
    //||
    mLegalMoves[START_STATE][OR_CHAR] = OR_ALMOST_STATE;
    mLegalMoves[OR_ALMOST_STATE][OR_CHAR] = OR_STATE;
    //&&
    mLegalMoves[START_STATE][AND_CHAR] = AND_ALMOST_STATE;
    mLegalMoves[AND_ALMOST_STATE][AND_CHAR] = AND_STATE;

        //add more DFA transition

    // Initialize all states to BAD_TOKEN
    for (int i = 0; i < LAST_STATE; i++)
    {
        mCorrespondingTokenTypes[i] = BAD_TOKEN;
    }
    
    // End states that produce real tokens
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[LPARATHESIS_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RPARATHESIS_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[LCURLYBRACE_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLYBRACE_STATE] = RCURLY_TOKEN;

    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;

    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[RSLASH_STATE] = DIVIDE_TOKEN;

    mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[NOT_STATE] = NOT_TOKEN;

    mCorrespondingTokenTypes[LESS_EQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[GREATER_EQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[EQUAL_EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[NOT_EQUAL_STATE] = NOTEQUAL_TOKEN;

    mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
    mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
    mCorrespondingTokenTypes[PLUSEQUAL_STATE] = PLUSEQUAL_TOKEN;
    mCorrespondingTokenTypes[MINUSEQUAL_STATE] = MINUSEQUAL_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter,
    TokenType& previousTokenType)
{   // convert the input character into an input character type
    CharacterType charType = BAD_CHAR;

    if (isalpha(currentCharacter))
        charType = LETTER_CHAR;
    else if (isdigit(currentCharacter))
        charType = DIGIT_CHAR;
    else if (currentCharacter == '\n')
        charType = NEWLINE_CHAR;
    //else if (currentCharacter == '\r')
        //harType = Recarge_CHAR;
    else if (isspace(currentCharacter))
        charType = WHITESPACE_CHAR;
    else if (currentCharacter == '+')
        charType = PLUS_CHAR;
    else if (currentCharacter == EOF)
        charType = ENDFILE_CHAR;
    else if (currentCharacter == '{')
        charType = LCURLYBRACE_CHAR;
    else if (currentCharacter == '}')
        charType = RCURLYBRACE_CHAR;
    else if (currentCharacter == '(')
        charType = LPARATHESIS_CHAR;
    else if (currentCharacter == ')')
        charType = RPARATHESIS_CHAR;
    else if (currentCharacter == '=')
        charType = EQUAL_CHAR;
    else if (currentCharacter == ';')
        charType = SEMICOLON_CHAR;
    else if (currentCharacter == '<')
        charType = LESS_CHAR;
    else if (currentCharacter == '>')
        charType = GREATER_CHAR;
    else if (currentCharacter == '/')
        charType = RSLASH_CHAR; //divide token
    else if (currentCharacter == '*')
        charType = STAR_CHAR;
    else if (currentCharacter == '-')
        charType = MINUS_CHAR;
    else if (currentCharacter == '!') 
        charType = AHH_CHAR;
    else if (currentCharacter == '&')
        charType = AND_CHAR;
    else if (currentCharacter == '|')
        charType = OR_CHAR;
    else if (currentCharacter == ',')
        charType = COMMA_CHAR;


        previousTokenType = mCorrespondingTokenTypes[mCurrentState];
        mCurrentState = mLegalMoves[mCurrentState][charType];
        //MSG("UpdateState-> Current State: " << mCurrentState);
        return mCurrentState;
    }