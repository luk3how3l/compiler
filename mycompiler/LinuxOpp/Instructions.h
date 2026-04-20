#pragma once

const int MAX_INSTRUCTIONS = 5000;
class InstructionsClass
{
public:
	InstructionsClass();
	void Encode(unsigned char c);
	void Encode(void* p);
	void Encode(int x);
	void Encode(long long int x);
	void Finish();
	void Execute();
	void PushValue(int value);
	void PopAndWrite(int value);
	void PrintIntegerLinux64();
	void PrintMinusLinux64();
	void PrintSpaceLinux64();
	void WriteMinusLinux64();
	void WriteSpaceLinux64();
	void PopAndWrite();
	unsigned char* GetAddress();
	void Call(void* function_address);


private:
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

};

