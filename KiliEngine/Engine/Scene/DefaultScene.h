#pragma once
#include "Scene.h"
#include "Engine/EnviroActor.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/FreeCamComponent.h"

class DefaultScene : public Scene
{

public :

	DefaultScene() : Scene("DefaultScene") {}
	~DefaultScene() override = default;

	void AssetLoad() override {
	}

	void OnStart() override {
		Camera* camera = new Camera(Transform(Vector3(0, 0, 1), Quaternion(), Vector3::unit), 70.0f, 0.1f, 1000.0f);
		camera->AddComponent(new FreeCamComponent(camera, 20.0f, 5.0f));
		AddActor(camera);

		EnviroActor* cube = new EnviroActor(Transform(Vector3(10, 0, 0), Quaternion(), Vector3::unit));
		cube->AddComponent(new MeshComponent(cube, Transform::Origin, AssetManager::GetMesh("cube")));
		AddActor(cube);

		EnviroActor* plane = new EnviroActor(Transform(Vector3(10, 3, 0), Quaternion(), Vector3::unit));
		plane->AddComponent(new MeshComponent(plane, Transform::Origin, AssetManager::GetMesh("plane")));
		AddActor(plane);

		EnviroActor* sphere = new EnviroActor(Transform(Vector3(10, 6, 0), Quaternion(), Vector3::unit));
		sphere->AddComponent(new MeshComponent(sphere, Transform::Origin, AssetManager::GetMesh("sphere")));
		AddActor(sphere);

		EnviroActor* monkey = new EnviroActor(Transform(Vector3(10, 9, 0), Quaternion(), Vector3::unit));
		monkey->AddComponent(new MeshComponent(monkey, Transform::Origin, AssetManager::GetMesh("monkey")));
		AddActor(monkey);
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};

