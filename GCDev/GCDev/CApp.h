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
	std::shared_ptr<CBreakOut> m_pGame;

	unsigned int m_lastLoopTick;
	unsigned int m_lastUpdateTick;
	unsigned int m_tick;

	EAppState m_state;

	int m_currentOption;

	// Main menu texture IDS
	int m_breakoutTexID;
	int m_startTexID;
	int m_quitTexID;
	int m_arrowTexID;

	int m_menuLastCheck;
};


#endif