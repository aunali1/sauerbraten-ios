#include "main.h"
#include "App.h"
#include <windows.h>

/******************************************************************************
 Defines
******************************************************************************/

//#define C_LANDSCAPE_NO_NECK_HURT_MODE 1

//#define NO_GDI 1 /* Remove the GDI functions */

// Windows class name to register
#define	WINDOW_CLASS _T("AppClass")

#ifdef C_LANDSCAPE_NO_NECK_HURT_MODE

// Width and height of the window
#define WINDOW_WIDTH	480
#define WINDOW_HEIGHT	320

#else
#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#endif


/******************************************************************************
 Global variables
******************************************************************************/

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif

bool g_leftMouseButtonDown = false; //to help emulate how an iphone works

// Variable set in the message handler to finish the demo
bool	g_bDemoDone = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Handles the close message when a user clicks the quit icon of the window
		case WM_CLOSE:
			g_bDemoDone = true;
			PostQuitMessage(0);
			return 1;
			
			case WM_LBUTTONDOWN:
			{
				g_leftMouseButtonDown = true;
				int xPos = GET_X_LPARAM(lParam);
				int yPos = GET_Y_LPARAM(lParam) + GetYOffset();
#ifndef GLES2
				ConvertCoordinatesIfRequired(xPos, yPos);
#endif
				GetMessageManager()->AddGUI(0, MESSAGE_TYPE_GUI_CLICK_START, xPos, yPos);
			break;
			}
			
			case WM_KEYDOWN:

				switch ((int)wParam)
				{
				case 'L': //landscape mode
#ifndef GLES2
#ifndef C_LANDSCAPE_NO_NECK_HURT_MODE
					SetupScreenInfo(480, 320, 3);
#endif
#endif
					break;

				case 'P': //portrait mode
#ifndef GLES2
#ifndef C_LANDSCAPE_NO_NECK_HURT_MODE
					SetupScreenInfo(320, 480, 1);
#endif
#endif
					break;
				}
					//LogMsg("Got key %d", (int)wParam);
				break;
			case WM_LBUTTONUP:
				{
					int xPos = GET_X_LPARAM(lParam);
					int yPos = GET_Y_LPARAM(lParam) + GetYOffset();
#ifndef GLES2
					ConvertCoordinatesIfRequired(xPos, yPos);
#endif
					GetMessageManager()->AddGUI(0, MESSAGE_TYPE_GUI_CLICK_END, xPos, yPos);
					g_leftMouseButtonDown = false;
					break;

				}

			case WM_MOUSEMOVE:
				{
					if (g_leftMouseButtonDown)
					{
						int xPos = GET_X_LPARAM(lParam);
						int yPos = GET_Y_LPARAM(lParam) + GetYOffset();
#ifndef GLES2
						ConvertCoordinatesIfRequired(xPos, yPos);
#endif
						GetMessageManager()->AddGUI(0, MESSAGE_TYPE_GUI_CLICK_MOVE, xPos, yPos);
						break;
					}
				}

			break;
		default:
			break;
	}

	// Calls the default window procedure for messages we did not handle
	return DefWindowProc(hWnd, message, wParam, lParam);
}


