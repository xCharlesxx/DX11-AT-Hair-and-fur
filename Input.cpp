#include "Input.h"

Input::Input(Camera * cam)
{
	m_camera = cam;
}

void Input::InitInput(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void Input::DetectInput()
{
	DIMOUSESTATE mouseCurrState;
	BYTE keyboardState[256] = { false };
	m_keyboard->Acquire();
	m_keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (keyboardState[DIK_W] & 0x80 || keyboardState[DIK_UP] & 0x80)
		m_camera->goUp();

	if (keyboardState[DIK_A] & 0x80 || keyboardState[DIK_LEFT] & 0x80)
		m_camera->goLeft();

	if (keyboardState[DIK_S] & 0x80 || keyboardState[DIK_DOWN] & 0x80)
		m_camera->goDown();

	if (keyboardState[DIK_D] & 0x80 || keyboardState[DIK_RIGHT] & 0x80)
		m_camera->goRight();

	if (keyboardState[DIK_F] & 0x80)
		m_camera->goForward();

	if (keyboardState[DIK_B] & 0x80)
		m_camera->goBackwards();

}