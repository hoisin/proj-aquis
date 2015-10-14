#include "CApp.h"

#include "SDL.h"

#include "CGfx.h"
#include "CInput.h"
#include "CKeyboard.h"

#include "CAztroid.h"

#include "CObject.h"
#include "Utility.h"


CApp::CApp() : m_bRun(false), m_pGfx(nullptr), m_pInput(nullptr),
	m_pGame(nullptr), m_lastLoopTick(0), m_lastUpdateTick(0), m_tick(0), m_state(ESplashLoad)
{
	myTexture = -1;
	myRot = 0;
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

		case EMainMenu:
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
				}

				// Draw
				Draw(deltaLoopT);
			}
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

					// Update components
					InputProcess(deltaUpdateT);
					Update(deltaUpdateT);

					// Update the last tick
					m_lastUpdateTick = currentTick;
				}

				// Draw
				Draw(deltaLoopT);
			}
			break;

		case EGameOver:
			{	
				unsigned int currentTick = SDL_GetTicks();
				unsigned int deltaUpdateT = currentTick - m_lastUpdateTick;
				
				unsigned int deltaLoopT = currentTick - m_lastLoopTick;

				if (deltaUpdateT > 5000)
					m_state = EMainMenu;

				Draw(deltaLoopT);
			}
			break;

		case EShutDown:
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
	m_pGfx.reset(new CGfx);
	m_pGfx->Initialise(800, 600, "Aztroid");

	// Load font 
	m_pGfx->LoadFont("..\\Assets\\cambria.ttf", 24);

	m_pInput.reset(new CInput);
	m_pInput->Initialise(100);

	m_pGame.reset(new CAztroid);
	m_pGame->Initialise(m_pGfx.get(), 800, 600, m_tick);

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
	switch (m_state)
	{
	case ESplashLoad:
		break;

	case EMainMenu:
		break;

	case EGameRun:
		m_pGame->Update(deltaT);
		break;

	case EGameOver:
		break;

	default:
		break;

	}
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
	int texWidth = 0, texHeight = 0;

	switch (m_state)
	{
	case ESplashLoad:
		break;

	case EMainMenu:
		m_pGfx->BeginDraw(true, 64, 128, 64);

		m_pGfx->EndDraw();
		break;

	case EGameRun:
		m_pGfx->BeginDraw(true, 150, 180, 200);
		m_pGame->Draw(deltaT, m_pGfx.get());
		m_pGfx->EndDraw();
		break;

	case EGameOver:
		m_pGfx->BeginDraw(true, 64, 128, 64);

		m_pGfx->EndDraw();
		break;

	default:
		break;

	}
}


//---------------------------------------------------------------------------
//
//	InputProcess()
//
//	Descrition:
//	Input process handler
//
//---------------------------------------------------------------------------
void CApp::InputProcess(unsigned int deltaT)
{
	switch (m_state)
	{
	case EMainMenu:
		break;

	case EGameRun:

		if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_ESCAPE))
			m_state = EShutDown;

		if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_w) ||
			m_pInput->GetKeyboard()->IsKeyHeld(SDLK_w)) 
			m_pGame->GetObject("ships", 0)->VMove(eUp);
		
		if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_s) ||
			m_pInput->GetKeyboard()->IsKeyHeld(SDLK_s))
			m_pGame->GetObject("ships", 0)->VMove(eDown);

		if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_a) ||
			m_pInput->GetKeyboard()->IsKeyHeld(SDLK_a))
			m_pGame->GetObject("ships", 0)->VMove(eLeft);


		if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_d) ||
			m_pInput->GetKeyboard()->IsKeyHeld(SDLK_d))
			m_pGame->GetObject("ships", 0)->VMove(eRight);

		if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_SPACE) ||
			m_pInput->GetKeyboard()->IsKeyHeld(SDLK_SPACE))
			m_pGame->GetObject("ships", 0)->VFire();
		break;

	default:
		break;

	}
}