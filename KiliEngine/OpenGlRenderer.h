#pragma once
#include <map>

#include "IRenderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Matrix4Row.h"
#include "MeshComponent.h"

enum RenderMode : Uint8
{
	DefaultRender,
	Uvs,
	Normals,
	Wireframe,
};


class SpriteComponent;

class GlRenderer : public IRenderer
{
private:
	Window* mWindow;
	VertexArray* mSpriteVao;
	
	ShaderProgram* mSpriteShader;
	
	Matrix4Row mSpriteViewProj;
	
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
	std::map<std::string, std::vector<MeshComponent*>> mMeshes; //Mesh sorted by shader
public:

	static RenderMode RenderMode;
	
	GlRenderer();

	~GlRenderer() override = default;
	GlRenderer(const GlRenderer&) = delete;
	GlRenderer& operator=(const GlRenderer&) = delete;

	bool Initialize(Window& pWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void DrawMeshes() const;
	void DrawSprites();
	void EndDraw() override;
	void Close() override;

	void DrawSprite(GameActor* pActor, WorldTransform pTransform, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip pFlip) const override;
	void AddSprite(SpriteComponent* pSprite) override;
	void RemoveSprite(SpriteComponent* pSprite) override;

	void AddMesh(MeshComponent* pMesh) override;
	void RemoveMesh(const MeshComponent* pMesh) override;
	
	RendererType GetType() override;
};
