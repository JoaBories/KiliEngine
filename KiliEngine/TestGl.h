#pragma once
#include "Scene.h"
#include "AssetManager.h"
#include "Log.h"
#include "TestActor.h"
#include "SpriteComponent.h"


class TestGl : public Scene
{

public:

	TestGl() : Scene("Test openGl") {}
	virtual ~TestGl() = default;

	void AssetLoad() override {
		AssetManager::LoadTexture(mRenderer, "pokeball.png", "pokeball");
		AssetManager::LoadTexture(mRenderer, "rock.png", "rock");
		AssetManager::LoadShader("Basic");
	}

	void OnStart() override {
		TestActor* testMesh = new TestActor(Transform(Vector3(5, 0, 0), Quaternion(Vector3::unitY, 10), Vector3(1, 1, 1)));
		Mesh* mesh = new Mesh({AssetManager::GetTexture("rock")}, new VertexArray(CubeVertices, 24, CubeIndices, 36), AssetManager::GetShader("Basic"));
		MeshComponent* meshComp = new MeshComponent(testMesh, Transform(Vector3(0, 0, 0), Quaternion(Vector3::unitX, 0), Vector3(1, 1, 1)), mesh);
		testMesh->AddComponent(meshComp);
		AddActor(testMesh);

		// TestActor* testSprite = new TestActor(Transform(Vector3(0, 0, 0), Quaternion(Vector3::unitX, 0), Vector3(1, 1, 1)));
		// testSprite->AddComponent(new SpriteComponent(testSprite, Transform(), AssetManager::GetTexture("rock")));
		// AddActor(testSprite);
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};