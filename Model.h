#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/cimport.h>
#include <vector>
#include <string>
#include <fstream>
#include <d3d11.h>
#include <directxmath.h>
#include "Debug.h"
#include "Renderer.h"
#include "gameobject.h"

using namespace std;
using namespace DirectX; 

class Model : public GameObject
{
public:
	Model(const char* pFile, DrawData* _DD);
	~Model();
	void getModel(const char* pFile, Renderer& renderer);
	void createShaders(Renderer& renderer);
	void createRenderStates(Renderer& renderer);
	virtual void draw(DrawData* _DD) override;
	//void draw(Renderer& renderer);
	//XMVECTOR getTransform() { return transform; };
private:
	Debug m_debug;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;
	ID3D11RasterizerState* m_rasterizerState = nullptr;
	ID3D11DepthStencilState* m_depthState = nullptr;
	ID3D11BlendState* m_blendState = nullptr;

	int m_vertexCount, m_indexCount;
	struct Vertice
	{
		XMFLOAT3 Pos; 
		XMFLOAT3 Colour; 
	};
};