#pragma once
#include "Scene.h"
class DefaultScene : public Scene
{

public :

	DefaultScene() : Scene("DefaultScene") {};

	void AssetLoad() override {
	};

	void OnStart() override {
	};

	void OnUpdate() override {
	};

	void OnClose() override {
	};
};

