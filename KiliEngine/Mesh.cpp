#include "Mesh.h"
#include "AssetManager.h"

float* Mesh::ToVerticeArray(const std::vector<Vertex>& pVertices)
{
	const auto array = new float[pVertices.size() * 8];
	int counter = 0;
	for (auto& [Position, Normal, Uv] : pVertices)
	{
		array[counter+0] = Position.x;
		array[counter+1] = Position.y;
		array[counter+2] = Position.z;
		array[counter+3] = Normal.x;
		array[counter+4] = Normal.y;
		array[counter+5] = Normal.z;
		array[counter+6] = Uv.x;
		array[counter+7] = Uv.y;
		counter += 8;
	}
	return array;
}

Mesh::Mesh() :
	mVao(nullptr), mShaderName("Basic")
{
}

Mesh::Mesh(const std::vector<Vertex>& pVertices) :
	mShaderName("Basic")
{
	float* verticeInfo = ToVerticeArray(pVertices);
	mVao = new VertexArray(verticeInfo, pVertices.size());
	delete[] verticeInfo;
}

void Mesh::Unload()
{
	delete mVao;
	mVao = nullptr;
}

Texture* Mesh::GetTexture(const size_t pIndex) const
{
	if (mTextures.size() > pIndex)
	{
		return mTextures.at(pIndex);
	}
	
	if (!mTextures.empty())
	{
		return mTextures.at(0);
	}
	
	return nullptr;
}

ShaderProgram* Mesh::GetShaderProgram() const
{
	return AssetManager::GetShader(mShaderName);
}
