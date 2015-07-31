#include "CApp.h"

#include "SDL.h"

#include "CGfx.h"


CApp::CApp() : m_bRun(false), m_pGfx(nullptr)
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
	Intitialise();

	SDL_Event sdlEvent;

	while (m_bRun) {

		// Handle events on queue
		while (SDL_PollEvent(&sdlEvent) != 0) {

			Update();

			Draw();

			// User quits
			if (sdlEvent.type == SDL_QUIT)
				m_bRun = false;
		}
	}

	SDL_Quit();
}


//---------------------------------------------------------------------------
//
//	Initialise()
//
//	Descrition:
//	Initialises application
//
//---------------------------------------------------------------------------
bool CApp::Intitialise()
{
	m_bRun = true;

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
void CApp::Update()
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
void CApp::Draw()
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