bool TestEGLError(HWND hWnd, char* pszLocation)
{
	/*
		eglGetError returns the last error that has happened using egl,
		not the status of the last called function. The user has to
		check after every single egl call or at least once every frame.
	*/
	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS)
	{
		TCHAR pszStr[256];
		_stprintf_s(pszStr, _T("%s failed (%d).\n"), pszLocation, iErr);
		MessageBox(hWnd, pszStr, _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR *lpCmdLine, int nCmdShow)
{
	int				i;

	// Windows variables
	HWND				hWnd	= 0;
	HDC					hDC		= 0;

	// EGL variables
	EGLDisplay			eglDisplay	= 0;
	EGLConfig			eglConfig	= 0;
	EGLSurface			eglSurface	= 0;
	EGLContext			eglContext	= 0;
	NativeWindowType	eglWindow	= 0;
	EGLint				pi32ConfigAttribs[128];

	/*
		Step 0 - Create a NativeWindowType that we can use for OpenGL ES output
	*/
#ifndef NO_GDI
	// Register the windows class
	WNDCLASS sWC;
    sWC.style = CS_HREDRAW | CS_VREDRAW;
	sWC.lpfnWndProc = WndProc;
    sWC.cbClsExtra = 0;
    sWC.cbWndExtra = 0;
    sWC.hInstance = hInstance;
    sWC.hIcon = 0;
    sWC.hCursor = 0;
    sWC.lpszMenuName = 0;
	sWC.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    sWC.lpszClassName = WINDOW_CLASS;
	ATOM registerClass = RegisterClass(&sWC);
	if (!registerClass)
	{
		MessageBox(0, _T("Failed to register the window class"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
	}

	// Create the eglWindow
	RECT	sRect;
	int offsety = 23;
	int offsetX = 3;

	SetRect(&sRect, 0, 0, WINDOW_WIDTH+offsetX, WINDOW_HEIGHT+offsety);
	
	AdjustWindowRectEx(&sRect, WS_CAPTION | WS_SYSMENU, false, 0);
	
	hWnd = CreateWindow( WINDOW_CLASS, _T("RTApp - L for Landscape, P for portrait"), WS_VISIBLE | WS_SYSMENU,
						 0, 0, sRect.right, sRect.bottom, NULL, NULL, hInstance, NULL);
	eglWindow = hWnd;

	// Get the associated device context
	hDC = GetDC(hWnd);
	if (!hDC)
	{
		MessageBox(0, _T("Failed to create the device context"), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		goto cleanup;
	}
#endif
	
	eglDisplay = eglGetDisplay((NativeDisplayType) hDC);

    if(eglDisplay == EGL_NO_DISPLAY)
         eglDisplay = eglGetDisplay((NativeDisplayType) EGL_DEFAULT_DISPLAY);
	
	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
	{
#ifndef NO_GDI
		MessageBox(0, _T("eglInitialize() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
#endif
		goto cleanup;
	}

	i = 0;
	pi32ConfigAttribs[i++] = EGL_RED_SIZE;
	pi32ConfigAttribs[i++] = 5;
	pi32ConfigAttribs[i++] = EGL_GREEN_SIZE;
	pi32ConfigAttribs[i++] = 6;
	pi32ConfigAttribs[i++] = EGL_BLUE_SIZE;
	pi32ConfigAttribs[i++] = 5;
	pi32ConfigAttribs[i++] = EGL_ALPHA_SIZE;
	pi32ConfigAttribs[i++] = 0;
	pi32ConfigAttribs[i++] = EGL_SURFACE_TYPE;
	pi32ConfigAttribs[i++] = EGL_WINDOW_BIT;
	pi32ConfigAttribs[i++] = EGL_NONE;

	int iConfigs;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
#ifndef NO_GDI
		MessageBox(0, _T("eglChooseConfig() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
#endif
		goto cleanup;
	}

	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);

    if(eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}

	if (!TestEGLError(hWnd, "eglCreateWindowSurface"))
	{
		goto cleanup;
	}

	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, NULL);
	if (!TestEGLError(hWnd, "eglCreateContext"))
	{
		goto cleanup;
	}

	
	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	if (!TestEGLError(hWnd, "eglMakeCurrent"))
	{
		goto cleanup;
	}
#ifndef GLES2
	SetupScreenInfo(WINDOW_WIDTH, WINDOW_HEIGHT, ORIENTATION_PORTRAIT);
#endif
	if (!g_App.Init())
	{
		assert(!"Unable to init");
		MessageBox(NULL, "Error initializing the game.  Did you unzip everything right?", "Unable to load stuff", NULL);
		goto cleanup;
	}

	
	//our main loop

	while(1)
	{
		if (g_bDemoDone) break;

		g_App.Update();
		g_App.Draw();

		eglSwapBuffers(eglDisplay, eglSurface);
		if (!TestEGLError(hWnd, "eglSwapBuffers"))
		{
			goto cleanup;
		}
		// Managing the window messages
		MSG msg;
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}
	}

cleanup:
	eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(eglDisplay);

	// Release the device context
	if (hDC) ReleaseDC(hWnd, hDC);

	// Destroy the eglWindow
	if (hWnd) DestroyWindow(hWnd);

	return 0;
}
