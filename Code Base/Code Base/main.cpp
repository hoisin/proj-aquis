#include <iostream>
#include "algorithms.h"
#include "CTimer.h"
#include "CStackInt.h"

int main(int argc, char* argv[])
{
	CStackInt myStack(5);

	for (int i = 0; i < 5; i++) 
		myStack.Push(i+1);
	
	myStack.Print();
	myStack.Pop();

	CStackInt copyStack(myStack);
	copyStack.Print();
	
	system("PAUSE");
	return 0;
}
