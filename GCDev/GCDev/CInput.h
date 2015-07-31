/*
	31/07/2015

	Input Interface
*/


#ifndef __CINPUT_H__
#define __CINPUT_H__


#include "SDL.h"

class CInput
{
public:
	CInput();
	~CInput();

	bool Initialise();

	void Update(float delta);
};


#endif