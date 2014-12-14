#ifndef _ASSERT_H_
#define _ASSERT_H_

//v0.2.1

#define NDEBUG 
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Assert{
public:
	void intAssert(int);
	void stringAssert(string);
};
#endif
