#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS WndClass;
	HWND hwnd;
	MSG msg;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hinstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = TEXT("MouseWheelClass");

	if (!RegisterClass(&WndClass))
		return 1;

	hwnd = CreateWindow(
		TEXT("MouseWheelClass"),
		TEXT("Mouse Example"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinstance,
		NULL
		);
	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[200] = TEXT("마우스 휠을 움직여 보세요");
	//TCHAR str2[200] = TEXT("")

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_MOUSEWHEEL:
		MessageBox(hwnd, TEXT("마우스 휠을 움직이셨습니다."), TEXT("마우스 휠 움직임!"), MB_OK);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

