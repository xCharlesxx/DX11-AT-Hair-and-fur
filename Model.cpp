#include "Model.h"

Model::Model(const char* pFile, Renderer& renderer)
{
	getModel(pFile, renderer);
	createShaders(renderer);
	createRenderStates(renderer);
	transform = XMVectorSet(posX, posY, posZ, 0);
}

Model::~Model()
{
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
	m_rasterizerState->Release();
	m_depthState->Release();
	m_blendState->Release();
}
void Model::getModel(const char* pFile, Renderer& renderer)
{
	//Check if files are available
	if (aiImportFile(pFile, aiProcessPreset_TargetRealtime_MaxQuality))
		m_debug.Output("Successful file grab");
	else
	{
		m_debug.Output("Unsuccessful file grab");
		m_debug.Output(aiGetErrorString());
	}
	//Get file
	auto modelFile = aiImportFile(pFile, aiProcessPreset_TargetRealtime_Fast);
	m_debug.Output("Number of meshes found in file: " + std::to_string(modelFile->mNumMeshes));
	m_debug.Output("Number of vertices in meshes: ");
	for (int i = 0; i < modelFile->mNumMeshes; i++)
		m_debug.Output(std::to_string(i) + " " + std::to_string(modelFile->mMeshes[0]->mNumVertices));
	
	//Create an instance of the Importer class
	Assimp::Importer importer;
	const aiScene* scene = modelFile; 
	aiMesh *mesh = scene->mMeshes[0];
	std::vector<UINT> indices;
	m_vertexCount = mesh->mNumVertices; 
	std::vector<Vertice> vertices(m_vertexCount);
	//vertices = new Vertice[m_vertexCount]; 

	for (int i = 0; i < vertices.size(); i++)
	{
		{
			aiVector3D pos = mesh->mVertices[i];
			vertices[i].Pos.x = pos.x;
			vertices[i].Pos.y = pos.y;
			vertices[i].Pos.z = pos.z;
			m_debug.Output(std::to_string(vertices[0].Pos.x) + std::to_string(vertices[0].Pos.y) + std::to_string(vertices[0].Pos.z));
		}
	}
	
	m_debug.Output("Number of Faces: ");
	m_debug.Output(std::to_string(mesh->mNumFaces));
	
	for (int i = 0; i < mesh->mNumFaces; i++) 
	{
		const aiFace& Face = mesh->mFaces[i];
		for (int x = 0; x < Face.mNumIndices; x++)
			indices.push_back(Face.mIndices[x]);
	}

	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	//vertexData.pSysMem = vertices;
	renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
}

void Model::createShaders(Renderer & renderer)
{
	//Create shaders
	ifstream vsFile("VertexShader.cso", ios::binary);
	vector<char> vsData = { istreambuf_iterator<char>(vsFile), istreambuf_iterator<char>() };

	ifstream psFile("PixelShader.cso", ios::binary);
	vector<char> psData = { istreambuf_iterator<char>(psFile), istreambuf_iterator<char>() };

	renderer.getDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	renderer.getDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);

	//Create input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	renderer.getDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
}



void Model::createRenderStates(Renderer& renderer)
{
	//Rasterizer state
	auto rasterizerDesc = CD3D11_RASTERIZER_DESC(
		D3D11_FILL_SOLID,
		D3D11_CULL_NONE,
		false,
		0, 0, 0, 0,
		false, false, false);
	renderer.getDevice()->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);

	//Blend state
	auto blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	renderer.getDevice()->CreateBlendState(&blendDesc, &m_blendState);

	//Depth state
	auto depthDesc = CD3D11_DEPTH_STENCIL_DESC(
		FALSE, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS,
		FALSE, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS,
		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS);
	renderer.getDevice()->CreateDepthStencilState(&depthDesc, &m_depthState);
}
void Model::draw(Renderer & renderer)
{
	auto deviceContext = renderer.getDeviceContext();

	////Set render states
	deviceContext->RSSetState(m_rasterizerState);
	deviceContext->OMSetBlendState(m_blendState, NULL, 0xffffffff);
	deviceContext->OMSetDepthStencilState(m_depthState, 1);

	////Bind the triangle shaders
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	//Bind the vertex buffer
	UINT stride = sizeof(Vertice);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	
	//Draw
	deviceContext->Draw(m_vertexCount, 0);
}


//importer.ReadFile(pFile,
//aiProcess_CalcTangentSpace |
//aiProcess_Triangulate |
//aiProcess_JoinIdenticalVertices |
//aiProcess_SortByPType);