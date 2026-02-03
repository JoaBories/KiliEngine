#pragma once
#include "Scene.h"
#include "Struct.h"
#include "Player.h"
#include "Block.h"
#include "GameRenderer.h"
#include "AssetManager.h"

using Struct::Rectangle;

class ScenePlatformer :
    public Scene
{

public :

    ScenePlatformer() : Scene("Platformer")
    {
    }

    void OnStart() override {
        AddActor(new Player(Transform2D(Vector2(400, 400))));

        for (int i = 0; i < 13; i++)
        {
            AddActor(new Block(Transform2D{ Vector2(i * 64.0f, 750.0f), Vector2::one, i*90.0f }));
        }
        AddActor(new Block(Transform2D{ Vector2(150.0f, 650.0f), Vector2::one, 0 }));
    };

    void OnUpdate() override {
    };

    void Scene::OnClose() override {
    };

    void AssetLoad() override {
        AssetManager::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
        AssetManager::LoadTexture(*mRenderer, "Resources/block.png", "box");
        for (size_t i = 0; i < 22; i++)
        {
            std::string name = "run_" + std::to_string(i);
            AssetManager::LoadTexture(*mRenderer, "Resources/run/" + name + ".png", name);
        }
    };

};