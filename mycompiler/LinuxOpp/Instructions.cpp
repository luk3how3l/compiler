#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
//#include <windows.h>
#include "Instructions.h"
// Some assembly like definitions for our machine code:
const unsigned char SYS_CALL1 = 0x0F;
const unsigned char SYS_CALL2 = 0x05;
const unsigned char CALL = 0xE8;
// function Call within segment. Add 4 byte offset
const unsigned char POP_EAX = 0x58;
const unsigned char EAX_TO_MEM = 0xA3;
// Add 4 (or 8) byte address value in reverse order
const unsigned char BIT64 = 0x48;
// BIT64 (0x48) makes IMMEDIATE_TO_EAX take 8 byte address,
// or IMMEDIATE_TO_RAX
const unsigned char IMMEDIATE_TO_EDX = 0xBA;
const unsigned char IMMEDIATE_TO_ESI = 0xBE;
const unsigned char IMMEDIATE_TO_EDI = 0xBF;
const unsigned char CMP_EAX1 = 0x83; // followed by 1 byte
const unsigned char CMP_EAX2 = 0xF8;
const unsigned char MEM_TO_EAX = 0xA1;
// Add 4 (or 8) byte address value in reverse order
const unsigned char JNE = 0x75;
const unsigned char JGE = 0x7D;
const unsigned char NEG_EAX1 = 0xF7;
const unsigned char NEG_EAX2 = 0xD8;
const unsigned char IMMEDIATE_TO_ECX = 0xB9;
const unsigned char IMMEDIATE_TO_EBX = 0xBB;
const unsigned char ADD_ECX1 = 0x83; // followed by 1 byte to add.
const unsigned char ADD_ECX2 = 0xC1;
const unsigned char SUB_ECX1 = 0x83; // followed by 1 byte to add.
const unsigned char SUB_ECX2 = 0xE9;
const unsigned char DIV_EAX_EBX1 = 0xF7;
const unsigned char DIV_EAX_EBX2 = 0xFB;
// Registers D and A divided by B. (clear D with CDQ first!)
// .. Quotient->A and Remainder->D.
const unsigned char CDQ = 0x99;
const unsigned char ADD_EDX1 = 0x83; // followed by 1 byte
const unsigned char ADD_EDX2 = 0xC2;
const unsigned char POP_ECX = 0x59;
const unsigned char POP_EDX = 0x5A;
const unsigned char PUSH_ECX = 0x51;
const unsigned char PUSH_EDX = 0x52;
const unsigned char CMP_ECX1 = 0x83; // followed by 1 byte
const unsigned char CMP_ECX2 = 0xF9;

const unsigned char PUSH_EBP = 0x55;
const unsigned char MOV_EBP_ESP1 = 0x8B;
const unsigned char MOV_EBP_ESP2 = 0xEC;
const unsigned char POP_EBP = 0x5D;
const unsigned char NEAR_RET = 0xC3;
//more constants
const unsigned char PUSH_EBX = 0x53;
const unsigned char PUSH_ESI = 0x56;
const unsigned char PUSH_EDI = 0x57;
const unsigned char POP_EDI = 0x5F;
const unsigned char POP_ESI = 0x5E;
const unsigned char POP_EBX = 0x5B;
//
const unsigned char IMMEDIATE_TO_EAX = 0xB8;
//followed by 4 byte address.
const unsigned char PUSH_EAX = 0x50;

// Put one instruction at a time into mCode:
void InstructionsClass::Encode(unsigned char c)
{	//
	if (mCurrent + sizeof(unsigned char) < MAX_INSTRUCTIONS)
	{
		mCode[mCurrent] = c;
		mCurrent += sizeof(unsigned char);
	}
	else
	{
		std::cerr << "Error. Used up all " << MAX_INSTRUCTIONS
			<< " instructions." << std::endl;
		exit(1);
	}
}
void InstructionsClass::Encode(int x)
{
	if (mCurrent + sizeof(int) <= MAX_INSTRUCTIONS)
	{
		//using memcpy instead of mCode[mCurrent] = x;

		memcpy(&mCode[mCurrent], &x, sizeof(int));
		mCurrent += sizeof(int);
	}
	else
	{
		std::cerr << "Error. Buffer overflow." << std::endl;
		exit(1);
	}
}

void InstructionsClass::Encode(long long int xx)
{
	if (mCurrent + sizeof(long long) <= MAX_INSTRUCTIONS)
	{
		*((long long*)(&(mCode[mCurrent]))) = xx;
		mCurrent += sizeof(long long);
	}
	else
	{
		std::cerr << "Error. Buffer overflow." << std::endl;
		exit(1);
	}

}

void InstructionsClass::Encode(void* p)
{
	int pointerSize = sizeof(p);
	if (pointerSize == 4)
	{	//chad says  Encode((int)(uintptr_t)p);
		Encode((int)(long long)p);
	}
	else if (sizeof(p) == 8)
	{
		Encode((long long)p);
	}
}


