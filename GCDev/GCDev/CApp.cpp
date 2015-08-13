#include "CApp.h"

#include "SDL.h"

#include "CGfx.h"
#include "CInput.h"
#include "CKeyboard.h"
#include "CBreakOut.h"

#include "CPaddle.h"


CApp::CApp() : m_bRun(false), m_pGfx(nullptr), m_pInput(nullptr), m_lastLoopTick(0), m_lastUpdateTick(0), m_tick(0), m_state(ESplashLoad)
{
}


CApp::~CApp()
{
}


//---------------------------------------------------------------------------
//
//	Run()
//
//	Descrition:
//	Main running method
//
//---------------------------------------------------------------------------
void CApp::Run()
{
	SDL_Event sdlEvent;

	while (m_bRun) {

		switch (m_state)
		{
		case ESplashLoad:
			break;

		case ELoadLevel:
			break;

		case EGameRun:
		{
			// Handle events on queue.
			// Must be called to detect input events
			while (SDL_PollEvent(&sdlEvent) != 0) {

				// User quits
				if (sdlEvent.type == SDL_QUIT)
					m_bRun = false;
			}

			unsigned int currentTick = SDL_GetTicks();

			// The amount of elapsed time from last update to current
			unsigned int deltaUpdateT = currentTick - m_lastUpdateTick;

			// The amount of elapsed time from last loop to current
			unsigned int deltaLoopT = currentTick - m_lastLoopTick;
			m_lastLoopTick = currentTick;

			// Check input 
			m_pInput->Update(deltaLoopT);

			// Update if enough time elapsed
			if (deltaUpdateT > m_tick) {
				InputProcess(deltaUpdateT);

				m_lastUpdateTick = currentTick;
				Update(deltaUpdateT);
			}

			// Draw
			Draw(deltaLoopT);
		}
			break;

		case EQuit:
			m_bRun = false;
			break;

		default:
			break;
		}
	}

	SDL_Quit();
}


//---------------------------------------------------------------------------
//
//	Initialise()
//
//	Description:
//	Initialises application
//
//---------------------------------------------------------------------------
bool CApp::Intitialise(unsigned int updateTick)
{
	m_bRun = true;

	m_tick = updateTick;

	// Create instance of graphics component
	m_pGfx = new CGfx;
	m_pGfx->Initialise(800, 600, "SDL Window");

	m_pGfx->LoadTexture("..\\Assets\\backgroundTest.bmp");

	m_pGfx->LoadFont("..\\Assets\\cambria.ttf", 24);

	m_pInput.reset(new CInput);
	m_pInput->Initialise(100);

    m_pGame.reset(new CBreakOut);
    m_pGame->Initialise(m_pGfx);

    m_pGame->SetLevel(1, 800, 600);

	m_state = EGameRun;

	return true;
}


//---------------------------------------------------------------------------
//
//	Update()
//
//	Descrition:
//	Performs updating code
//
//---------------------------------------------------------------------------
void CApp::Update(unsigned int deltaT)
{
	m_pGame->Update(deltaT);
}


//---------------------------------------------------------------------------
//
//	Draw()
//
//	Descrition:
//	Performs any drawing required
//
//---------------------------------------------------------------------------
void CApp::Draw(unsigned int deltaT)
{
	m_pGfx->BeginDraw(true);

	m_pGame->Draw(deltaT, m_pGfx);

	m_pGfx->EndDraw();
}


void CApp::InputProcess(unsigned int deltaT)
{
	auto paddle = (CPaddle*)m_pGame->GetEntity("paddles", 0);

	if (m_pInput->GetKeyboard()->IsKeyHeld(SDLK_LEFT))
		paddle->MoveLeft(10);

	if (m_pInput->GetKeyboard()->IsKeyHeld(SDLK_RIGHT))
		paddle->MoveRight(10);

	if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_ESCAPE))
		m_state = EQuit;
}