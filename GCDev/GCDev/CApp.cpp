#include "CApp.h"

#include "SDL.h"

#include "CGfx.h"


CApp::CApp() : m_bRun(false), m_pGfx(nullptr), m_lastTick(0), m_tick(0)
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
		unsigned int deltaT = (m_lastTick - currentTick);

		if (deltaT > m_tick)
		{
			m_lastTick = currentTick;
			Update(deltaT);
		}

		Draw(deltaT);
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
	m_pGfx->BeginDraw();

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

	m_pGfx->DrawTexture(0, test, 0, 0);

	m_pGfx->EndDraw();
}
