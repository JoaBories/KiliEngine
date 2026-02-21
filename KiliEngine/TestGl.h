#pragma once
#include "Scene.h"
#include "AssetManager.h"
#include "Log.h"
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

		auto testMesh = new TestActor(Transform(Vector3(2, 0, 0), Quaternion(Vector3::unitY, 10), Vector3(1, 1, 1)));
		auto mesh = new Mesh({AssetManager::GetTexture("rock")}, new VertexArray(CubeVertices, 24, CubeIndices, 36), "Basic");
		auto meshComp = new MeshComponent(testMesh, Transform(Vector3(0, 0, 0), Quaternion(Vector3::unitX, 0), Vector3(1, 1, 1)), mesh);
		testMesh->AddComponent(meshComp);
		AddActor(testMesh);

		//TestActor* testSprite = new TestActor(Transform(Vector3(0, 0, 0), Quaternion(Vector3::unitX, 0), Vector3(1, 1, 1)));
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