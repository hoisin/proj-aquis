#include "C3DApp.h"
#include "CD3DBase.h"

C3DApp::C3DApp(void) : _hwnd(NULL), _bRun(false), m_pRenderer(NULL)
{
}


C3DApp::~C3DApp(void)
{
	if(m_pRenderer)
		delete m_pRenderer;

	m_pRenderer = 0;

	DestroyWindow(_hwnd);
	_hwnd = 0;
}


bool C3DApp::Initialise(LPCWSTR windowName, UINT windowWidth, UINT windowHeight)
{
	//Create class
	WNDCLASSEX winClass;
	memset(&winClass, 0, sizeof(WNDCLASSEX));
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WndProc;
	winClass.hInstance = 0;
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszClassName = L"3DApp";
	winClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	m_windowName = windowName;

	//Register class
	if(!RegisterClassEx(&winClass))
	{
		throw std::runtime_error("Failed to register window");
		return false;
	}

	//Create and determine window size
	RECT windowSize;
	windowSize.left = 0;
	windowSize.right = windowWidth;
	windowSize.top = 0;
	windowSize.bottom = windowHeight;

	AdjustWindowRectEx(&windowSize, WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX  |
								WS_CLIPCHILDREN | WS_CLIPSIBLINGS, false, WS_EX_OVERLAPPEDWINDOW); 

	//Create window
	_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"3DApp", windowName, 
		WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS , 100, 100, 
		(windowSize.right - windowSize.left), (windowSize.bottom - windowSize.top), 0, 0, 0, 0);

	//Recalculate window to get client area to correct size
	RECT rClient, rWindow;
	POINT ptDiff;
	GetClientRect(_hwnd, &rClient);
	GetWindowRect(_hwnd, &rWindow);
	ptDiff.x = (rWindow.right - rWindow.left) - rClient.right;
	ptDiff.y = (rWindow.bottom - rWindow.top) - rClient.bottom;
	MoveWindow(_hwnd,rWindow.left, rWindow.top, windowWidth + ptDiff.x, windowHeight + ptDiff.y, TRUE);

	if(_hwnd == 0)
	{
		throw std::runtime_error("Failed to create window");
		return false;
	}

	// Store a pointer to this object in the window
	SetWindowLongPtr( _hwnd, GWLP_USERDATA, (long)this );

	// Create renderer
	m_pRenderer = new CGraphics;

	m_pRenderer->VInitialise(_hwnd, windowWidth, windowHeight, FALSE, FALSE, 100, 1);

	return true;
}


void C3DApp::Run(void)
{
	//show window
	ShowWindow(_hwnd,SW_SHOW);
	UpdateWindow(_hwnd);

	MSG msg;
	_bRun = true;

	long startTime = timeGetTime();

	m_timer.Start();

	//Main app loop
	while(_bRun)
	{
		m_timer.Tick();

		// Handle all pending events
		while ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) != 0 )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	
		//Update
		OnUpdate(0.001f * ( timeGetTime() - startTime ) );

		//Draw
		OnDraw();

		CalculateFrameStats();
	}

	m_timer.Stop();
}


void C3DApp::OnDraw(void)
{
	//Draw something
	m_pRenderer->VRenderScene();
}


void C3DApp::OnUpdate(float fTime)
{
	//Do some update here
}


void C3DApp::CalculateFrameStats(void)
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if((m_timer.Time() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCount;
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << m_windowName << L"    " << L"FPS: " << fps << L"    " << L"Frame Time: " << mspf << L" (ms)";

		SetWindowText(_hwnd, outs.str().c_str());

		frameCount = 0;
		timeElapsed += m_timer.Time();
	}
}


bool C3DApp::OnEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
	//mouse variables for allowing interaction with camera
	POINT temp;
	::GetCursorPos(&temp);
	static float lastX = (float)temp.x;
	static float lastY = (float)temp.y;
	static float x = (float)temp.x;
	static float y = (float)temp.y;
	float zDelta = 0;

	switch ( msg )
	{
	case WM_SIZE:
		//Handle resizing
		break;

	case WM_LBUTTONDOWN:
		SetCapture(_hwnd);
		break;

	case WM_LBUTTONUP:
		::ReleaseCapture();
		break;

	case WM_MOUSEMOVE:
		::GetCursorPos(&temp);
		x = (float)temp.x - lastX;
		y = (float)temp.y - lastY; 

		if(wParam && MK_LBUTTON)
		{
			((CFPCamera*)(m_pRenderer->GetCamera()))->RotatePitch(y*0.5);
			((CFPCamera*)(m_pRenderer->GetCamera()))->RotateYaw(x*0.5);
			//g_firstPersonCam.RotateLeftRight(x*g_rotationAmt);
			//g_firstPersonCam.RotateUpDown(y*g_rotationAmt);
		}

		lastX = (float)temp.x;
		lastY = (float)temp.y;

		

		//std::cout << x << " " << y << std::endl;
		break;

	case WM_KEYDOWN:
		{
			// Test by outputting messages into console
			switch(wParam)
			{
			case 'W':
				((CFPCamera*)(m_pRenderer->GetCamera()))->MoveForward(1);
				break;

			case 'S':
				((CFPCamera*)(m_pRenderer->GetCamera()))->MoveBackward(1);
				break;

			case 'A':
				((CFPCamera*)(m_pRenderer->GetCamera()))->StrafeLeft(1);
				break;

			case 'D':
				((CFPCamera*)(m_pRenderer->GetCamera()))->StrafeRight(1);
				break;

			case 'N':
				m_pRenderer->SetWireFrameMode(true);
				break;

			case 'M':
				m_pRenderer->SetWireFrameMode(false);
				break;

			case VK_ESCAPE:
				_bRun = false;
				break;

			default:
				break;
			}
		}

	default:
		return false;
	}

	return true;
}


LRESULT WINAPI C3DApp::WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if(wnd == NULL)
		throw std::runtime_error("Invalid window handle");

	// Retrieve a pointer to the D3D9Application object
	C3DApp* app = (C3DApp*)GetWindowLongPtr( wnd, GWLP_USERDATA );

	if ( app == NULL )
		return DefWindowProc( wnd, msg, wParam, lParam );

	// Handle required messages
	switch ( msg )
	{
	case WM_CLOSE:
		ShowWindow( app->_hwnd, SW_HIDE );
		app->_bRun = false;
		break;
	}

	if(app->OnEvent(msg,wParam,lParam) == false)
		return DefWindowProc( wnd, msg, wParam, lParam );

	return 0;
}