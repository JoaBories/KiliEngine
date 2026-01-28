#pragma once
#include "Scene.h"
#include "Struct.h"
#include "Player.h"
#include "GameRenderer.h"
#include "AssetManager.h"

using Struct::Rectangle;

class SpaceInvader :
    public Scene
{

public :

    SpaceInvader() : Scene("Game")
    {
    }

    void OnStart() override {
        AddActor(new Player(Transform2D(Vector2(400, 700))));
    };

    void OnUpdate() override {
    };

    void Scene::OnClose() override {
    };

    void AssetLoad() override {
        AssetManager::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
        for (size_t i = 0; i < 22; i++)
        {
            std::string name = "run_" + std::to_string(i);
            AssetManager::LoadTexture(*mRenderer, "Resources/run/" + name + ".png", name);
        }
    };

};