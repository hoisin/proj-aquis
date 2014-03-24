//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Main entry point, win32 based
//
//--------------------------------------------------------------------------

#include <Windows.h>
#include "CApp.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{
	CApp app;

	if(!app.InitialiseApp("opengl_3_3"))
		return 0;

	app.RegisterAppClass(hInstance);

	if(!app.CreateAppWindow("OpenGL 3.3 App", 800, 600))
		return 0;

	app.AppRun();
	app.ShutDown();

	return 0;
}

