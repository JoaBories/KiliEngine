#pragma once
#include "Scene.h"
#include "Engine/EnviroActor.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/FreeCamComponent.h"
#include "Engine/Components/MeshComponent.h"
#include "Engine/Components/SpriteComponent.h"

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
		Camera* camera = new Camera(Transform(Vector3(0, 0, 10), Quaternion(), Vector3::unit), 70.0f, 0.1f, 1000.0f);
		camera->AddComponent(new FreeCamComponent(camera, 20.0f, 5.0f));
		AddActor(camera);
		
		EnviroActor* sprite = new EnviroActor(Transform::Origin);
		sprite->AddComponent(new SpriteComponent(sprite, Transform::Origin, AssetManager::GetTexture("DefaultTexture")));
		AddActor(sprite);

		CreateEnviroActor(Transform(Vector3(10, 12, 0), Quaternion(), Vector3::unit), "cube", "DefaultTexture", "BasicLight");
		CreateEnviroActor(Transform(Vector3(10, 3, 0), Quaternion(), Vector3::unit), "plane", "DefaultTexture", "BasicLight");
		CreateEnviroActor(Transform(Vector3(10, 6, 0), Quaternion(), Vector3::unit), "sphere", "DefaultTexture", "BasicLight");
		CreateEnviroActor(Transform(Vector3(10, 9, 0), Quaternion(), Vector3::unit), "monkey", "DefaultTexture", "BasicLight");

		CreateEnviroActor(Transform(Vector3(0, 0, -5), Quaternion(), Vector3(20,20,1)), "planeBig", "Ground", "TerrainTess");
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};

