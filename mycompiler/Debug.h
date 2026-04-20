#pragma once
//6
#include <stdio.h>
#include <iostream>

//showmessage can be set as 0 or 1 as binary switch
#define ShowMessages 0
//This is used as a switch to control a macro called MSG(X).  

//If ShowMessages is 1, #define MSG(X) to “std::cout << X << std::endl”. 
// Otherwise, MSG(X) should map to nothing. 
#if ShowMessages
	#define MSG(X) std::cout << X << std::endl;
#else
	#define MSG(X);
#endif
