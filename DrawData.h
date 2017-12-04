#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include "Renderer.h"
using namespace DirectX;

class Camera;
class Lighting;

struct DrawData
{
	ID3D11DeviceContext* m_pd3dImmediateContext;
	Renderer* m_renderer; 
	Camera* m_cam;
	Lighting* m_light;
};