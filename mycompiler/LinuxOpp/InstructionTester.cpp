#include "Instructions.h"

#include <iostream>




int main()
{
	InstructionsClass code;
	code.PushValue(-500);
	code.PopAndWrite();
	code.PushValue(1000);
	code.PopAndWrite();
	code.Finish();
	code.Execute();
	return 0;

}
