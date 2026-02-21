#include "Mesh.h"

#include "AssetManager.h"

Mesh::Mesh() :
	mVao(nullptr)
{
}

Mesh::Mesh(const std::vector<Texture*>& pTextures, VertexArray* pVao, const std::string& pShader) :
	mTextures(pTextures), mVao(pVao), mShaderName(pShader)
{
}

bool Mesh::LoadMesh(std::string pFileName)
{
	mVao = new VertexArray(CubeVertices, 28, CubeIndices, 12); // will be using mesh name to load it from file later
	mShaderName = "Basic";
	mTextures.push_back(AssetManager::GetTexture("rock"));
	return true;
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
