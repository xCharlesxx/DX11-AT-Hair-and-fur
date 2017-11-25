#include "Model.h"
#include <DirectXMath.h>
Model::Model()
{
	
}

bool Model::getModel(const char* pFile)
{
	if (aiImportFile(pFile, aiProcessPreset_TargetRealtime_MaxQuality))
		m_debug.Output("Successful file grab");
	else
	{
		m_debug.Output("Unsuccessful file grab");
		m_debug.Output(aiGetErrorString());
	}

	auto modelFile = aiImportFile(pFile, aiProcessPreset_TargetRealtime_MaxQuality);
	m_debug.Output("Number of meshes found in file: " + std::to_string(modelFile->mNumMeshes));
	m_debug.Output("Number of vertices in first mesh: " + std::to_string(modelFile->mMeshes[0]->mNumVertices));

	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = modelFile; 
		//importer.ReadFile(pFile,
		//aiProcess_CalcTangentSpace |
		//aiProcess_Triangulate |
		//aiProcess_JoinIdenticalVertices |
		//aiProcess_SortByPType);
	aiMesh *mesh = scene->mMeshes[0];
	std::vector<UINT> indices;
	m_vertexCount = mesh->mNumVertices; 
	std::vector<Vertice> vertices(m_vertexCount);
	//vertices = new VertexType[m_vertexCount]; 
	if (m_vertexCount == 0)
		m_debug.Output("Error Loading Vertices");
	//indices = new unsigned long[m_indexCount]; 
	//if (indices)
	//	m_debug.Output("Error Loading Indicies");

	for (int i = 0; i<8; i++)
	{
		{
			aiVector3D pos = mesh->mVertices[i];
			vertices[i].Pos.x = pos.x;
			vertices[i].Pos.y = pos.y;
			vertices[i].Pos.z = pos.z;
		}
	}
	
	for (int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& Face = mesh->mFaces[i];
		if (Face.mNumIndices == 3) {
			indices.push_back(Face.mIndices[0]);
			indices.push_back(Face.mIndices[1]);
			indices.push_back(Face.mIndices[2]);
		}
	}

	// If the import failed, report it
	if (!scene)
	{
		//DoTheErrorLogging(importer.GetErrorString());
		return false;
	}
	// Now we can access the file's contents. 
	//DoTheSceneProcessing(scene);
	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}
