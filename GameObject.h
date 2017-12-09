#pragma once
#include "DirectXMath.h"
#include <string>

using namespace DirectX;

struct DrawData;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void draw(DrawData* _DD) = 0;
	void updateWorldMatrix(); 
	void tick(); 

	//getters
	XMVECTOR		getPos() { return m_pos; }
	XMVECTOR		getScale() { return m_scale; }
	XMMATRIX     getWorldMat() { return m_worldMatrix; }
	float*       getXPos() { return &m_posx; }
	float*       getYPos() { return &m_posy; }
	float*       getZPos() { return &m_posz; }
	float*       getYaw() { return &m_yaw; }
	float*       getPitch() { return &m_pitch; }
	float*       getRoll() { return &m_roll; }
	float*       getScaler() { return &m_scaler; }
	bool		isPhysicsOn() { return m_physicsOn; }
	float		getDrag() { return m_drag; }
	std::string getPosStr() { return std::to_string(m_posx) + ", " + std::to_string(m_posy) + ", " + std::to_string(m_posz); }
	std::string getRotStr() { return std::to_string(m_yaw) + ", " + std::to_string(m_pitch) + ", " + std::to_string(m_roll); }

	//setters
	void		setPos(float x, float y, float z) { m_posx = x; m_posy = y; m_posz = z; }
	void		setScale(float _scale) { m_scale = _scale * XMVectorSet(1, 1, 1, 0); }
	void		setScale(float _x, float _y, float _z) { m_scale = XMVectorSet(_x, _y, _z, 0); }
	void		setScale(XMVECTOR _scale) { m_scale = _scale; }
	void        setScaler(int scaler) { m_scaler = scaler; }
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
		  m_posx, m_posy, m_posz,
		  m_scaler;
	XMVECTOR m_scale;

	//very basic physics
	bool m_physicsOn = false;
	float m_drag = 0.0f;
	XMVECTOR m_vel = XMVectorSet(0, 0, 0, 0);
	XMVECTOR m_acc = XMVectorSet(0, 0, 0, 0);
};
