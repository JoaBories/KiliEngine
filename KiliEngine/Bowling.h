#pragma once
#include "Scene.h"
#include "AssetManager.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "EnviroActor.h"


class Bowling : public Scene
{

private:
	void CreateEnviroActor(const std::string& pMeshName, const std::string& pTextureName)
	{
		EnviroActor* Enviro = new EnviroActor(Transform::Origin);
		Enviro->AddComponent(new MeshComponent(Enviro, Transform::Origin, AssetManager::GetMesh(pMeshName), AssetManager::GetTexture(pTextureName)));
		AddActor(Enviro);
	}

public:

	Bowling() : Scene("Test openGl") {}
	~Bowling() override = default;

	void AssetLoad() override {
		AssetManager::LoadTexture("pokeball");
		AssetManager::LoadTexture("rock");
	}

	void OnStart() override {
		AddActor(new Camera(Transform::Origin, 70.0f, 0.1f, 1000.0f));
		
		CreateEnviroActor("Enviro1", "floor");
		CreateEnviroActor("Enviro2", "return");
		CreateEnviroActor("Decals", "decals");
		CreateEnviroActor("Gutters", "floor");
		CreateEnviroActor("Board", "board");
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};
