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
	};

	void OnStart() override {
		TestActor* test = new TestActor(Transform(Vector3(400, 400, 0), Vector3(0,0,0), Vector3(1,1,1)));

		test->AddComponent(new SpriteComponent(test, Transform(), AssetManager::GetTexture("pokeball")));
		AddActor(test);
	};

	void OnUpdate() override {
	};

	void OnClose() override {
	};

	void DebugDraw() override {
	};
};