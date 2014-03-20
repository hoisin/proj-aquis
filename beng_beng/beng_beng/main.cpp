//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Main entry point
//
//--------------------------------------------------------------------------

#include <Windows.h>
#include "CApp.h"

//#include <iostream>
//
//#include "Math.h"
//
//using namespace beng;
//
//int main(int argc, char* argv [])
//{
//	Vec2i test(0,10);
//	Vec2i test2(15, 0);
//
//	test = test + test2;
//
//	std:: cout << "Dot: " << Dot(test,test2) << " Angle: " << Angle(test,test2) << std::endl;
//
//	system("PAUSE");
//
//	return 0;
//}

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

