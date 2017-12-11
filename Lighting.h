#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include "GameObject.h"

using namespace DirectX; 

class Lighting : public GameObject
{
public:
	Lighting(XMFLOAT3 _pos, XMFLOAT4 _colour, XMFLOAT3 _attenuation, float _range, XMFLOAT4 _ambient, XMFLOAT4 _diffuse);
private:
	XMFLOAT3 dir;
	float  range;
	XMFLOAT3 att;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 colour; 
	XMFLOAT3 ShiftTangent(XMFLOAT3 T, XMFLOAT3 N, float shift);
	float StrandSpecular(XMFLOAT3 T, XMFLOAT3 V, XMFLOAT3 L, float exponent);
	virtual void draw(DrawData* _DD) override;
};

