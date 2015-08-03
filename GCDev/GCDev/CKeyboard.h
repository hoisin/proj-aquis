/*
	31/07/2015

	The keyboard
*/

#ifndef __CKEYBOARD_H__
#define __CKEYBOARD_H__

#include "SDL.h"

class CKeyboard
{
public:
	CKeyboard();
	~CKeyboard();

	void SetHeldTime(Uint16 heldTime);

	void Update(unsigned int delta);

	bool IsKeyDown(char key);
	bool IsKeyUp(char key);
	bool IsKeyHeld(char key);

private:
	char		m_keys[256];			// State for each ASCII key
	Uint32		m_keysTime[256];		// Time for each key held down for

	Uint16		m_heldTime;				// Time to wait for key to be held to detect as held
};

#endif