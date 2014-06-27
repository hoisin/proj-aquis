#include <sstream>
#include "CApp.h"

// test
#include "CCameraFPS.h"

float g_movAmt = 0.2f;
float g_rotAmt = 0.3f;


CApp::CApp() : m_pGfx(NULL), m_pResourceMgr(NULL), m_bAppActive(true), m_bRun(true)
{
}


CApp::~CApp()
{
}


//------------------------------------------------------------------
//
//	InitialiseApp(..)
//
//	Params:
//	appName		-	Label of class/process
//
//	Initialises application with specified unique identifier.
//	Prevents running of multiple instances
//
//------------------------------------------------------------------
bool CApp::InitialiseApp(const std::string &appName)
{
	m_sAppName = appName;
	m_hMutex = CreateMutex(NULL, 1, m_sAppName.c_str());

	// Don't allow to run multiple instances
	if(GetLastError() == ERROR_ALREADY_EXISTS) {
		MessageBox(NULL, "Application already running!", "Multiple Instances Found", MB_ICONINFORMATION | MB_OK);
		return false;
	}

	return true;
}


//------------------------------------------------------------------
//
//	RegisterAppClass(..)
//
//	Params:
//	hAppInstance		-	Label of class/process
//
//	Initialises application with specified unique identifier.
//	Prevents running of multiple instances
//
//------------------------------------------------------------------
void CApp::RegisterAppClass(HINSTANCE hAppInstance)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// Memory Access Violation error
	/*wcex.hIcon = LoadIcon(m_hInstance, IDI_WINLOGO);
	wcex.hIconSm = LoadIcon(m_hInstance, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(m_hInstance, IDC_ARROW);*/

	wcex.hInstance = m_hInstance;

	wcex.lpfnWndProc = MsgHandlerMain;
	wcex.lpszClassName = m_sAppName.c_str();

	wcex.lpszMenuName = NULL;

	// Register Class
	if(!RegisterClassEx(&wcex)) {
		throw std::runtime_error("Failed to register window");
	}
}


//------------------------------------------------------------------
//
//	CreateAppWindow(..)
//
//	Params:
//	windowTitle		-	Title of the window
//	windowWidth		-	Width of window
//	windowHeight	-	Height of window
//
//	Creates the window with the specified string as title
//
//------------------------------------------------------------------
bool CApp::CreateAppWindow(const std::string &windowTitle, UINT windowWidth, UINT windowHeight)
{
	m_windowName = windowTitle;

	// Create and determine window size
	RECT windowSize;
	windowSize.left = 0;
	windowSize.right = windowWidth;
	windowSize.top = 0;
	windowSize.bottom = windowHeight;

	AdjustWindowRectEx(&windowSize, WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX  |
								WS_CLIPCHILDREN | WS_CLIPSIBLINGS, false, WS_EX_OVERLAPPEDWINDOW); 

	m_hWnd = CreateWindowEx(0, m_sAppName.c_str(), windowTitle.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		0, 0, (windowSize.right - windowSize.left), (windowSize.bottom - windowSize.top), NULL,
		NULL, m_hInstance, NULL);

	// Recalculate window to get client area to correct size
	RECT rClient, rWindow;
	POINT ptDiff;
	GetClientRect(m_hWnd, &rClient);
	GetWindowRect(m_hWnd, &rWindow);
	ptDiff.x = (rWindow.right - rWindow.left) - rClient.right;
	ptDiff.y = (rWindow.bottom - rWindow.top) - rClient.bottom;
	MoveWindow(m_hWnd,rWindow.left, rWindow.top, windowWidth + ptDiff.x, windowHeight + ptDiff.y, TRUE);

	if(m_hWnd == 0) {
		throw std::runtime_error("Failed to create window");
		return FALSE;
	}

	// Store a pointer to this object in the window, otherwise we can't grab it using
	// GetWindowLongPtr(..) in the callback for messages
	SetWindowLongPtr( m_hWnd, GWLP_USERDATA, (long)this );

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// Run initialisation, if fail quit the application
	if(!OnInitialise(windowWidth, windowHeight))
		m_bRun = false;

	return true;
}


//------------------------------------------------------------------
//
//	AppRun(..)
//
//	Main Loop 
//
//------------------------------------------------------------------
void CApp::AppRun()
{
	MSG msg;
	long startTime = timeGetTime();

	m_timer.Reset();
	m_timer.Start();

	while(m_bRun)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // Otherwise send message to appropriate window
			DispatchMessage(&msg);	
		}
		else 
		{
			// If app is currently active
			if(m_bAppActive)
			{
				// Only want to process the timer when our app is the active window (may change)
				m_timer.Tick();

				OnUpdate( 0.001f * ( timeGetTime() - startTime )  );

				OnDraw();

				CalculateFrameStats();
			}
			else 
			{
				Sleep(200); // Do not consume processor power if application isn't active
			}
		}

	}
}


//------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Cleans up 
//
//------------------------------------------------------------------
void CApp::ShutDown()
{
	if(m_pGfx) {
		delete m_pGfx;
		m_pGfx = NULL;
	}

	if(m_pResourceMgr) { 
		delete m_pResourceMgr;
		m_pResourceMgr = NULL;
	}

	DestroyWindow(m_hWnd);
	UnregisterClass(m_sAppName.c_str(), m_hInstance);
	ReleaseMutex(m_hMutex);
}


//------------------------------------------------------------------
//
//	GetInstance(..)
//
//	Returns instance
//
//------------------------------------------------------------------
HINSTANCE CApp::GetInstance()
{
	return m_hInstance;
}


