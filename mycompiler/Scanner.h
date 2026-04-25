#pragma once

#include <fstream>
#include <string>
#include "Token.h"

class ScannerClass
{
public:
    ScannerClass(const std::string& inputFileName);
    ~ScannerClass();
    //get line number using the 
    int get_line_number() const;
    TokenClass GetNextToken();
    TokenClass PeekNextToken();


private:
    std::ifstream mFin;
    int mCurr_line_number;
};
//only need endif if use ifndef
