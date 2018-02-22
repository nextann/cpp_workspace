#include <Windows.h>
/*
#include "stdafx.h"
#include <tchar.h>
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//***(2) main function

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS WndClass; //windows class structure
	HWND hwnd; //widnow handle
	MSG msg; //message sructure

	//***(3) windows class initialization and reistration

	WndClass.style = CS_HREDRAW | CS_VREDRAW; //class style
	WndClass.lpfnWndProc = WndProc; //window procedure
	WndClass.cbClsExtra = 0; //window class data segment
	WndClass.cbWndExtra = 0; //window's data segment
	WndClass.hInstance = hInstance; //instance handle
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //icon handle
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //cursor handle
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //background brush handle(white background)
	WndClass.lpszMenuName = NULL; //menu name
	WndClass.lpszClassName = TEXT("MouseClass"); //window class name

	if (!RegisterClass(&WndClass)) //window class register
		return 1;

	//***(4) window creation

	hwnd = CreateWindow(		//window creation API function
		TEXT("MouseClass"),		//registered window class name
		TEXT("MouseSDK"),		//printed text in titlebar
		WS_OVERLAPPEDWINDOW,	//window style
		CW_USEDEFAULT,			//window top-left x-coordinate
		CW_USEDEFAULT,			//window top-left y-coordinate
		CW_USEDEFAULT,			//window width
		CW_USEDEFAULT,			//window height
		NULL,					//parent window handle
		NULL,					//menu or child window handle
		hInstance,				//application instance handle
		NULL					//window creation data address
	);
	ShowWindow(hwnd, nCmdShow);	//show 프레인 window

	//***(5) message loop

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//***(6) window procedure

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		//device context
	PAINTSTRUCT ps;	//paint structure
	TCHAR str1[200] = TEXT("마우스를 클릭하세요");
	TCHAR str2[200] = TEXT("오륵쪽 마우스/왼쪽 마우스를 클릭하시면 메시지 상자가 나타납니다.");

	switch (message) //message recieved from kernel handled by switch
	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("왼쪽 마우스를 클릭하셨습니다."), TEXT("왼쪽 마우스 클릭!"), MB_OK);
		return 0;

	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("오른쪽 마우스를 클릭하셨습니다."), TEXT("오른쪽 마우스 클릭!"), MB_OK);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, str1, lstrlen(str1));
		TextOut(hdc, 100, 200, str2, lstrlen(str2));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}