#include "CApp.h"

#include "SDL.h"

#include "CGfx.h"
#include "CInput.h"
#include "CKeyboard.h"


int gX = 0;
int gY = 0;

CApp::CApp() : m_bRun(false), m_pGfx(nullptr), m_pInput(nullptr), m_lastLoopTick(0), m_lastUpdateTick(0), m_tick(0)
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

		// Handle events on queue
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
		if (deltaUpdateT > m_tick)
		{
			if (m_pInput->GetKeyboard().get()->IsKeyHeld('d'))
			{
				gX += 5;
			}

			m_lastUpdateTick = currentTick;
			Update(deltaUpdateT);
		}

		// Draw
		Draw(deltaLoopT);
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
	m_pInput->Initialise(150);

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

	SDL_Color col;
	col.r = 0;
	col.g = 255;
	col.b = 0;

	m_pGfx->DrawText("Hello World", 300, 200, col);

	SDL_Rect test;
	test.x = 64;
	test.y = 64;
	test.w = 128;
	test.h = 128;

	m_pGfx->DrawTexture(0, test, gX, gY);

	m_pGfx->EndDraw();
}
