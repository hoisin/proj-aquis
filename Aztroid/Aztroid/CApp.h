/*
	30/07/2015

	Application code
*/

#ifndef __CAPP_H__
#define __CAPP_H__

#include <memory>
#include "SDL.h"

class CGfx;
class CInput;
class CBreakOut;

class CApp
{
public:
	enum EAppState {
		ESplashLoad,
		EMainMenu,
		EGameOver,
		EGameRun,
		ELoadLevel,
		EShutDown,
		ETotalStates
	};

public:
	CApp();
	~CApp();

	bool Intitialise(unsigned int updateTick);

	void Run();

private:
	void Update(unsigned int deltaT);

	void Draw(unsigned int deltaT);

	void InputProcess(unsigned int deltaT);

	void GameRun(SDL_Event sdlEvent);

private:
	bool m_bRun;

	CGfx* m_pGfx;
	std::shared_ptr<CInput> m_pInput;

	unsigned int m_lastLoopTick;
	unsigned int m_lastUpdateTick;
	unsigned int m_tick;

	EAppState m_state;

	int m_currentOption;
};


#endif