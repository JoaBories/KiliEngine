#pragma once
#include "Scene.h"
#include "Engine/CameraActor.h"
#include "Engine/EnviroActor.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/FreeCamComponent.h"
#include "Engine/Components/MeshComponent.h"
#include "Engine/Components/PlaneCollider.h"
#include "Engine/Components/RigidBody.h"
#include "Engine/Components/SphereCollider.h"
#include "Engine/Components/SpriteComponent.h"
#include "Engine/Components/TerrainComponent.h"

class DefaultScene : public Scene
{
	void CreateEnviroActor(const Transform& pTransform, const std::string& pMesh, const std::string& pTexture = "DefaultTexture", const std::string& pShader = "Basic")
	{
		EnviroActor* actor = new EnviroActor(pTransform);
		actor->AddComponent(new MeshComponent(actor, Transform::Origin, AssetManager::GetMesh(pMesh), AssetManager::GetTexture(pTexture), pShader));
		AddActor(actor);
	}

public :

	DefaultScene() : Scene("DefaultScene") {}
	~DefaultScene() override = default;

	void AssetLoad() override {
	}

	void OnStart() override {
		CameraActor* camera = new CameraActor(Transform(Vector3(0, 0, 10), Quaternion(), Vector3::unit), 70.0f, 0.1f, 1000.0f);
		camera->AddComponent(new FreeCamComponent(camera, 20.0f, 5.0f));
		AddActor(camera);
		
		EnviroActor* terrain = new EnviroActor(Transform(Vector3(0,0,0), Quaternion(), Vector3::unit));
		terrain->AddComponent(new TerrainComponent(terrain, Transform::Origin, 
			AssetManager::GetTexture("Ground"), 2.0f, 10, 25));
		//terrain->AddComponent(new PlaneCollider(terrain, Transform::Origin, Vector2(25, 25)));
		AddActor(terrain);

		EnviroActor* ball  = new EnviroActor(Transform(Vector3(0,0,10), Quaternion(), Vector3(0.55f, 0.55f, 0.55f)));
		ball->AddComponent(new MeshComponent(ball, Transform::Origin, AssetManager::GetMesh("sphere"), AssetManager::GetTexture("bowling"), "BasicLight"));
		ball->AddComponent(new SphereCollider(ball, Transform::Origin, 0.55f));
		ball->AddComponent(new RigidBody(ball, 0.01f,1,7,0.1f));
		AddActor(ball);

		CreateEnviroActor(Transform(Vector3(10, 12, 0), Quaternion(), Vector3::unit), "cube", "DefaultTexture", "BasicLight");
		CreateEnviroActor(Transform(Vector3(10, 3, 0), Quaternion(), Vector3::unit), "plane", "DefaultTexture", "BasicLight");
		CreateEnviroActor(Transform(Vector3(10, 6, 0), Quaternion(), Vector3::unit), "sphere", "DefaultTexture", "BasicLight");
		CreateEnviroActor(Transform(Vector3(10, 9, 0), Quaternion(), Vector3::unit), "monkey", "DefaultTexture", "BasicLight");
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};

