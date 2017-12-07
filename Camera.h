#pragma once
#include "GameObject.h"
#include <dinput.h>
#include <string>

using namespace DirectX;

class Camera : public GameObject
{
public:
	Camera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance);
	void updateCamera(); 
	void SetViewMatrix(XMMATRIX& viewMatrix) { viewMatrix = m_viewMatrix; }
	XMMATRIX getViewMatrix() { return m_viewMatrix; }
	XMMATRIX getProjMatrix() { return m_camProjection; }
	void goLeft() { m_posx--; };
	void goRight() { m_posx++; };
	void goUp() { m_posy++; };
	void goDown() { m_posy--; };
	void goForward() { m_posz++; };
	void goBackwards() { m_posz--; };

	XMMATRIX m_viewMatrix, m_camProjection = XMMatrixIdentity();
	virtual void draw(DrawData* _DD) override;
private:
	
	XMFLOAT3 m_up, m_lookAt;
	XMVECTOR upVector, lookAtVector;
	//parameters for setting up a camera
	float m_fieldOfView;
	float m_aspectRatio;
	float m_nearPlaneDistance;
	float m_farPlaneDistance;
	struct cbPerObject
	{
		XMMATRIX  WVP;
	};

	cbPerObject cbPerObj;
};

