#pragma once

#include <string>
#include <vector>
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Vertex.h"

class Mesh
{
private:
	std::string mFilename;
	std::vector<Vertex> mVertices;
	VertexArray* mVao;
	std::vector<Texture*> mTextures;
	std::string mShaderName;
	
	float* ToVerticeArray();

public:
	explicit Mesh(std::vector<Vertex> pVertices);
	
	void Unload();

	[[nodiscard]] std::vector<Texture*> GetTextures() const { return mTextures; }
	[[nodiscard]] Texture* GetTexture(size_t pIndex) const;
	void SetTextures(const std::vector<Texture*>& pTextures) { mTextures = pTextures; }
	void AddTexture(Texture* pTexture) { mTextures.push_back(pTexture); }

	[[nodiscard]] VertexArray* GetVertexArray() const { return mVao; }
	void SetVertexArray(VertexArray* pVao) { mVao = pVao; }

	[[nodiscard]] std::string GetShaderName() const { return mShaderName; }
	[[nodiscard]] ShaderProgram* GetShaderProgram() const;
	void SetShader(const std::string& pShader) { mShaderName = pShader; }
};

