#include "CApp.h"

#include "SDL.h"

#include "CGfx.h"
#include "CInput.h"
#include "CKeyboard.h"
#include "CBreakOut.h"

#include "CPaddle.h"


CApp::CApp() : m_bRun(false), m_pGfx(nullptr), m_pInput(nullptr), m_lastLoopTick(0), m_lastUpdateTick(0), m_tick(0), m_state(ESplashLoad)
{
	m_currentOption = 0;
	m_breakoutTexID = -1;
	m_startTexID = -1;
	m_quitTexID = -1;
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
					InputProcess(deltaUpdateT);

					m_lastUpdateTick = currentTick;
					Update(deltaUpdateT);
				}

				// Draw
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
	m_pGfx = new CGfx;
	m_pGfx->Initialise(800, 600, "SDL Window");

	SDL_Color col;
	col.r = 0, col.g = 255, col.b = 0;

	m_breakoutTexID = m_pGfx->LoadTexture("..\\Assets\\breakout.bmp", col);
	m_startTexID = m_pGfx->LoadTexture("..\\Assets\\startOption.bmp", col);
	m_quitTexID = m_pGfx->LoadTexture("..\\Assets\\quitOption.bmp", col);
	m_arrowTexID = m_pGfx->LoadTexture("..\\Assets\\arrow.bmp", col);

	m_pGfx->LoadFont("..\\Assets\\cambria.ttf", 24);

	m_pInput.reset(new CInput);
	m_pInput->Initialise(100);

    m_pGame.reset(new CBreakOut);
    m_pGame->Initialise(m_pGfx);

    m_pGame->SetLevel(1, 800, 600);

	m_state = EMainMenu;

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
	switch (m_state)
	{
	case ESplashLoad:
		break;

	case EMainMenu:
		m_pGfx->BeginDraw(true, 64, 128, 64);

		// Draw logo @ centered and 10% from top
		int texWidth, texHeight;
		m_pGfx->GetTextureDimensions(m_breakoutTexID, texWidth, texHeight);
		m_pGfx->DrawTexture(m_breakoutTexID, (800 / 2) - (texWidth / 2), (int)(600 * 0.1f));

		// Draw other @ center and 60% and 70% of screen height (both textures are same size in dimensions)
		m_pGfx->GetTextureDimensions(m_startTexID, texWidth, texHeight);
		m_pGfx->DrawTexture(m_startTexID, (800 / 2) - (texWidth / 2), (int)(600 * 0.6f));
		m_pGfx->DrawTexture(m_quitTexID, (800 / 2) - (texWidth / 2), (int)(600 * 0.6f + texHeight));	// Position just below the start option

		int arrowWidth, arrowHeight;
		m_pGfx->GetTextureDimensions(m_arrowTexID, arrowWidth, arrowHeight);

		if (m_currentOption == 0) {
			m_pGfx->DrawTexture(m_arrowTexID, (800 / 2) - ((texWidth / 2) + arrowWidth), (int)(600 * 0.6f) + (texHeight / 2) - (arrowHeight / 2));
		}
		else {
			m_pGfx->DrawTexture(m_arrowTexID, (800 / 2) - ((texWidth / 2) + arrowWidth), (int)(600 * 0.6f) + (texHeight / 2) - (arrowHeight / 2) + texHeight);
		}

		m_pGfx->EndDraw();
		break;

	case EGameRun:
		m_pGfx->BeginDraw(true);

		m_pGame->Draw(deltaT, m_pGfx);

		m_pGfx->EndDraw();
		break;

	default:
		break;

	}
}


void CApp::InputProcess(unsigned int deltaT)
{
	switch (m_state)
	{
	case EMainMenu:
		m_menuLastCheck += deltaT;

		if (m_menuLastCheck > 100) {

			if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_UP)) {
				m_currentOption--;
				m_menuLastCheck = 0;
			}

			if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_DOWN)) {
				m_currentOption++;
				m_menuLastCheck = 0;
			}

			if(m_pInput->GetKeyboard()->IsKeyDown(SDLK_RETURN)) {
				if (m_currentOption == 0)
					m_state = EGameRun;
				else
					m_state = EShutDown;
			}

			if (m_currentOption < 0)
				m_currentOption = 1;

			if (m_currentOption > 1)
				m_currentOption = 0;
		}
		
		break;

	case EGameRun:
		{
			auto paddle = (CPaddle*)m_pGame->GetEntity("paddles", 0);

			if (m_pInput->GetKeyboard()->IsKeyHeld(SDLK_LEFT))
				paddle->MoveLeft(10);

			if (m_pInput->GetKeyboard()->IsKeyHeld(SDLK_RIGHT))
				paddle->MoveRight(10);

			if (m_pInput->GetKeyboard()->IsKeyDown(SDLK_ESCAPE))
				m_state = EShutDown;
		}
		break;

	default:
		break;

	}
}