#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include "DrawData.h"
using namespace DirectX; 

class Material
{
public:
	Material();
	~Material();
	void createBuffers(DrawData *_DD); 
	void setTransformMatrix(const XMMATRIX &transMatrix) { obj.transform = transMatrix; };
	void setViewMatrix(const XMMATRIX &viewMatrix) { frame.view = viewMatrix; };
	void setProjectionMatrix(const XMMATRIX &projMatrix) {}; 
	void setCameraPos(XMVECTOR pos) {}; 
	void setBuffers(DrawData *_DD); 
	void updateBuffers(DrawData *_DD);
private: 
	XMMATRIX m_transMateral; 
	ID3D11Buffer* object_buffer = nullptr; 
	ID3D11Buffer* frame_buffer = nullptr; 

	struct VSFRAMEBUFFER
	{
		XMMATRIX view; 
	};
	struct VSOBJBUFFER
	{
		XMMATRIX transform; 
	};
	VSFRAMEBUFFER frame; 
	VSOBJBUFFER obj; 

};

