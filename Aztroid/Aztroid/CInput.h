/*
	31/07/2015

	Input Interface
*/


#ifndef __CINPUT_H__
#define __CINPUT_H__


#include <memory>
#include "SDL.h"
#include "CKeyboard.h"

class CInput
{
public:
	CInput();
	~CInput();

	bool Initialise(Uint16 keyHeldTime);

	void Update(Uint32 delta);

	std::shared_ptr<CKeyboard> GetKeyboard();

private:
	std::shared_ptr<CKeyboard> m_pKeyboard;
};


#endif