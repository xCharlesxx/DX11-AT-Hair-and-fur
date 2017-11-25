#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/cimport.h>
#include <vector>
#include <string>
#include <d3d11.h>
#include <directxmath.h>
#include "Debug.h"
#include "Renderer.h"
using namespace DirectX; 

class Model
{
public:
	Model();
	bool getModel(const char* pFile);
	void draw(Renderer& renderer);
private:
	Debug m_debug;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	struct Vertice
	{
		XMFLOAT3 Pos; 
		XMFLOAT3 colour; 
	};
};