#pragma once

#include <string>
#include <vector>
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"

class Mesh
{
private:
	std::string mFilename;
	std::vector<Texture*> mTextures;
	VertexArray* mVao;
	ShaderProgram* mShader;

public:

	Mesh();
	Mesh(std::vector<Texture*> pTextures, VertexArray* pVao, ShaderProgram* pShader);

	bool LoadMesh(std::string pFileName);
	void Unload();

	std::vector<Texture*> GetTextures() const { return mTextures; };
	Texture* GetTexture(int index) const;
	void SetTextures(std::vector<Texture*> pTextures) { mTextures = pTextures; };
	void AddTexture(Texture* pTexture) { mTextures.push_back(pTexture); };

	VertexArray* GetVertexArray() const { return mVao; };
	void SetVertexArray(VertexArray* pVao) { mVao = pVao; };

	ShaderProgram* GetShaderProgram() const { return mShader; };
	void SetShaderProgram(ShaderProgram* pShader) { mShader = pShader; };
};

