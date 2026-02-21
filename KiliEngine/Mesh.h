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
	std::string mShaderName;

public:

	Mesh();
	Mesh(const std::vector<Texture*>& pTextures, VertexArray* pVao, const std::string& pShader);

	bool LoadMesh(std::string pFileName);
	void Unload();

	[[nodiscard]] std::vector<Texture*> GetTextures() const { return mTextures; }
	[[nodiscard]] Texture* GetTexture(size_t pIndex) const;
	void SetTextures(const std::vector<Texture*>& pTextures) { mTextures = pTextures; }
	void AddTexture(Texture* pTexture) { mTextures.push_back(pTexture); }

	[[nodiscard]] VertexArray* GetVertexArray() const { return mVao; }
	void SetVertexArray(VertexArray* pVao) { mVao = pVao; }

	[[nodiscard]] std::string GetShaderName() const { return mShaderName; }
	ShaderProgram* GetShaderProgram() const;
	void SetShaderProgram(const std::string& pShader) { mShaderName = pShader; }
};

