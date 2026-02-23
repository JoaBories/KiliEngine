#pragma once
#include "Scene.h"
#include "AssetManager.h"
#include "TestActor.h"
#include "SpriteComponent.h"
#include "Camera.h"


class TestGl : public Scene
{

public:

	TestGl() : Scene("Test openGl") {}
	~TestGl() override = default;

	void AssetLoad() override {
		AssetManager::LoadTexture("pokeball");
		AssetManager::LoadTexture("rock");
	}

	void OnStart() override {
		auto camera = new Camera(Transform::Origin, 90.0f, 0.1f, 1000.0f);
		AddActor(camera);
		
		TestActor* testMesh = new TestActor(Transform(Vector3(0,2,0), Quaternion(Vector3::unitZ, 180), Vector3::unit));
		MeshComponent* meshComponent = new MeshComponent(testMesh, Transform::Origin, AssetManager::GetMesh("monkey"));
		testMesh->AddComponent(meshComponent);
		AddActor(testMesh);

		//TestActor* testSprite = new TestActor(Transform::Origin);
		//testSprite->AddComponent(new SpriteComponent(testSprite, Transform(), AssetManager::GetTexture("rock")));
		//AddActor(testSprite);
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};