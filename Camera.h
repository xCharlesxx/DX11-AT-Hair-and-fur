#pragma once
#include "DirectXMath.h"
#include <dinput.h>
#include <string>
using namespace DirectX;

class Camera
{
public:
	Camera(); 
	void updateCamera(); 
	void SetViewMatrix(XMMATRIX& viewMatrix) { viewMatrix = m_viewMatrix; }
	XMMATRIX getViewMatrix() { return m_viewMatrix; }

	void goLeft() { camPosX--; };
	void goRight() { camPosX++; };
	void goUp() { camPosY--; };
	void goDown() { camPosY++; };
	void goForward() { camPosZ--; };
	void goBackwards() { camPosZ++; };
	float* getCamX() { return &camPosX; };
	float* getCamY() { return &camPosY; };
	float* getCamZ() { return &camPosZ; };
	void setPos(float x, float y, float z) { camPosX = x; camPosY = y; camPosZ = z; }
	void setRot(float x, float y, float z) { camYaw = x; camPitch = y; camRoll = z; }
	
	XMFLOAT3 getPos() { return XMFLOAT3(camPosX, camPosY, camPosZ); }
	XMFLOAT3 getRot() { return XMFLOAT3(camYaw, camPitch, camRoll); }
	std::string getPosStr() { return std::to_string(camPosX) + ", " + std::to_string(camPosY) + ", " + std::to_string(camPosZ); }
	std::string getRotStr() { return std::to_string(camYaw) + ", " + std::to_string(camPitch) + ", " + std::to_string(camRoll); }
private:
	float camPosX = 0.0f, camPosY = 0.0f, camPosZ = 5.0f;
	float camYaw = 0.0f, camPitch = 0.0f, camRoll = 0.0f; 
	XMMATRIX m_viewMatrix, rotationMatrix, m_world, m_camProjection;
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
};

