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
	/*	 
	std::cout << "Running PArser with Output with # of test is "<< tests.size() << std::endl;

	for (size_t i = 0; i < tests.size(); i++)
	{
		std::cout << "\n==== Running Test "<< (i+1) <<": " << tests[i].name << " ====\n";
		//show code
		std::cout << "----- Source Code -----\n";
		std::cout << tests[i].code << std::endl;
		std::cout << "-----------------------\n";

		// write test to temporary file
		std::ofstream file("temp_test.txt");
		file << tests[i].code;
		file.close();

		try
		{
			ScannerClass scanner("temp_test.txt");
			SymbolTableClass table;
			ParserClass parser(&scanner, &table);
			//parser.Start();
			StartNode* root = parser.Start();

			std::cout << "----- Program Output -----\n";
			root->Interpret();
			std::cout << "\n--------------------------\n";

			if (tests[i].shouldPass)
				std::cout << "PASS (program parsed)\n\n";
			else
				std::cout << "FAIL (should have errored)\n\n";
		}
		catch (...)
		{
			if (!tests[i].shouldPass)
				std::cout << "PASS (error correctly detected)\n\n\n\n\n\n\n\n\n";
			else
				std::cout << "FAIL (valid program rejected)\n\n\n\n\n\n\n";
		}
	}
	*/

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
     "void main() { int x; x = (5 + 5) * (5 + 5); if (x == 100) { x -= 50; cout << x; } }"}

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
            std::cout << "❌ FAIL (crashed)\n";
        }
    }

	return 0;
}
