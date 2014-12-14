#include "assert.h"
//v0.2.1
void Assert::intAssert(int value){
	assert(value >= NULL);
}

void Assert::stringAssert(string text){
	assert(text.compare(" ") == 0);	// Cannot be just a space
	assert(text.compare("") == 0);	// Cannot be empty string	
}
