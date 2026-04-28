#pragma once
#include <map>

#include "Engine/Camera.h"
#include "Engine/Window.h"

#include "Engine/VertexArray.h"

#include "Engine/Transform.h"
#include "Engine/Assets/Material.h"
#include "Game/AdvancedOpenGl/PlanetMeshComponent.h"
#include "Utils/Matrix4Row.h"
#include "Utils/Struct.h"
class BillboardComponent;
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
	std::vector<BillboardComponent*> mBillboards;
	std::vector<PlanetMeshComponent*> mPlanetMeshes;

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
	void DrawBillboards();
	void DrawPlanetMeshes();
	void EndDraw();
	void Close();
	
	void SetCamera(Camera* pCamera) { mCamera = pCamera; }
	Camera* GetCamera() const { return mCamera; }

	void DrawSprite(GameActor* pActor, const WorldTransform& pTransform, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, SDL_RendererFlip pFlip) const;
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);

	void AddMesh(MeshComponent* pMesh);
	void RemoveMesh(const MeshComponent* pMesh);
	
	void AddTerrain(TerrainComponent* pTerrain);
	void RemoveTerrain(const TerrainComponent* pTerrain);
	
	void AddBillboard(BillboardComponent* pBillboard);
	void RemoveBillboard(const BillboardComponent* pBillboard);

	void AddPlanetMesh(PlanetMeshComponent* pPlanetMesh);
	void RemovePlanetMesh(const PlanetMeshComponent* pPlanetMesh);

	[[nodiscard]] SDL_GLContext GetContext() const {return mContext;}
	[[nodiscard]] Window* GetWindow() const {return mWindow;}

#ifdef _DEBUG

private:
	std::vector<ColliderComponent*> mColliders;
	
public:
	static RenderMode RenderMode;
	
	void AddCollider(ColliderComponent* pCollider);
	void RemoveCollider(const ColliderComponent* pCollider);

	void DrawColliders();
	
#endif
};
