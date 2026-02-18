#include "Mesh.h"

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
	mVao = new VertexArray(cubeVertices, 28, cubeIndices, 12); // will be using mesh name to load it from file later
}

void Mesh::Unload()
{
	delete mVao;
	mVao = nullptr;
}

Texture* Mesh::GetTexture(int index) const
{
	if (mTextures.size() > index)
	{
		return mTextures.at(index);
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
