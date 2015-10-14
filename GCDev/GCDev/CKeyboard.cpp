#include "CKeyboard.h"


CKeyboard::CKeyboard() : m_heldTime(0)
{
	for (int keys = 0; keys < 256; keys++) {
		m_keys[keys] = 'u';
		m_keysTime[keys] = 0;
	}
}


CKeyboard::~CKeyboard()
{
}


//---------------------------------------------------------------------------
//
//	SetHeldTime()
//
//	Params:
//	heldTime	-	Time(ms) to pass to flag key as held when pressed
//
//	Descrition:
//	Sets the held time to change key state from pressed to held
//
//---------------------------------------------------------------------------
void CKeyboard::SetHeldTime(Uint16 heldTime)
{
	m_heldTime = heldTime;
}


//---------------------------------------------------------------------------
//
//	Update()
//
//	Params:
//	delta		-	Time passed since last main loop (not update tick)
//
//	Descrition:
//	Update keyboard state
//
//---------------------------------------------------------------------------
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


//---------------------------------------------------------------------------
//
//	IsKeyDown()
//
//	Params:
//	sdlKey		-	which key to check
//
//	Descrition:
//	Checks specified key if it is pressed
//
//---------------------------------------------------------------------------
bool CKeyboard::IsKeyDown(int sdlKey)
{
	if (m_keys[SDL_GetScancodeFromKey(sdlKey)] == 'd')
		return true;

	return false;
}


//---------------------------------------------------------------------------
//
//	Update()
//
//	Params:
//	sdlKey		-	which key to check
//
//	Descrition:
//	Checks specified key if it is not pressed
//
//---------------------------------------------------------------------------
bool CKeyboard::IsKeyUp(int sdlKey)
{
	if (m_keys[SDL_GetScancodeFromKey(sdlKey)] == 'u')
		return true;

	return false;
}


//---------------------------------------------------------------------------
//
//	Update()
//
//	Params:
//	sdlKey		-	which key to check
//
//	Descrition:
//	Checks specified key if it is held down
//
//---------------------------------------------------------------------------
bool CKeyboard::IsKeyHeld(int sdlKey)
{
	if (m_keys[SDL_GetScancodeFromKey(sdlKey)] == 'h')
		return true;

	return false;
}