#pragma once
#include "Scene.h"
#include "Struct.h"
#include <vector>
#include "Player.h"
#include "Alien.h"
#include "BoxCollider2D.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "GameRenderer.h"
#include "Bullet.h"
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
        for (size_t i = 0; i < 6; i++)
        {
            AddActor(new Alien(Transform2D(Vector2(100, (i + 1) * 100))));
        }

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