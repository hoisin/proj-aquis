/*
	Date: 24/08/2012
	Author: Matthew Tsang

	Main Entry Point....
*/

#include <iostream>

//memory leak detection
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC


#include "C3DApp.h"
#include "CTimer.h"

using namespace std;

int main(int argc, char* argv [])
{
	//memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(220);

	// Create and run our app!
	C3DApp app;

	if(app.Initialise(L"3D Renderer", 1024, 768))
		app.Run();

	//system("PAUSE");

	return 0;
}