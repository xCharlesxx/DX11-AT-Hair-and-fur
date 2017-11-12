#pragma once
#include "DirectXMath.h"

class Camera
{
public:
	Camera(); 
	void UpdateCamera(); 

private:


	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;
};

