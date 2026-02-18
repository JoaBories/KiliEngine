#pragma once
#include "Scene.h"
#include "AssetManager.h"
#include "TestActor.h"
#include "SpriteComponent.h"
#include "AnimatedSpriteComponent.h"


class TestGl :
    public Scene
{

public:

	TestGl() : Scene("Test openGl") {};

	void AssetLoad() override {
		AssetManager::LoadTexture(mRenderer, "Resources/pokeball.png", "pokeball");
		AssetManager::LoadTexture(mRenderer, "Resources/rock.png", "rock");
	};

	void OnStart() override {
		TestActor* test = new TestActor(Transform(Vector3(0, 0, 0), Quaternion(Vector3::unitX, 0), Vector3(1, 1, 1)));

		test->AddComponent(new SpriteComponent(test, Transform(), AssetManager::GetTexture("rock")));
		AddActor(test);
	};

	void OnUpdate() override {
	};

	void OnClose() override {
	};

	void DebugDraw() override {
	};
};