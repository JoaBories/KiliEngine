#pragma once

#include <string>
#include <vector>
#include "Texture.h"
#include "Engine/VertexArray.h"
#include "Material.h"
#include "Utils/Vertex.h"

class Mesh
{
private:
	std::string mFilename;
	VertexArray* mVao;
	std::vector<Texture*> mTextures;
	std::string mMaterialName;

public:
	Mesh();
	explicit Mesh(const std::vector<Vertex>& pVertices, Texture* pTexture = nullptr, std::string pMaterialName = "Basic");
	~Mesh();
	
	void Unload();

	[[nodiscard]] std::vector<Texture*> GetTextures() const { return mTextures; }
	[[nodiscard]] Texture* GetTexture(size_t pIndex) const;
	void SetTextures(const std::vector<Texture*>& pTextures) { mTextures = pTextures; }
	void AddTexture(Texture* pTexture) { mTextures.push_back(pTexture); }

	[[nodiscard]] VertexArray* GetVertexArray() const { return mVao; }
	void SetVertexArray(VertexArray* pVao) { mVao = pVao; }

	[[nodiscard]] std::string GetMaterialName() const { return mMaterialName; }
	[[nodiscard]] Material* GetMaterial() const;
	void SetShader(const std::string& pShader) { mMaterialName = pShader; }
};