/*
	Currently testing template math vector 2
*/

#include <iostream>

#include "CBVec2.h"



int main(int argc, char* argv[])
{
	cbmath::Vec2<int> test(10,10);
	cbmath::Vec2<int> test2(2, 2);
	cbmath::Vec2<float> my(40.f, 2.f);
	cbmath::Vec2<float> copy(my);

	test2 += cbmath::Vec2<int>(100,100);
	test2 = test / cbmath::Vec2<int>(2,2);
	copy -= cbmath::Vec2<float>(20, 5);

	std::cout << "Test 1: " << test.x << " " << test.y << std::endl;
	std::cout << "Test 2: " << test2.x << " " << test2.y << std::endl;
	std::cout << "Test 3: "<< copy.x << " " << copy.y << std::endl;

	system("PAUSE");
	return 0;
}