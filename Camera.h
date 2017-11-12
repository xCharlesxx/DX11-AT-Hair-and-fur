#pragma once
#include "DirectXMath.h"
#include <dinput.h>

using namespace DirectX;

class Camera
{
public:
	Camera(); 
	void updateCamera(); 
	void GetViewMatrix(XMMATRIX& viewMatrix);
	void setPos(float x, float y, float z) { camPosX = x; camPosY = y; camPosZ = z; }
	void getRot(float x, float y, float z) { camYaw = x; camPitch = y; camRoll = z; }
	XMFLOAT3 getPos() { return XMFLOAT3(camPosX, camPosY, camPosZ); }
	XMFLOAT3 getRot() { return XMFLOAT3(camYaw, camPitch, camRoll); }
private:
	float camPosX = 0.0f, camPosY = 0.0f, camPosZ = 0.0f;
	float camYaw = 0.0f, camPitch = 0.0f, camRoll = 0.0f; 
	XMMATRIX m_viewMatrix;
};

