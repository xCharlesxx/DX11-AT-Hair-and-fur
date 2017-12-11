#include "Model.h"
#include "DrawData.h"

Model::Model(const char* pFile, DrawData* _DD)
{
	getModel(pFile, *_DD->m_renderer);
	createShaders(*_DD->m_renderer);
	createRenderStates(*_DD->m_renderer);
	//this->setScale(XMVectorSet(1, 1, 1, 0));
	this->setPos(0, 0, 0);
	this->setScaler(537616192);
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
void Model::getModel(const char* pFile, Renderer & renderer)
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
	if (!modelFile)
		m_debug.Output("Error storing data in file: " + string(pFile));

	
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
	m_indexCount = indices.size(); 

	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(Vertice) * vertices.size(), D3D11_BIND_VERTEX_BUFFER);
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE; 
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = &vertices[0];
	renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	auto indexBufferDesc = CD3D11_BUFFER_DESC(sizeof(UINT) * indices.size(), D3D11_BIND_INDEX_BUFFER);
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA indexData = { 0 };
	indexData.pSysMem = &indices[0];
	renderer.getDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);

}

void Model::createLight()
{
	//light.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//light.range = 100.0f;
	//light.att = XMFLOAT3(0.0f, 0.2f, 0.0f);
	//light.ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	//light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
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
		{ "POSITION", 3, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 3, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = _countof(layout); 
	renderer.getDevice()->CreateInputLayout(layout, numElements, vsData.data(), vsData.size(), &m_inputLayout);
}

void Model::createRenderStates(Renderer& renderer)
{
	//Rasterizer state
	auto rasterizerDesc = CD3D11_RASTERIZER_DESC(
		D3D11_FILL_SOLID,
		D3D11_CULL_NONE,
		true,
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

void Model::draw(DrawData* _DD)
{
	auto deviceContext = _DD->m_renderer->getDeviceContext();
	m_material->setTransformMatrix(XMMatrixTranspose(m_worldMatrix));
	m_material->setViewMatrix(XMMatrixTranspose(_DD->m_cam->getViewMatrix()));
	m_material->setProjectionMatrix(XMMatrixTranspose(_DD->m_cam->getProjMatrix()));
	m_material->updateBuffers(_DD);
	m_material->setBuffers(_DD);

	//////Set render states
    deviceContext->RSSetState(m_rasterizerState);
	deviceContext->OMSetBlendState(m_blendState, NULL, 0xffffffff);
	deviceContext->OMSetDepthStencilState(m_depthState, 1);

	////Bind the triangle shaders
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
	//Bind the vertex buffer
	UINT stride = sizeof(Vertice);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	////Draw
	deviceContext->DrawIndexed(m_indexCount, 0, 0);
}


//importer.ReadFile(pFile,
//aiProcess_CalcTangentSpace |
//aiProcess_Triangulate |
//aiProcess_JoinIdenticalVertices |
//aiProcess_SortByPType);