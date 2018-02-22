//mouse moving program

//******(1) header file

#include <Windows.h>

/*
#include "stdafx.h"
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//***(2) main function

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS WndClass;	//window class structrue
	HWND hwnd;			//window handle
	MSG msg;			//message strucuture

	//***(3)windows class initialization and registration

	WndClass.style = CS_HREDRAW | CS_VREDRAW;		//class style
	WndClass.lpfnWndProc = WndProc;					//window procedure
	WndClass.cbClsExtra = 0;						//window class data region
	WndClass.cbWndExtra = 0;						//window's data region
	WndClass.hInstance = hInstance;					//instance handle
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//icon handle
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//cursor handle
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	//background brush handle (light gray background)
	WndClass.lpszMenuName = NULL;				//menu name
	WndClass.lpszClassName = TEXT("MClass");	//window class name

	if (!RegisterClass(&WndClass))				//window class register
		return 1;

	//***(4)create window

	hwnd = CreateWindow(				//create window API function
		TEXT("MClass"),					//registered window class name
		TEXT("마우스로 그림 그리기"),	//printed text on title bar
		WS_OVERLAPPEDWINDOW,			//window style
		CW_USEDEFAULT,					//window top-left x-coordinate
		CW_USEDEFAULT,					//window top-left y-coordinate
		CW_USEDEFAULT,					//window width
		CW_USEDEFAULT,					//window height
		NULL,							//parent window handle
		NULL,							//menu or child window handle
		hInstance,						//application instance handle
		NULL							//created window data address
	);
	ShowWindow(hwnd, nCmdShow);			//show window within display

	//***(5)message loop

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//***(6)window procedure

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT MousePos; //variable to store mouse x,y coordinate 

	static BOOL bDrawing = FALSE;

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		MousePos.x = LOWORD(lParam);
		MousePos.y = HIWORD(lParam);
		bDrawing = TRUE;
		SetCapture(hWnd);
		return 0;
	case WM_MOUSEMOVE:
		if (bDrawing == TRUE) {
			hdc = GetDC(hWnd);
			MoveToEx(hdc, MousePos.x, MousePos.y, NULL);
			MousePos.x = LOWORD(lParam);
			MousePos.y = HIWORD(lParam);
			LineTo(hdc, MousePos.x, MousePos.y);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		bDrawing = FALSE;
		ReleaseCapture();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}