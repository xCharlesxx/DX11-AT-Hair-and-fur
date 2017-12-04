#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include "GameObject.h"

using namespace DirectX; 

class Lighting : public GameObject
{
public:
	Lighting(XMFLOAT3 _pos, XMFLOAT4 _colour);
private:
	XMFLOAT3 ShiftTangent(XMFLOAT3 T, XMFLOAT3 N, float shift);
	float StrandSpecular(XMFLOAT3 T, XMFLOAT3 V, XMFLOAT3 L, float exponent);
	virtual void draw(DrawData* _DD) override;
};