//------------------------------------------------------------------
//
//	GetInstance(..)
//
//	Windows event callback method.
//	Don't handles events here, do it in OnEvent(...)
//
//------------------------------------------------------------------
LRESULT CALLBACK CApp::MsgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if(hWnd == NULL)
		throw std::runtime_error("Invalid window handle");

	// Retrieve a pointer to the D3D9Application object
	CApp* app = (CApp*)GetWindowLongPtr( hWnd, GWLP_USERDATA );

	if ( app == NULL )
		return DefWindowProc( hWnd, uiMsg, wParam, lParam );

	// Handle required messages
	switch ( uiMsg )
	{
	case WM_CLOSE:
		ShowWindow( app->m_hWnd, SW_HIDE );
		app->m_bRun = false;
		break;
	}

	if(app->OnEvent(hWnd, uiMsg,wParam,lParam) == FALSE)
		return DefWindowProc( hWnd, uiMsg, wParam, lParam );

	return 0;
}


//------------------------------------------------------------------
//
//	OnInitialise(..)
//
//	Do App initialisation here
//
//------------------------------------------------------------------
bool CApp::OnInitialise(UINT windowWidth, UINT windowHeight)
{
	if(!m_pResourceMgr) { 
		m_pResourceMgr = new CResourceManager;
	}

	if(!m_pResourceMgr->Initialise())
		return false;

	if(!m_pGfx) {
		m_pGfx = new CGraphics;
	}

	if(!m_pGfx->Initialise(m_hInstance, &m_hWnd, 3, 1, m_pResourceMgr, windowWidth, windowHeight, MsgHandlerMain))
		return false;

	m_pGfx->LoadScene();

	return true;
}


//------------------------------------------------------------------
//
//	OnDraw(..)
//
//	Do Drawing here
//
//------------------------------------------------------------------
void CApp::OnDraw()
{
	m_pGfx->RenderScene();
}


//------------------------------------------------------------------
//
//	OnUpdate(..)
//
//	fTime	-	Time elapsed since last update
//
//	Do updating here
//
//------------------------------------------------------------------
void CApp::OnUpdate(float fTime)
{
}


//------------------------------------------------------------------
//
//	OnEvent(..)
//
//	Handle events here
//
//------------------------------------------------------------------
bool CApp::OnEvent(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	//mouse variables for allowing interaction with camera
	POINT temp;
	::GetCursorPos(&temp);
	static float lastX = (float)temp.x;
	static float lastY = (float)temp.y;
	static float x = (float)temp.x;
	static float y = (float)temp.y;

	switch ( msg )
	{
	case WM_PAINT:
		BeginPaint(wnd, &ps);					
		EndPaint(wnd, &ps);
		break;

	case WM_ACTIVATE:
		{
			switch(LOWORD(wParam))
			{
			case WA_ACTIVE:
			case WA_CLICKACTIVE:
				m_bAppActive = true;
				break;
			case WA_INACTIVE:
				m_bAppActive = false;
				break;
			}
			break;
		}

	case WM_SIZE:
		break;

	case WM_LBUTTONDOWN:
		SetCapture(m_hWnd);
		break;

	case WM_LBUTTONUP:
		::ReleaseCapture();
		break;

	case WM_MOUSEWHEEL:
		break;

	case WM_MOUSEMOVE:
		::GetCursorPos(&temp);
		x = (float)temp.x - lastX;
		y = (float)temp.y - lastY; 
		if(wParam && MK_LBUTTON)
		{
			CCameraFPS* cam = (CCameraFPS*)m_pGfx->GetCamera();
			cam->RotateYaw(x*g_rotAmt);
			cam->RotatePitch(y*g_rotAmt);
	/*		g_firstPersonCam.RotateLeftRight(x*g_rotationAmt);
			g_firstPersonCam.RotateUpDown(y*g_rotationAmt);*/
		}

		lastX = (float)temp.x;
		lastY = (float)temp.y;
		break;

	case WM_KEYDOWN:
		{
			CCameraFPS* cam = (CCameraFPS*)m_pGfx->GetCamera();
			switch(wParam)
			{
			case 'W':
				cam->MoveForward(g_movAmt);
				break;

			case 'S':
				cam->MoveBack(g_movAmt);
				break;

			case 'A':
				cam->StrafeLeft(g_movAmt);
				break;

			case 'D':
				cam->StrafeRight(g_movAmt);
				break;

			case 'N':
				m_pGfx->SetWireFrame(true);
				break;

			case 'M':
				m_pGfx->SetWireFrame(false);
				break;

			default:
				break;
			}
		}
		break;

	default:
		return false;
	}

	return true;
}


//------------------------------------------------------------------
//
//	CalculateFrameStats(..)
//
//	Calculates frames per second
//
//------------------------------------------------------------------
void CApp::CalculateFrameStats()
{
	static int frameCount = 0;
	static double timeElapsed = 0.0f;

	// Increment counter and elapsed time
	frameCount++;
	timeElapsed += m_timer.DeltaTime();

	// If exceed over a second
	if((timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCount;
		float mspf = 1000.0f / fps;

		// Write stats on the title of the window
		std::ostringstream outs;
		outs.precision(6);
		outs << m_windowName << "    " << "FPS: " << fps << "    " << "Frame Time: " << mspf << " (ms)";

		SetWindowText(m_hWnd, outs.str().c_str());

		// Reset vars
		frameCount = 0;
		timeElapsed = 0;
	}
}
