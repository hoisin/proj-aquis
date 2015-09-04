#include <iostream>

#include "CApp.h"

int main(int argc, char* argv[])
{
	
	CApp newApp;

	if (newApp.Intitialise(50))
		newApp.Run();
	
	return 0;
}