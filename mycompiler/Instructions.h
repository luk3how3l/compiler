#pragma once

const int MAX_INSTRUCTIONS = 5000;
const int MAX_DATA = 5000;
class InstructionsClass
{
public:
	InstructionsClass();

	void Finish();
	void Execute();
	void PushValue(int value);
	void PopAndWrite(int value);
	// +-/*
	void PopPopDivPush();
	void PopPopAddPush();
	void PopPopSubPush();
	void PopPopMulPush();
	// relation operators
	void PopPopLessPush();
	void  PopPopNEQPush();
	void  PopPopEQPush();
	void  PopPopGreEQPush();
	void  PopPopLessEQPush();
	void  PopPopGrePush();
	void PopPopAndPush();
	void PopPopOrPush();
	unsigned char * Jump();
	unsigned char * SkipIfZeroStack();
	void SetOffset(unsigned char * codeAddress, int offset);
	void PrintAllMachineCodes();
	void PrintMinusLinux64();
	void PrintSpaceLinux64();
	void WriteSpaceLinux64();
	void PopAndWrite();
	void PopAndStore(int index);
	unsigned char* GetAddress();
	void PushVariable(int index);

private:
	void PopPopComparePush(unsigned char relational_operator);
	void WriteMinusLinux64();
	void PrintIntegerLinux64();
	void Call(void* function_address);
	int* GetMem(int index);
	void Encode(unsigned char c);
	void Encode(void* p);
	void Encode(int x);
	void Encode(long long int x);

	unsigned char mCode[MAX_INSTRUCTIONS];
	int mCurrent; // where we are in mCode
	int mPrintInteger;
	// Location to store an integer about to be printed.
	int mTempInteger;
	// Location to store one char of integer to be printed.
	int mStartOfPrint;
	// The value of mCurrent where PrintIntegerLinux 64 starts.
	// Jump to this offset of mCode to print.
	int mStartOfMain;
	// the value of mCurrent after coding the Print functions.
	// Jump to this offset of mCode to start program execution.
	char mMinusString; // Holds '-'
	char mSpaceString; // Holds ' '
	int mData[MAX_DATA];
};
