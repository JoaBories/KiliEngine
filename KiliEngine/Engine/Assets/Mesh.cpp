#include "Mesh.h"
#include "AssetManager.h"

Mesh::Mesh() :
	mVao(nullptr), mMaterialName("Basic")
{
}

Mesh::Mesh(const std::vector<Vertex>& pVertices) :
	mMaterialName("Basic")
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

Material* Mesh::GetMaterial() const
{
	return AssetManager::GetMaterial(mMaterialName);
}
