#pragma once
#include "Scene.h"
#include "Struct.h"
using Struct::Rectangle;
#include <vector>
#include "Player.h"
#include "Alien.h"
#include "BoxCollider2D.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "GameRenderer.h"
#include "Bullet.h"

class SpaceInvader :
    public Scene
{

public :

    SpaceInvader() : Scene("Game")
    {
        for (size_t i = 0; i < 6; i++)
        {
            AddActor(new Alien(Transform2D(Vector2(100, (i + 1) * 100))));
        }

        AddActor(new Player(Transform2D(Vector2(400, 700))));
    }

    void OnStart() override {
    };

    void OnUpdate() override {
    };

    void OnRender() override {
    };

    void Scene::OnClose() override {
    };

    void AssetLoad() override {
    };

};