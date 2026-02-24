#pragma once
#include "Scene.h"
#include "AssetManager.h"
#include "BowlingBall.h"
#include "BowlingPin.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "EnviroActor.h"


class Bowling : public Scene
{

private:
	void CreateEnviroActor(const std::string& pMeshName, const std::string& pTextureName)
	{
		EnviroActor* enviro = new EnviroActor(Transform(Vector3::zero, Quaternion(Vector3::unitZ, 90.0f), Vector3(0.5f, 0.5f, 0.5f)));
		enviro->AddComponent(new MeshComponent(enviro, Transform::Origin, AssetManager::GetMesh(pMeshName), AssetManager::GetTexture(pTextureName)));
		AddActor(enviro);
	}

	void CreateBowlingBall(const Vector3& pPosition)
	{
		BowlingBall* ball  = new BowlingBall(Transform(pPosition, Quaternion(), Vector3(1, 1, 1)));
		ball->AddComponent(new MeshComponent(ball, Transform::Origin, AssetManager::GetMesh("sphere"), AssetManager::GetTexture("bowling")));
		AddActor(ball);
	}

	void CreateBowlingPin(const Vector3& pPosition)
	{
		BowlingPin* pin  = new BowlingPin(Transform(pPosition, Quaternion(), Vector3(0.2f, 0.2f, 0.2f)));
		pin->AddComponent(new MeshComponent(pin, Transform::Origin, AssetManager::GetMesh("Pin"), AssetManager::GetTexture("pin")));
		AddActor(pin);
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

		CreateBowlingBall(Vector3(10,0,4));

		CreateBowlingPin(Vector3(10,0,4));
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};
