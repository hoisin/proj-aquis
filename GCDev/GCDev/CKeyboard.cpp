#include "CKeyboard.h"


CKeyboard::CKeyboard() : m_heldTime(0)
{
	for (int keys = 0; keys < 256; keys++) {
		m_keys[keys] = 'd';
		m_keysTime[keys] = 0.f;
	}
}


CKeyboard::~CKeyboard()
{
}


void CKeyboard::SetHeldTime(Uint16 heldTime)
{
	m_heldTime = heldTime;
}


void CKeyboard::Update(unsigned int delta)
{
	auto state = SDL_GetKeyboardState(nullptr);

	// Loop throught he entire keyboard
	for (int key = 0; key < 256; key++) {
		// If current key detected active by SDL
		if (state[key]) {
			// If the current key state is up
			if (m_keys[key] == 'u')	
				m_keys[key] = 'd';		// Set to down
			else
			{
				// If the current key state is down
				if (m_keys[key] == 'd') {
					// If the current key has been pressed down over a certain period of time
					if (m_keysTime[key] > m_heldTime)
						m_keys[key] = 'h';			// Set to held down
					else
						m_keysTime[key] += delta;	// Increment the time key has been pushed down.
				}
			}
		} 
		else {	// Reset state and time
			m_keys[key] = 'u';
			m_keysTime[key] = 0;
		}
	}
}


bool CKeyboard::IsKeyDown(char key)
{
	if (m_keys[key] == 'd')
		return true;

	return false;
}


bool CKeyboard::IsKeyUp(char key)
{
	if (m_keys[key] == 'u')
		return true;

	return false;
}


bool CKeyboard::IsKeyHeld(char key)
{
	if (m_keys[key] == 'h')
		return true;

	return false;
}