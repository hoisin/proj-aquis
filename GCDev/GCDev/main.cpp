#include <iostream>

#include "SDL.h"
#include <stdio.h>

#include "CApp.h"
#include "Math.h"

int main(int argc, char* argv[])
{
	//CApp app;

	//if(app.Intitialise(50))
	//	app.Run();

	Vec2<int> test(1, 2), test2(1, 2);

	test += test2;

	std::cout << test.x << " " << test.y << std::endl;
	
	system("PAUSE");
	return 0;
}