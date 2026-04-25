#include <iostream>
#include "Symbol.h"

int unittest()
{
    std::cout << "----- Symbol Table Unit Test -----\n";

    SymbolTableClass table;

    //AddEntry
    table.AddEntry("x");
    table.AddEntry("y");

    std::cout << "Count after adding x and y: "
        << table.GetCount() << std::endl;

    //Exists
    std::cout << "Exists(x): " << table.Exists("x") << std::endl;
    std::cout << "Exists(z): " << table.Exists("z") << std::endl;

    //GetValue
    std::cout << "preSetValue: Value of x: " << table.GetValue("x") << std::endl;
    std::cout << "preSetValue: Value of y: " << table.GetValue("y") << std::endl;


    //SetValue
    table.SetValue("x", 10);
    table.SetValue("y", 20);
    std::cout << "Value are set! "<< std::endl;

    //GetValue
    std::cout << "Value of x: " << table.GetValue("x") << std::endl;
    std::cout << "Value of y: " << table.GetValue("y") << std::endl;

    // Test GetIndex
    std::cout << "Index of x: " << table.GetIndex("x") << std::endl;
    std::cout << "Index of y: " << table.GetIndex("y") << std::endl;
    std::cout << "Index of z (should be -1): "
        << table.GetIndex("z") << std::endl;

    std::cout << "----- Normal Tests Passed -----\n";

    // ===============================
    // ERROR HANDLING TESTS
    // Uncomment ONE at a time
    // ===============================

    // Duplicate variable test
    table.AddEntry("x");

    // GetValue on nonexistent variable
    table.GetValue("z");

    // SetValue on nonexistent variable
    table.SetValue("z", 100);

    return 0;
}

// old main tests 

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


    //new tests 

    
    /*

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
    */

