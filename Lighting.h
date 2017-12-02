#pragma once
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX; 

class Lighting
{
public:
	Lighting();
private:
	XMFLOAT3 ShiftTangent(XMFLOAT3 T, XMFLOAT3 N, float shift);
	float StrandSpecular(XMFLOAT3 T, XMFLOAT3 V, XMFLOAT3 L, float exponent);
};

