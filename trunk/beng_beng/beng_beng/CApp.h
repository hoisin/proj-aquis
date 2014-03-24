//--------------------------------------------------------------------------
//
//	20/03/2014
//
//	Class managing application framework code (no console window)
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CAPP_H__
#define __CAPP_H__

#include <string>
#include <Windows.h>
#include "CGraphics.h"
#include "COpenGL.h"

#include "CTimer.h"

class CApp
{
public:
	CApp();
	~CApp();

	bool InitialiseApp(const std::string &appName);
	void RegisterAppClass(HINSTANCE hAppInstance);
	bool CreateAppWindow(const std::string &windowTitle,
		UINT windowWidth, UINT windowHeight);
	
	void AppRun();
	void ShutDown();

	HINSTANCE GetInstance();

	static LRESULT CALLBACK MsgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

private:
	bool OnInitialise();

	void OnDraw();

	void OnUpdate(float fTime);
	
	bool OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void CalculateFrameStats();

public:
	HWND m_hWnd;

private:
	HINSTANCE m_hInstance;
	std::string m_sAppName, m_windowName;
	HANDLE m_hMutex;

	CGraphics *m_pGfx;
	COpenGL *m_pOpenGL;

	CTimer m_timer;	
	bool m_bAppActive, m_bRun;
};



#endif