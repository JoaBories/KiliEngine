#pragma once
#include "Engine/Scene/Scene.h"
#include "Engine/Assets/AssetManager.h"
#include "BowlingBall.h"
#include "BowlingPin.h"
#include "Engine/Components/BoxCollider.h"
#include "Engine/Components/SpriteComponent.h"
#include "Camera.h"
#include "EnviroActor.h"
#include "Floor.h"
#include "Engine/Components/FollowCameraComponent.h"
#include "Engine/Components/FreeCamComponent.h"
#include "Engine/Components/RigidBody.h"
#include "Engine/Components/SphereCollider.h"


class Bowling : public Scene
{

private:
	void CreateEnviroActor(const std::string& pMeshName, const std::string& pTextureName, const std::string& pShaderName = "BasicLight")
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
		BowlingBall* ball  = new BowlingBall(Transform(pPosition, Quaternion(), Vector3(0.55f, 0.55f, 0.55f)));
		ball->AddComponent(new MeshComponent(ball, Transform::Origin, AssetManager::GetMesh("sphere"), AssetManager::GetTexture("bowling"), "BasicLight"));
		ball->AddComponent(new MeshComponent(ball, Transform(Vector3::zero, Quaternion(), Vector3::unit * -5.0f), AssetManager::GetMesh("plane"), AssetManager::GetTexture("arrow"), "Decals"));
		ball->AddComponent(new SphereCollider(ball, Transform::Origin, 0.55f));
		ball->AddComponent(new RigidBody(ball, 0.01f,1,7,0.1f));
		AddActor(ball);
	}

	void CreateBowlingPin(const Vector3& pPosition)
	{
		BowlingPin* pin  = new BowlingPin(Transform(pPosition, Quaternion(Vector3::unitZ, 45.0f), Vector3(0.2f, 0.2f, 0.2f)));
		pin->AddComponent(new MeshComponent(pin, Transform::Origin, AssetManager::GetMesh("Pin"), AssetManager::GetTexture("pin"), "BasicLight"));
		pin->AddComponent(new BoxCollider(pin, Transform::Origin, Vector3(1.4f,1.4f,4.5f)));
		pin->AddComponent(new RigidBody(pin, 0.5f,1, 2.0f, 0.5f));
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

		Camera* camera = new Camera(Transform(Vector3(0, 0, 5.0f), Quaternion(), Vector3::zero), 70.0f, 0.1f, 1000.0f);
		//camera->AddComponent(new FreeCamComponent(camera, 20.0f, 10.0f));
		camera->AddComponent(new FollowCameraComponent(camera, nullptr, {false, true, true}, Vector3(-10,0,0)));
		AddActor(camera);
		
		CreateEnviroActor("Enviro1", "floor");
		CreateEnviroActor("Enviro2", "return");
		CreateEnviroActor("Decals", "decals", "Decals");
		CreateEnviroActor("Gutters", "gutters");
		CreateEnviroActor("Board", "board");

		CreateFloor(Vector3(40,0,-1), Vector3(40,2.65f,1));
		CreateFloor(Vector3(40,0,-0.75f), Vector3(40,5,0.5f));
		CreateFloor(Vector3(40,4,0.75f), Vector3(40,0.25f,1));
		CreateFloor(Vector3(40,-4,0.75f), Vector3(40,0.25f,1));

		CreateBowlingBall(Vector3(0,0,5));

		CreatePinGroup(Vector3(70,0,5));
		
		camera->GetComponent<FollowCameraComponent>()->SetTargetActor(GetActorOfClass<BowlingBall>());
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};
