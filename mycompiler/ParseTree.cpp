#include "Node.h"
#include <iostream>
#include "Symbol.h"
#include "Parser.h"

//TESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTEST
// 
// TESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTES

//        Parser Test

std::vector<ParserTest> tests =
{

    // ---------------- VALID PROGRAMS ----------------
    /*
    {
    "Valid Program",
    R"(void main()
{
    int x;
    int y;

    x = 5 + 3;
    y = x * 2;

    cout << y;
})",
true
},

{
"Multiple arithmetic precedence",
R"(void main()
{
    int x;
    x = 2 + 3 * 4 - 5;
    cout << x;
})",
true
},

{
"Parentheses precedence",
R"(void main()
{
    int x;
    x = (2 + 3) * 4;
    cout << x;
})",
true
},

{
"Relational operators",
R"(void main()
{
    int x;
    int y;

    x = 5;
    y = x < 10;

    cout << y;
})",
true
},

{
"Nested blocks",
R"(void main()
{
    int x;
    x = 5;

    {
        int y;
        y = x + 1;
        cout << y;
    }

    cout << x;
})",
true
},

{
"Multiple declarations",
R"(void main()
{
    int a;
    int b;
    int c;

    a = 1;
    b = 2;
    c = a + b;

    cout << c;
})",
true
},

{
"Complex expression",
R"(void main()
{
    int x;
    int y;

    x = (5 + 3) * (2 + 4) / 3;
    y = x >= 4;

    cout << y;
})",
true
},

// ---------------- INVALID PROGRAMS ----------------

{
"Missing semicolon in declaration",
R"(void main()
{
    int x
})",
false
},

{
"Missing closing brace",
R"(void main()
{
    int x;
)",
false
},

{
"Missing identifier in declaration",
R"(void main()
{
    int ;
})",
false
},

{
"Assignment missing expression",
R"(void main()
{
    int x;
    x = ;
})",
false
},

{
"Assignment missing semicolon",
R"(void main()
{
    int x;
    x = 5
})",
false
},

{
"Bad relational usage",
R"(void main()
{
    int x;
    x = 5 < ;
})",
false
},

{
"Missing assignment operator",
R"(void main()
{
    int x;
    x 5;
})",
false
},

{
"Broken cout statement",
R"(void main()
{
    cout y;
})",
false
},

{
"Missing cout expression",
R"(void main()
{
    cout << ;
})",
false
},

{
"Missing closing parenthesis",
R"(void main()
{
    int x;
    x = (5 + 3;
})",
false
},

{
"Invalid start of statement",
R"(void main()
{
    5 + 3;
})",
false
},


{
    "If true",
        R"(void main()
{
    int x;
    x = 5;

    if (x > 3)
        cout << x;
})",
true
//"5\n"
},
    */
{
    "If false",
    R"(void main()
{
    int x;
    x = 2;

    if (x > 3)
        cout << x;
})",
    true
},

{
    "While once",
    R"(void main()
{
    int x;
    x = 0;

    while (x < 3)
    {
        x = x + 1;
        cout << x;
    }
})",
    true
    // 0/n1/n2
    },
    {
        "Nested if in while",
        R"(void main()
{
    int x;
    x = 0;

    while (x < 3)
    {
        if (x == 1)
            cout << x;

        x = x + 1;
    }
})",
    true
    //"1\n"
    },

    
    // ---------------- Logical AND / OR Tests ----------------

{
    "If with AND true",
        R"(void main()
{
    int x;
    x = 5;

    if (x > 3 && x < 10)
        cout << x;
})",
true
// Expected output: "5\n"
},

{
    "If with AND false",
    R"(void main()
{
    int x;
    x = 2;

    if (x > 3 && x < 10)
        cout << x;
})",
    true
    // Expected output: none
},

{
    "If with OR true",
    R"(void main()
{
    int x;
    x = 2;

    if (x > 3 || x == 2)
        cout << x;
})",
    true
    // Expected output: "2\n"
},

{
    "If with OR false",
    R"(void main()
{
    int x;
    x = 1;

    if (x > 3 || x == 2)
        cout << x;
})",
    true
    // Expected output: none
},

{
    "AND vs OR precedence",
    R"(void main()
{
    int x; 
    int y;
    x = 5;
    y = 2;

    if (x > 3 || x == 5 && y == 2)
        cout << x;
})",
    true
    // Expected output: "5\n"
    // Tests that AND binds tighter than OR
},


//I forgot to handle comments, it's broken ...
{
    "Combined logical and relational",
    R"(void main()
{
    
    int x;
    int y;
    x = 4;
    y = 6;

    if ((x < 5 && y > 5) || x == 0)
        cout << y;
})",
    true,
    // Expected output: "6\n"
    }
};