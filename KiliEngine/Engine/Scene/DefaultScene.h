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
		Camera* camera = new Camera(Transform::Origin, 70.0f, 0.1f, 1000.0f);
		camera->AddComponent(new FreeCamComponent(camera, 20.0f, 5.0f));
		AddActor(camera);

		EnviroActor* cube = new EnviroActor(Transform::Origin);
		cube->AddComponent(new MeshComponent(cube, Transform::Origin, AssetManager::GetMesh("cube")));
		AddActor(cube);
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};

