/*
	Date: 24/08/2012
	Class for handling the window (win32). Contains our main execution loop

	Might create an interface for it, but seems overkill/unnecessary for our application
*/

#pragma once
#ifndef __C3DAPP_H__
#define __C3DAPP_H__

#include <windows.h>
#include <sstream>
#include <iostream>

#include "CGraphics.h"
#include "CTimer.h"

class C3DApp
{
private:
	CGraphics* m_pRenderer;		//Our renderer
	CTimer m_timer;
	std::wstring m_windowName;

	HWND _hwnd;					//Handler to our window
	bool _bRun;

public:
	C3DApp(void);
	~C3DApp(void);

	//Performs window creation and other initialisation
	BOOL Initialise(LPCWSTR windowName, UINT windowWidth, UINT windowHeight);

	//Main loop
	void Run(void);

private:
	
	//Do all drawing here
	void OnDraw(void);

	//Do all updating here
	void OnUpdate(float fTime);

	//An event that needs capturing in here
	BOOL OnEvent(UINT msg, WPARAM wParam, LPARAM lParam);

	void CalculateFrameStats(void);

private:
	static LRESULT WINAPI WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif