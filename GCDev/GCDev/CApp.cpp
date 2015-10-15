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
	m_gameOverTexID = -1;
	m_menuLastCheck = 0;
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

		unsigned int currentTick = SDL_GetTicks();

		// The amount of elapsed time from last update to current
		unsigned int deltaUpdateT = currentTick - m_lastUpdateTick;

		// The amount of elapsed time from last (main)loop to current
		unsigned int deltaLoopT = currentTick - m_lastLoopTick;

		switch (m_state)
		{
		case ESplashLoad:
			break;

		case EMainMenu:
			// Handle events on queue.
			// Must be called to detect input events
			while (SDL_PollEvent(&sdlEvent) != 0) {

				// User quits
				if (sdlEvent.type == SDL_QUIT)
					m_bRun = false;
			}

			// Update last loop tick
			m_lastLoopTick = currentTick;

			// Check input 
			m_pInput->Update(deltaLoopT);

			// Update if enough time elapsed
			if (deltaUpdateT > m_tick) {
				InputProcess(deltaUpdateT);

				// Update last update tick
				m_lastUpdateTick = currentTick;
			}

			// Draw
			Draw(deltaLoopT);
			break;

		case EGameRun:
			// Handle events on queue.
			// Must be called to detect input events
			while (SDL_PollEvent(&sdlEvent) != 0) {

				// User quits
				if (sdlEvent.type == SDL_QUIT)
					m_bRun = false;
			}

			// Update last loop tick
			m_lastLoopTick = currentTick;

			// Check input 
			m_pInput->Update(deltaLoopT);

			// Update if enough time elapsed
			if (deltaUpdateT > m_tick) {
				InputProcess(deltaUpdateT);

				// Update last update tick
				m_lastUpdateTick = currentTick;

				Update(deltaUpdateT);
			}

			// Draw
			Draw(deltaLoopT);
			break;

		case EGameOver:
			// Should change. Currently does nothing (we don't have game over).
			// Once 5 seconds has passed, change state to main menu
			if (deltaUpdateT > 5000)
				m_state = EMainMenu;

			Draw(deltaLoopT);

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

	// Load font
	m_pGfx->LoadFont("..\\Assets\\cambria.ttf", 24);

	// Green - 255 is used as transparency for loaded textures
	SDL_Color col;
	col.r = 0, col.g = 255, col.b = 0;

	// Load GUI assets
	m_breakoutTexID = m_pGfx->LoadTexture("..\\Assets\\breakout.bmp", col);
	m_startTexID = m_pGfx->LoadTexture("..\\Assets\\startOption.bmp", col);
	m_quitTexID = m_pGfx->LoadTexture("..\\Assets\\quitOption.bmp", col);
	m_arrowTexID = m_pGfx->LoadTexture("..\\Assets\\arrow.bmp", col);
	m_gameOverTexID = m_pGfx->LoadTexture("..\\Assets\\gameOver.bmp", col);

	// Initialise input component
	m_pInput.reset(new CInput);
	m_pInput->Initialise(100);

	// Initialise game component
    m_pGame.reset(new CBreakOut);

	if (!m_pGame->Initialise(m_pGfx)) {
		m_state = EShutDown;
		return false;
	}

	m_state = EMainMenu;

	return true;
}


//---------------------------------------------------------------------------
//
//	Update()
//
//	Params:
//	deltaT - Time since last update tick
//
//	Descrition:
//	Performs updating code
//
//---------------------------------------------------------------------------
void CApp::Update(unsigned int deltaT)
{
	m_pGame->Update(deltaT);

	// Check for level clear condition or game over
	if (m_pGame->IsClear()) {
		if (m_pGame->GetCurrentLevel() >= m_pGame->GetMaxLevels())
			m_state = EGameOver;
		else
		{
			// Transistion level
			m_pGame->SetLevel(m_pGame->GetCurrentLevel() + 1, 800, 600);

			// Wait a bit for game to register an update
			SDL_Delay(200);
		}
	}
}


//---------------------------------------------------------------------------
//
//	Draw()
//
//	Params:
//	deltaT - Time since last main loop (not update tick!)
//
//	Descrition:
//	Performs any drawing required
//
//---------------------------------------------------------------------------
void CApp::Draw(unsigned int deltaT)
{
	int texWidth, texHeight;

	switch (m_state)
	{
	case ESplashLoad:
		break;

	case EMainMenu:
		m_pGfx->BeginDraw(true, 64, 128, 64);

		// Draw logo @ centered and 10% from top
		m_pGfx->GetTextureDimensions(m_breakoutTexID, texWidth, texHeight);
		m_pGfx->DrawTexture(m_breakoutTexID, (800 / 2) - (texWidth / 2), (int)(600 * 0.1f));

		// Draw other @ center and 60% and 70% of screen height (both textures are same size in dimensions)
		m_pGfx->GetTextureDimensions(m_startTexID, texWidth, texHeight);
		m_pGfx->DrawTexture(m_startTexID, (800 / 2) - (texWidth / 2), (int)(600 * 0.6f));
		m_pGfx->DrawTexture(m_quitTexID, (800 / 2) - (texWidth / 2), (int)(600 * 0.6f + texHeight));	// Position just below the start option

		// Draw selection arrow on left side of menu options
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

	case EGameOver:
		m_pGfx->BeginDraw(true, 64, 128, 64);

		// Draw game over texture
		m_pGfx->GetTextureDimensions(m_gameOverTexID, texWidth, texHeight);
		m_pGfx->DrawTexture(m_gameOverTexID, (800 / 2) - (texWidth / 2), (int)(600 * 0.1f));

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
//	Params:
//	deltaT - Time since last update tick
//
//	Descrition:
//	Input handler method
//
//---------------------------------------------------------------------------
void CApp::InputProcess(unsigned int deltaT)
{
	// Handle input dependant on the game state
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
				if (m_currentOption == 0) {
					m_pGame->SetLevel(1, 800, 600);
					m_state = EGameRun;

					// Wait a bit so update tick occurs on first loop run
					SDL_Delay(200);
				}
				else
					m_state = EShutDown;
			}

			// Cap selection value
			if (m_currentOption < 0)
				m_currentOption = 1;

			if (m_currentOption > 1)
				m_currentOption = 0;
		}
		
		break;

	case EGameRun:
		{
			// Could do this a better way...
			// Prefer not to expose game logic specific code in the application framework
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