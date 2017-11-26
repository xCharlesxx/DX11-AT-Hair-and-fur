#pragma once
#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
#include "Camera.h"
class Input
{
public:
	Input(Camera* cam);
	void InitInput(HINSTANCE hInstance, HWND hwnd);
	void DetectInput();
private:
	bool m_keys[256] = { false };
	bool m_prevKeys[256] = { false };
	Camera* m_camera;
	IDirectInput8 * m_directInput = 0;
	IDirectInputDevice8* m_keyboard = 0;
};