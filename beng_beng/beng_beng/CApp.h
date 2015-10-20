//--------------------------------------------------------------------------
//
//	20/03/2014
//
//	Class managing application framework code (no console window)
//
//	Author: Matt © 2014
//
//--------------------------------------------------------------------------

#ifndef __CAPP_H__
#define __CAPP_H__

#include <string>
#include <Windows.h>
#include "CGraphics.h"

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
	bool OnInitialise(UINT windowWidth, UINT windowHeight);

	void OnDraw();

	void OnUpdate(float fTime);
	
	bool OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void CalculateFrameStats();

public:
	HWND m_hWnd;

private:
	HINSTANCE m_hInstance;
	HANDLE m_hMutex;

	std::string m_sAppName;
	std::string m_windowName;

	CGraphics *m_pGfx;

	CTimer m_timer;	
	bool m_bAppActive;
	bool m_bRun;

	// Testing
	std::string myGraphicActorID;
	glm::vec3	myActorPos;
};



#endif