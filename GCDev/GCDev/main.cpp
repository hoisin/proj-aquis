#include <iostream>

#include "SDL.h"
#include <stdio.h>

#include "CApp.h"


int main(int argc, char* argv[])
{
	CApp app;

	if(app.Intitialise(50))
		app.Run();

	return 0;
}