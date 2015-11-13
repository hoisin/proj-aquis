#include "CStackInt.h"

#include <iostream>

CStackInt::CStackInt() : top(nullptr), stack(nullptr), count(0), maxSize(10)
{
	stack = new int[maxSize];
	std::fill(stack, stack + maxSize, 0);
	//memset(stack, 0, sizeof(int)* maxSize);
}


CStackInt::CStackInt(int stackSize) : top(nullptr), stack(nullptr), count(0), maxSize(stackSize)
{
	stack = new int[maxSize];
	std::fill(stack, stack + maxSize, 0);
	//memset(stack, 0, sizeof(int)* maxSize);
}


CStackInt::CStackInt(const CStackInt& other)
{
	if (this == &other)
		std::cout << "Error: Self assignment" << std::endl;
	else {
		maxSize = other.GetMaxSize();
		stack = new int[maxSize];
		std::fill(stack, stack + maxSize, 0);
		//memset(stack, 0, sizeof(int)* maxSize);
		top = stack;
		memcpy(stack, other.stack, sizeof(int)* other.count);
	}
}


CStackInt::~CStackInt()
{
	top = nullptr;
	delete[] stack;
	stack = nullptr;
	count = 0;
	maxSize = 0;
}


int CStackInt::Top()
{
	return *top;
}


void CStackInt::Push(int value)
{
	if (count == 0) {
		top = stack;
		*top = value;
		count++;
	}
	else {
		if (count < maxSize) {
			top++;
			count++;
			*top = value;
		}
		else
			std::cout << "Error: Stack full" << std::endl;	
	}
}


int CStackInt::Pop()
{
	int returnVal = *top;
	top--;
	count--;
	return returnVal;
}


bool CStackInt::IsEmpty()
{
	return (count == 0) ? true : false;
}


void CStackInt::Print()
{
	std::cout << "Printing Stack: " << std::endl;
	int* temp = stack;
	for (int i = 0; i < maxSize; i++){
		std::cout << "Element " << i << " : " << *temp << std::endl;
		temp++;
	}
}