#include "Token.h"
#include "StateMachine.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"
#include <iostream>


void CodeAndExecute(std::string inputFile)
{
// Create scanner, symbol table, and parser objects.
ScannerClass scanner(inputFile);
SymbolTableClass symbolTable;
ParserClass parser(&scanner, &symbolTable);
// Do the parsing, which results in a parse tree.
StartNode * root = parser.Start();
// Create the machine code instructions from the parse tree
InstructionsClass machineCode;
root->Code(machineCode);
machineCode.Finish();

//took this out for now
//machineCode.PrintAllMachineCodes();
// Execute the machine code instructions previously created
machineCode.Execute();
// cleanup recursively
delete root;
}


int main()
{

struct Test {
        std::string name;
        std::string code;
    };

    std::vector<Test> tests = {
    {"Print constant",
     "void main() { cout << 1000; }"},

    {"Empty Program",
     "void main() { }"},

    {"Declaration only",
     "void main() { int x; }"},

    {"Simple assignment",
     "void main() { int x; x = 5; cout << x; }"},

    {"Addition",
     "void main() { int x; x = 10 + 20; cout << x; }"},

    {"Subtraction",
     "void main() { int x; x = 50 - 15; cout << x; }"},

    {"Multiplication",
     "void main() { int x; x = 6 * 7; cout << x; }"},

    {"Division",
     "void main() { int x; x = 100 / 4; cout << x; }"},

    {"Chained expression",
     "void main() { int x; x = (10 + 5) * 2; cout << x; }"},

    {"Less than (true)",
     "void main() { int x; x = 3 < 5; cout << x; }"},

    {"Greater than (false)",
     "void main() { int x; x = 2 > 10; cout << x; }"},

    {"Logical AND",
     "void main() { int x; x = (1 < 2) && (3 < 4); cout << x; }"},

    {"Logical OR",
     "void main() { int x; x = (1 > 2) || (3 < 4); cout << x; }"},

    {"If statement (true branch)",
     "void main() { int x; x = 5; if (x > 3) { cout << x; } }"},

    {"If statement (false branch)",
     "void main() { int x; x = 2; if (x > 3) { cout << x; } }"},

    {"While loop (count up)",
     "void main() { int x; x = 0; while (x < 5) { cout << x; x = x + 1; } }"},

    {"While loop (never executes)",
     "void main() { int x; x = 10; while (x < 5) { cout << x; } }"},

    {"Nested expression + logic",
     "void main() { int x; x = (5 + 5) * (2 + 3); if (x == 50) { cout << x; } }"},

    {"Multiple variables",
     "void main() { int a; int b; a = 10; b = 20; cout << a; cout << b; }"},

    {"Variable reuse",
	"void main() { int a; int b; a = 10; b = 20; cout << a; cout << b; }"},
    
	{"Enchancements problem 1",
    "void main() { int x; x = 8; cout << 10 << x+2 << endl << endl << x*3+1 << endl ; }"},

	{"Enchancements problem 2 +=",
    "void main() { int x; x = (5 + 5) * (5 + 5); if (x == 100) { x += 20; cout << x; } }"},

	{"Enchancements problem 2 -=",
    "void main() { int x; x = (5 + 5) * (5 + 5); if (x == 100) { x -= 50; cout << x; } }"},
    
    {"Scope 1: simple shadow",
    "void main() { int x; x = 5; { int x; x = 10; cout << x << endl; } cout << x << endl; }"},

    {"Scope 2: inner does not affect outer",
    "void main() { int x; x = 3; { int x; x = 7; } cout << x << endl; }"},

    {"Scope 3: reuse outer after block",
    "void main() { int x; x = 2; { int y; y = 9; } cout << x << endl; }"},

    {"Scope 4: multiple nested scopes",
    "void main() { int x; x = 1; { int x; x = 2; { int x; x = 3; cout << x << endl; } cout << x << endl; } cout << x << endl; }"},
	
    
    {"Scope 16: use after scope (should fail)",
    "void main() { { int x; x = 5; } cout << x << endl; }"},
    
    {"Scope 17: inner variable lost",
    "void main() { int y; { int x; x = 5; y = x; } cout << y << endl; }"},
    
    {"Scope 21: triple nesting",
    "void main() { int x; x = 1; { int x; x = 2; { int x; x = 3; { int x; x = 4; cout << x << endl; } } } }"},

    {"Scope 22: outer reuse after deep",
    "void main() { int x; x = 9; { int x; x = 1; { int x; x = 2; } } cout << x << endl; }"},
    
    {"Scope 27: redeclare same scope (should fail)",
    "void main() { int x; int x; }"},

    {"Scope 28: nested redeclare ok",
    "void main() { int x; { int x; } }"},

    {"Scope 29: many nested",
    "void main() { int x; x = 0; { int x; x = 1; { int x; x = 2; { int x; x = 3; cout << x << endl; } } } }"},

    {"Scope 30: alternating shadow",
    "void main() { int x; x = 1; { int x; x = 2; } { int x; x = 3; cout << x << endl; } }"},

    {"Scope 33: deep reuse",
    "void main() { int x; x = 5; { int y; y = x; { int x; x = y + 2; cout << x << endl; } } }"},

    {"Scope 34: chained dependencies",
    "void main() { int x; x = 2; { int y; y = x + 3; { int z; z = y + x; cout << z << endl; } } }"},
        
};

    for (size_t i = 0; i < tests.size(); i++)
    {
        std::cout << "\n============================\n";
        std::cout << "Test " << (i + 1) << ": " << tests[i].name << "\n";
        std::cout << "============================\n";

        // Write code to file
        std::ofstream file("temp_test.txt");
        file << tests[i].code;
        file.close();

        std::cout << "----- Source Code -----\n";
        std::cout << tests[i].code << "\n";
        std::cout << "-----------------------\n";

        try
        {
            CodeAndExecute("temp_test.txt");
            std::cout << "✅ PASS\n";
        }
        catch (...)
        {
            std::cout << "❌ FAIL (very graceful exit)\n";
        }
    }

	return 0;
}
