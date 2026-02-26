#pragma once
#include "Scene.h"
#include "AssetManager.h"
#include "BowlingBall.h"
#include "BowlingPin.h"
#include "BoxCollider.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "EnviroActor.h"
#include "Floor.h"
#include "RigidBody.h"
#include "SphereCollider.h"


class Bowling : public Scene
{

private:
	void CreateEnviroActor(const std::string& pMeshName, const std::string& pTextureName, const std::string& pShaderName = "Basic")
	{
		EnviroActor* enviro = new EnviroActor(Transform(Vector3::zero, Quaternion(Vector3::unitZ, 90.0f * MathUtils::DEG2RAD), Vector3(0.5f, 0.4f, 0.5f)));
		enviro->AddComponent(new MeshComponent(enviro, Transform::Origin, AssetManager::GetMesh(pMeshName), AssetManager::GetTexture(pTextureName), pShaderName));
		AddActor(enviro);
	}

	void CreateFloor(const Vector3& pPosition, const Vector3& pHalfSize)
	{
		Floor* floor = new Floor(Transform(pPosition, Quaternion(), Vector3::unit));
		floor->AddComponent(new BoxCollider(floor, Transform::Origin, pHalfSize));
		AddActor(floor);
	}

	void CreateBowlingBall(const Vector3& pPosition)
	{
		BowlingBall* ball  = new BowlingBall(Transform(pPosition, Quaternion(), Vector3(0.6f, 0.6f, 0.6f)));
		ball->AddComponent(new MeshComponent(ball, Transform::Origin, AssetManager::GetMesh("sphere"), AssetManager::GetTexture("bowling")));
		ball->AddComponent(new SphereCollider(ball, Transform::Origin, 1.0f));
		ball->AddComponent(new RigidBody(ball));
		AddActor(ball);
	}

	void CreateBowlingPin(const Vector3& pPosition)
	{
		BowlingPin* pin  = new BowlingPin(Transform(pPosition, Quaternion(), Vector3(0.2f, 0.2f, 0.2f)));
		pin->AddComponent(new MeshComponent(pin, Transform::Origin, AssetManager::GetMesh("Pin"), AssetManager::GetTexture("pin")));
		pin->AddComponent(new BoxCollider(pin, Transform::Origin, Vector3(1.4f,1.4f,4.5f)));
		AddActor(pin);
	}

	void CreatePinGroup(const Vector3& pPosition)
	{
		CreateBowlingPin(Vector3(0	, 0   ,	0) + pPosition);
		CreateBowlingPin(Vector3(1	, 0.5f,	0) + pPosition);
		CreateBowlingPin(Vector3(1	,-0.5f,	0) + pPosition);
		CreateBowlingPin(Vector3(2	, 1   ,	0) + pPosition);
		CreateBowlingPin(Vector3(2	, 0   ,	0) + pPosition);
		CreateBowlingPin(Vector3(2	,-1   ,	0) + pPosition);
		CreateBowlingPin(Vector3(3	, 1.5f,	0) + pPosition);
		CreateBowlingPin(Vector3(3	, 0.5f,	0) + pPosition);
		CreateBowlingPin(Vector3(3	,-0.5f,	0) + pPosition);
		CreateBowlingPin(Vector3(3	,-1.5f,	0) + pPosition);
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
		CreateEnviroActor("Decals", "decals", "Decals");
		CreateEnviroActor("Gutters", "gutters");
		CreateEnviroActor("Board", "board");

		CreateFloor(Vector3(40,0,-2), Vector3(50,2.65f,2));

		CreateBowlingBall(Vector3(70,0,0.6f));

		CreatePinGroup(Vector3(70,0,1));

		CreateBowlingPin(Vector3(0,0,1));
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};
