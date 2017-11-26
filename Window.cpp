#include "Window.h"
#include "AntTweakBar.h"

Window::Window(int width, int height)
{
	//Set window Params
	WNDCLASS wc = { 0 };
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WinProc;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = "DX11 Advanced Tech";
	RegisterClass(&wc);
	//Create window
	m_handle = CreateWindow("DX11 Advanced Tech", "Hair and Fur",
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		100, 100, width, height,
		nullptr, nullptr, nullptr, nullptr);
}

LRESULT CALLBACK WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY ||
		msg == WM_CLOSE) {
		PostQuitMessage(0);
		return 0;
	}
	if (TwEventWin(handle, msg, wparam, lparam)) // send event message to AntTweakBar
		return 0; // event has been handled by AntTweakBar
				  // else process the event message
				  // ...
	return DefWindowProc(handle, msg, wparam, lparam);
}
