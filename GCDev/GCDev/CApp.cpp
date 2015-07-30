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
	m_pGfx->DrawTexture();
}