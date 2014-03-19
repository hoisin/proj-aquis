//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Main entry point
//
//--------------------------------------------------------------------------

#include <iostream>

#include "Math.h"

using namespace beng;

int main(int argc, char* argv [])
{
	Vec2i test(0,10);
	Vec2i test2(15, 0);

	test = test + test2;

	std:: cout << "Dot: " << Dot(test,test2) << " Angle: " << Angle(test,test2) << std::endl;

	system("PAUSE");

	return 0;
}