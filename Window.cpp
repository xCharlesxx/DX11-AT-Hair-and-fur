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
	return ApplicationHandle->MessageHandler(handle, msg, wparam, lparam);
}

LRESULT CALLBACK Window::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{

	if (TwEventWin(hwnd, umsg, wparam, lparam)) // send event message to AntTweakBar
		return 0; // event has been handled by AntTweakBar
				  // else process the event message
				  // ...
	switch (umsg)
	{
			//Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			//If a key is pressed send it to the input object so it can record that state.
			m_input.KeyDown((unsigned int)wparam);
			return 0;
		}

		//Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			//If a key is released then send it to the input object so it can unset the state for that key.
			m_input.KeyUp((unsigned int)wparam);
			return 0;
		}
		//Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

HWND Window::getHandle() 
{
	return m_handle;
}
