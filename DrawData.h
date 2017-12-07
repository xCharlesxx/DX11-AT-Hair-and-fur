#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include "Renderer.h"
using namespace DirectX;

class Camera;
class Lighting;

struct DrawData
{
	Renderer* m_renderer = nullptr; 
	Camera* m_cam = nullptr;
	Lighting* m_light = nullptr;
};