InstructionsClass::InstructionsClass()
{
	//rip
	mprotect((void*)((uintptr_t)mCode & ~(sysconf(_SC_PAGE_SIZE) - 1)),
		MAX_INSTRUCTIONS, PROT_READ | PROT_WRITE | PROT_EXEC);
	//DWORD oldProtect;



	// Initialize all class variables:
	mCurrent = 0;
	mStartOfMain = 0;
	mPrintInteger = 0;
	mTempInteger = 0;
	mMinusString = '-';
	mSpaceString = ' ';

	// Record where the PrintIntegerLinux64 function starts:
	mStartOfPrint = mCurrent;
	// Code one function PrintIntegerLinux64 that prints an integer.
	// It will be called later many times.
	PrintIntegerLinux64(); // Write all the codes into mCode.
	// Now record where the main finc
	mStartOfMain = mCurrent;
	// All functions start this way. So does our main function.
	Encode(PUSH_EBP);
	Encode(MOV_EBP_ESP1);
	Encode(MOV_EBP_ESP2);
	// Make sure we save and restore all 5 Callee-Save registers.
	// That is, EBP, ESP, EBX, ESI, and EDI
	Encode(PUSH_EBX);
	Encode(PUSH_ESI);
	Encode(PUSH_EDI);
}

// Modified from https://baptiste-wicht.com/posts/2011/11/print-stringsintegers-intel-assembly.html
// This is made into a function, so it can be called per cout instead of
//rewritten every time.
// The integer to print should be previously stored in mPrintInteger.
void InstructionsClass::PrintIntegerLinux64()
{
	// All functions start this way. So does PrintInteger.
	Encode(PUSH_EBP);
	Encode(MOV_EBP_ESP1);
	Encode(MOV_EBP_ESP2);
	// Make sure we save and restore all 5 Callee-Save registers.
	// That is, EBP, ESP, EBX, ESI, and EDI,
	Encode(PUSH_EBX);
	Encode(PUSH_ESI);
	Encode(PUSH_EDI);
	// Get the integer to print from mPrintInteger:
	Encode(MEM_TO_EAX);
	Encode(&mPrintInteger);
	// Check if the number to print is negative:
	Encode(CMP_EAX1);
	Encode(CMP_EAX2);
	Encode((unsigned char)0);
	// Jump if the integer is Not negative
	Encode(JGE);
	unsigned char DistanceToJump = 0; // fill in later
	int fillInAddress = mCurrent;
	Encode(DistanceToJump); // fill in this distance later
	unsigned char* jumpFrom = GetAddress();
	// Negate negative integers:
	Encode(NEG_EAX1);
	Encode(NEG_EAX2);
	// Print the minus sign, first saving register EAX.
	Encode(PUSH_EAX);
	WriteMinusLinux64();
	Encode(POP_EAX);
	// Fill in how far to jump from before:
	unsigned char* beginningOfPrintPositiveInteger = GetAddress();
	mCode[fillInAddress] = (unsigned char)
		(beginningOfPrintPositiveInteger - jumpFrom);

	// Jump to here!
	// Beginning of Write Positive Integer:
	// ECX is counter for how many decimal bytes are in the integer
	Encode(IMMEDIATE_TO_ECX);
	Encode((int)0);
	// Beginning of loop1.
	// It puts all the ascii characters of the integer on the stack.
	unsigned char* divide_loop = GetAddress();
	// increment the counter
	Encode(ADD_ECX1);
	Encode(ADD_ECX2);
	Encode((unsigned char)1);
	// Clear out high bytes before division
	Encode(CDQ); // Necessary to clear the D register.
	// edx = eax % 10
	Encode(IMMEDIATE_TO_EBX);
	Encode((int)10); // Divide by 10
	Encode(DIV_EAX_EBX1); // divide eax by ebx
	Encode(DIV_EAX_EBX2); // remainder result in edx
	// convert decimal remainder to ascii by adding 48.
	Encode(ADD_EDX1);
	Encode(ADD_EDX2);
	Encode((unsigned char)48);
	// ascii remainder onto stack
	Encode(PUSH_EDX);
	// we stop loop1 when quotient (eax) is zero
	Encode(CMP_EAX1);
	Encode(CMP_EAX2);
	Encode((unsigned char)0);
	// repeat loop1 while quotient != 0. Encode the jump.
	unsigned char* end_divide_loop = GetAddress() + 2;
	Encode(JNE);
	Encode((unsigned char)(divide_loop - end_divide_loop));
	// End of loop1.
	// 
	// Beginning of loop2.
	// It pops and prints all ascii characters.
	unsigned char* print_loop = GetAddress();
	// Code to print a character using syscall:
	{
		Encode(POP_EAX);
		Encode(EAX_TO_MEM);
		Encode(&mPrintInteger);
		Encode(BIT64);
		Encode(IMMEDIATE_TO_ESI); // move into ESI
		Encode(&mPrintInteger); // address of bytes to print
		Encode(IMMEDIATE_TO_EAX);
		Encode((int)1); // 1 for print syscall
		Encode(IMMEDIATE_TO_EDI);
		Encode((int)1); // 1 for stdout port

		Encode(IMMEDIATE_TO_EDX);
		Encode((int)1); // length of bytes to print
		// Engage 64 bit syscall with special codes 0x0F, 0x05
		// The EAX register indicates which syscall (print)
		// The EDI tells which port to print to (stdout)
		// The ESI contains the address to print
		// The EDX says how many bytes to print
		Encode(PUSH_ECX); // First save important registers
		Encode((unsigned char)SYS_CALL1);
		Encode((unsigned char)SYS_CALL2);
		Encode(POP_ECX); // Restore important register
	}
	// Decrement the count of characters left to print
	Encode(SUB_ECX1);
	Encode(SUB_ECX2);
	Encode((unsigned char)1);
	// Are there no characters left to print?
	Encode(CMP_ECX1);
	Encode(CMP_ECX2);
	Encode((unsigned char)0);
	// Repeat loop if there are more characters to print
	unsigned char* end_print_loop = GetAddress() + 2;
	Encode(JNE);
	Encode((unsigned char)(print_loop - end_print_loop));
	// End of loop2.
	// Separate multiple printed items with a space.
	WriteSpaceLinux64();
	// Restore Callee-Saved registers:
	Encode(POP_EDI);
	Encode(POP_ESI);
	Encode(POP_EBX);
	// All functions end this way:
	Encode(POP_EBP);
	Encode(NEAR_RET);
}

