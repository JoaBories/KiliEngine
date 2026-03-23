#pragma once
#include <map>

#include "Engine/Camera.h"
#include "Engine/Window.h"

#include "Engine/VertexArray.h"

#include "Engine/Transform.h"
#include "Engine/Assets/Material.h"
#include "Utils/Matrix4Row.h"
#include "Utils/Struct.h"
using Struct::Rectangle;

class Texture;
class SpriteComponent;
class MeshComponent;
class ColliderComponent;
class TerrainComponent;

#ifdef _DEBUG
enum RenderMode : Uint8
{
	DefaultRender,
	Uvs,
	Normals,
	Wireframe,
};
#endif

class GlRenderer
{
private:
	Window* mWindow;
	VertexArray* mSpriteVao;
	
	Material* mSpriteMaterial;
	
	Camera* mCamera = nullptr;
	
	Matrix4Row mSpriteViewProj;
	
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
	std::map<std::string, std::vector<MeshComponent*>> mMeshes; //Meshes sorted by material
	std::map<std::string, std::vector<TerrainComponent*>> mTerrains; //Terrains sorted by material

public:
	
	GlRenderer();

	~GlRenderer() = default;
	GlRenderer(const GlRenderer&) = delete;
	GlRenderer& operator=(const GlRenderer&) = delete;

	bool Initialize(Window& pWindow);
	void BeginDraw();
	void Draw();
	void DrawMeshes() const;
	void DrawSprites();
	void DrawTerrains();
	void EndDraw();
	void Close();
	
	void SetCamera(Camera* pCamera) {mCamera = pCamera;}

	void DrawSprite(GameActor* pActor, const WorldTransform& pTransform, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip pFlip) const;
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);

	void AddMesh(MeshComponent* pMesh);
	void RemoveMesh(const MeshComponent* pMesh);
	
	void AddTerrain(TerrainComponent* pTerrain);
	void RemoveTerrain(const TerrainComponent* pTerrain);

	[[nodiscard]] SDL_GLContext GetContext() const {return mContext;}

#ifdef _DEBUG

private:
	std::vector<ColliderComponent*> mColliders;
	
public:
	static RenderMode RenderMode;
	
	void AddCollider(ColliderComponent* pCollider);
	void RemoveCollider(ColliderComponent* pCollider);

	void DrawColliders();
	
#endif
};
