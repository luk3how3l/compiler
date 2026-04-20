#include "Instructions.h"
#include <iostream>

//commands to run this in linux
//  g++ -std=c++17 -o mycompiler *.cpp

//g++ -std=c++17 -o mycompiler Instructions.cpp InstructionTester.cpp

// ./mycompiler

int mainOLD()
{
    InstructionsClass code;

    // ===== MEMORY TEST =====
    code.PushValue(500);
    code.PopAndStore(1);
    code.PushVariable(1);
    code.PopAndWrite();   // EXPECT: 500

    // ===== BASIC ARITHMETIC =====
    code.PushValue(10);
    code.PushValue(20);
    code.PopPopAddPush();
    code.PopAndWrite();   // EXPECT: 30

    code.PushValue(100);
    code.PushValue(8);
    code.PopPopSubPush();
    code.PopAndWrite();   // EXPECT: 92

    code.PushValue(7);
    code.PushValue(6);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 42

    code.PushValue(100);
    code.PushValue(8);
    code.PopPopDivPush();
    code.PopAndWrite();   // EXPECT: 12

    // ===== NEGATIVE + DIV EDGE =====
    code.PushValue(-50);
    code.PushValue(5);
    code.PopPopDivPush();
    code.PopAndWrite();   // EXPECT: -10

    // ===== CHAINED EXPRESSIONS =====
    // (10 + 5) * 3 = 45
    code.PushValue(10);
    code.PushValue(5);
    code.PopPopAddPush();
    code.PushValue(3);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 45

    // (50 - 20) / 5 = 6
    code.PushValue(50);
    code.PushValue(20);
    code.PopPopSubPush();
    code.PushValue(5);
    code.PopPopDivPush();
    code.PopAndWrite();   // EXPECT: 6

    // ===== RELATIONAL (<) =====
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopLessPush();
    code.PushValue(9);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 9

    code.PushValue(4);
    code.PushValue(4);
    code.PopPopLessPush();
    code.PopAndWrite();   // EXPECT: 0

    code.PushValue(5);
    code.PushValue(4);
    code.PopPopLessPush();
    code.PopAndWrite();   // EXPECT: 0

    // ===== RELATIONAL (==) =====
    code.PushValue(5);
    code.PushValue(5);
    code.PopPopEQPush();
    code.PushValue(10);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 10

    code.PushValue(5);
    code.PushValue(6);
    code.PopPopEQPush();
    code.PopAndWrite();   // EXPECT: 0

    // ===== RELATIONAL (!=) =====
    code.PushValue(5);
    code.PushValue(6);
    code.PopPopNEQPush();
    code.PushValue(11);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 11

    code.PushValue(7);
    code.PushValue(7);
    code.PopPopNEQPush();
    code.PopAndWrite();   // EXPECT: 0

    // ===== GREATER / LESS EQUAL =====
    code.PushValue(6);
    code.PushValue(5);
    code.PopPopGrePush();
    code.PushValue(12);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 12
    // >=
    code.PushValue(5);
    code.PushValue(5);
    code.PopPopGreEQPush();
    code.PushValue(13);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 13
    // <=
    code.PushValue(4);
    code.PushValue(5);
    code.PopPopLessEQPush();
    code.PushValue(14);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 14
    // <=
    code.PushValue(4);
    code.PushValue(4);
    code.PopPopLessEQPush();
    code.PushValue(15);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 1

    // ===== LOGICAL OPS =====
    // AND
    code.PushValue(1);
    code.PushValue(1);
    code.PopPopAndPush();
    code.PushValue(16);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 16

    code.PushValue(1);
    code.PushValue(0);
    code.PopPopAndPush();
    code.PopAndWrite();   // EXPECT: 0

    // OR
    code.PushValue(0);
    code.PushValue(1);
    code.PopPopOrPush();
    code.PushValue(17);
    code.PopPopMulPush();
    code.PopAndWrite();   // EXPECT: 17

    code.PushValue(0);
    code.PushValue(0);
    code.PopPopOrPush();
    code.PopAndWrite();   // EXPECT: 0

    // ===== MEMORY + ARITHMETIC =====
    // mData[2] = 10, mData[3] = 20 → print sum
    code.PushValue(10);
    code.PopAndStore(2);

    code.PushValue(20);
    code.PopAndStore(3);

    code.PushVariable(2);
    code.PushVariable(3);
    code.PopPopAddPush();
    code.PopAndWrite();   // EXPECT: 30

    // ===== COMPLEX EXPRESSION =====
    // (mData[2] * 3) + (mData[3] / 2)
    // = (10*3) + (20/2) = 30 + 10 = 30
    code.PushVariable(2);
    code.PushValue(3);
    code.PopPopMulPush();

    code.PushVariable(3);
    code.PushValue(2);
    code.PopPopDivPush();

    code.PopPopAddPush();
    code.PopAndWrite();   // EXPECT: 40

    code.Finish();
    code.Execute();
    return 0;
}
