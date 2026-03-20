#pragma once
#include <map>

#include "IRenderer.h"
#include "Engine/VertexArray.h"
#include "Engine/Assets/Shader.h"
#include "Utils/Matrix4Row.h"
#include "Engine/Components/MeshComponent.h"


#ifdef _DEBUG
enum RenderMode : Uint8
{
	DefaultRender,
	Uvs,
	Normals,
	Wireframe,
};
#endif

class SpriteComponent;

class GlRenderer : public IRenderer
{
private:
	Window* mWindow;
	VertexArray* mSpriteVao;
	
	Material* mSpriteMaterial;
	
	Matrix4Row mSpriteViewProj;
	
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
	std::map<std::string, std::vector<MeshComponent*>> mMeshes; //Mesh sorted by material

public:
	
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

	[[nodiscard]] SDL_GLContext GetContext() const {return mContext;}

#ifdef _DEBUG

private:
	std::vector<ColliderComponent*> mColliders;
	
public:
	static RenderMode RenderMode;
	
	void AddCollider(ColliderComponent* pCollider) override;
	void RemoveCollider(ColliderComponent* pCollider) override;

	void DrawColliders();
	
#endif
};
