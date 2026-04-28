#pragma once
#include "Scene.h"
#include "Engine/CameraActor.h"
#include "Engine/EnviroActor.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/FreeCamComponent.h"
#include "Engine/Components/InstanceComponent.h"
#include "Engine/Components/MeshComponent.h"

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

		EnviroActor* blades = new EnviroActor(Transform(Vector3(100.0f, 0.0f, 0.0f), Quaternion(), Vector3::unit));
		blades->AddComponent(new InstanceComponent(blades, Transform::Origin, AssetManager::GetMesh("grass"), Vector2(100.0f,100.0f), 50000, AssetManager::GetTexture("grass")));
		blades->AddComponent(new MeshComponent(blades, Transform(Vector3(0,0,0), Quaternion(), Vector3(10.0f, 10.0f, 1.0f)), AssetManager::GetMesh("planeBig"), AssetManager::GetTexture("grassSoil")));
		AddActor(blades);
		
		EnviroActor* actor = new EnviroActor(Transform(Vector3::zero, Quaternion(), Vector3::unit * 3.0f));
		actor->AddComponent(new MeshComponent(actor, Transform::Origin, AssetManager::GetMesh("cube"), AssetManager::GetTexture("null"), "Planet"));
		actor->AddComponent(new MeshComponent(actor, Transform::Origin, AssetManager::GetMesh("cube"), AssetManager::GetTexture("null"), "PlanetGeom"));
		AddActor(actor);

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

