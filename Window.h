#pragma once

#include <Windows.h>
#include "Input.h"

class Window 
{
public:
	Window(int width, int height);
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	HWND getHandle();
	//Input getInput() { return input; };
private:
	HWND m_handle;
	Input m_input; 

};
static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
static Window* ApplicationHandle = 0;