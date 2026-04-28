#include "Mesh.h"
#include "AssetManager.h"
#include "Engine/Tools/Log.h"

Mesh::Mesh() :
	mVao(nullptr), mMaterialName("Basic")
{
}

Mesh::Mesh(const std::vector<Vertex>& pVertices, Texture* pTexture, std::string pMaterialName) :
	mTextures({pTexture}), mMaterialName(std::move(pMaterialName))
{
	float* verticeInfo = ToVerticeArray(pVertices);
	mVao = new VertexArray(verticeInfo, pVertices.size());
	delete[] verticeInfo;
}

Mesh::~Mesh()
{
	Unload();
	mTextures.clear();
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