void WriteSpaceLinux64() {
	//Implentment
}


// 64 bit print syscall Taken from:
//https://stackoverflow.com/questions/22503944/using-interrupt-0x80-on64-bit-linux
void InstructionsClass::WriteMinusLinux64()
{
	Encode(IMMEDIATE_TO_EAX);
	Encode((int)1); // 1 for print syscall
	Encode(IMMEDIATE_TO_EDI);
	Encode((int)1); // 1 for stdout port
	Encode(BIT64);
	Encode(IMMEDIATE_TO_ESI);
	Encode(&mMinusString); // address of bytes to print
	Encode(IMMEDIATE_TO_EDX);
	Encode((int)1); // length of bytes to print
	// 64 bit syscall:
	Encode((unsigned char)SYS_CALL1);
	Encode((unsigned char)SYS_CALL2);
}

void InstructionsClass::WriteSpaceLinux64()
{
	Encode(IMMEDIATE_TO_EAX);
	Encode((int)1); // 1 for print syscall
	Encode(IMMEDIATE_TO_EDI);
	Encode((int)1); // 1 for stdout port
	Encode(BIT64);
	Encode(IMMEDIATE_TO_ESI);
	Encode(&mSpaceString); // address of bytes to print
	Encode(IMMEDIATE_TO_EDX);
	Encode((int)1); // length of bytes to print
	// 64 bit syscall:
	Encode((unsigned char)SYS_CALL1);
	Encode((unsigned char)SYS_CALL2);
}

void InstructionsClass::PopAndWrite()
{
	// Move the integer to be printed from stack to mPrintInteger:
	Encode(POP_EAX);
	Encode(EAX_TO_MEM);
	Encode(&mPrintInteger);
	// Call previously coded function that prints mPrintInteger
	Call((void*)&(mCode[mStartOfPrint]));
	// &(mCode[mStartOfPrint])is where PrintIntegerLinux64 is.
}

void InstructionsClass::Call(void* function_address)
{
	unsigned char* a1 = (unsigned char*)function_address;
	unsigned char* a2 = (unsigned char*)(&mCode[mCurrent + 5]);
	int offset = (int)(a1 - a2);
	Encode(CALL);
	Encode(offset);
}

unsigned char* InstructionsClass::GetAddress()
{
	return &(mCode[mCurrent]);
}

// <><><><><><<><><><><><<><><><><><<><><><><><

void InstructionsClass::Finish()
{
	// Retore Callee-Saved registers:
	Encode(POP_EDI);
	Encode(POP_ESI);
	Encode(POP_EBX);
	// All functions end this way:
	Encode(POP_EBP);
	Encode(NEAR_RET);
	std::cout << "Finished creating " << mCurrent <<
		" bytes of machine code" << std::endl;
}
void InstructionsClass::Execute()
{
	// Jump into the main function of what we just coded,
	// found at mCode[mStartOfMain]
	std::cout << "About to Execute the machine code..." << std::endl;
	void* ptr = &(mCode[mStartOfMain]);
	void (*f)(void);
	f = (void (*)(void)) ptr;
	f();
	// Did everything work?
	std::cout << "\nThere and back again!" << std::endl;
}
void InstructionsClass::PushValue(int value)
{
	Encode(IMMEDIATE_TO_EAX);
	Encode(value);
	Encode(PUSH_EAX);
	std::cout << "Finished PushValue :" << value << " the machine code..." << std::endl;
}

