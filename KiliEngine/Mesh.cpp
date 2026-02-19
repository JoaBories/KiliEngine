#include "Mesh.h"

#include "AssetManager.h"

Mesh::Mesh() :
	mFilename(""), mTextures(), mVao(nullptr), mShader(nullptr)
{
}

Mesh::Mesh(std::vector<Texture*> pTextures, VertexArray* pVao, ShaderProgram* pShader) :
	mFilename(""), mTextures(pTextures), mVao(pVao), mShader(pShader)
{
}

bool Mesh::LoadMesh(std::string pFileName)
{
	mVao = new VertexArray(CubeVertices, 28, CubeIndices, 12); // will be using mesh name to load it from file later
	mShader = new ShaderProgram("Resources/Shaders/Basic.vert", "Resources/Shaders/Basic.frag");
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
	else if (!mTextures.empty())
	{
		return mTextures.at(0);
	}
	else
	{
		return nullptr;
	}
}
