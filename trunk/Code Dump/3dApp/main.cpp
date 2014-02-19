#include <iostream>

#include "C3DApp.h"


//memory leak detection
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

#include "CTimer.h"



int main(int argc, char* argv [])
{
	//memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(220);

	C3DApp app;

	if(app.Initialise(L"3D Renderer", 1024, 768))
		app.Run();

	//system("PAUSE");

	return 0;
}