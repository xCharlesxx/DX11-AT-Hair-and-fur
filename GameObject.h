#pragma once
#include "DirectXMath.h"

using namespace DirectX;
//using namespace DirectX::SimpleMath;

class Camera;
struct ID3D11DeviceContext;
struct DrawData;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void draw(DrawData* _DD) = 0;

	//getters
	XMVECTOR		getPos() { return m_pos; }
	XMVECTOR		getScale() { return m_scale; }
	float*       getXPos() { return &m_posx; }
	float*       getYPos() { return &m_posy; }
	float*       getZPos() { return &m_posz; }
	float		getPitch() { return m_pitch; }
	float		getYaw() { return m_yaw; }
	float		getRoll() { return m_roll; }
	bool		isPhysicsOn() { return m_physicsOn; }
	float		getDrag() { return m_drag; }
	//setters
	void		setPos(float x, float y, float z) { m_posx = x; m_posy = y; m_posz = z; }
	void		setScale(float _scale) { m_scale = _scale * XMVectorSet(1, 1, 1, 0); }
	void		setScale(float _x, float _y, float _z) { m_scale = XMVectorSet(_x, _y, _z, 0); }
	void		setScale(XMVECTOR _scale) { m_scale = _scale; }

	void		setPitch(float _pitch) { m_pitch = _pitch; }
	void		setYaw(float _yaw) { m_yaw = _yaw; }
	void		setRoll(float _roll) { m_roll = _roll; }
	void		setPitchYawRoll(float _pitch, float _yaw, float _roll) { m_pitch = _pitch; m_yaw = _yaw; m_roll = _roll; }

	void		setPhysicsOn(bool _physics) { m_physicsOn = _physics; }
	void		togglePhysics() { m_physicsOn = !m_physicsOn; }
	void		setDrag(float _drag) { m_drag = _drag; }


protected:

	//World transform/matrix of this GO and it components
	XMMATRIX m_worldMatrix;
	XMMATRIX m_rotationMatrix;
	XMMATRIX m_fudge;
	XMVECTOR m_pos;
	float m_pitch, m_yaw, m_roll,
		  m_posx, m_posy, m_posz;
	XMVECTOR m_scale;

	//very basic physics
	bool m_physicsOn = false;
	float m_drag = 0.0f;
	XMVECTOR m_vel = XMVectorSet(0, 0, 0, 0);
	XMVECTOR m_acc = XMVectorSet(0, 0, 0, 0);
};
