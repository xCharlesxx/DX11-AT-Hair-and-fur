#include "gameobject.h"


GameObject::GameObject()
{
	//set the Gameobject to the origin with no rotation and unit scaling 
	m_pos = XMVectorSet(0, 0, 0, 0);
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_posx = 0.0f;
	m_posy = 0.0f;
	m_posz = 0.0f;
	m_scale = XMVectorSet(1, 1, 1, 0);
	m_worldMatrix = XMMatrixIdentity(); 
	m_fudge = XMMatrixIdentity();
	//Matrix::CreateRotationY(1.6);
}

GameObject::~GameObject()
{

}

void GameObject::draw(DrawData* _DD)
{
	
}

void GameObject::tick()
{
	//build up the world matrix depending on the new position of the GameObject
	m_pos = XMVectorSet(m_posx, m_posy, m_posz, 0);

	XMMATRIX  scaleMat = XMMatrixScalingFromVector(m_scale);

	//Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float pitch = m_yaw * 0.0174532925f;
	float yaw = m_pitch * 0.0174532925f;
	float roll = m_roll * 0.0174532925f;

	////Create the rotation matrix from the yaw, pitch, and roll values.
	m_rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	XMMATRIX transMat = XMMatrixTranslationFromVector(m_pos);

	m_worldMatrix = scaleMat * m_rotationMatrix * transMat;

	//zero acceleration ready for the next time round
	m_acc = XMVectorSet(0, 0, 0, 0);
}
