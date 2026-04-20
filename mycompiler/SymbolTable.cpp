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
