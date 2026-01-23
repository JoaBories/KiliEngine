#pragma once
#include "Scene.h"
#include "Utils.h"
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

private :
    Player* pPlayer;
    std::vector<Alien*> pAliens;
    std::vector<Bullet*> pPlayerBullets;
    std::vector<Bullet*> pAlienBullets;

    void SpawnBullet(Vector2 pos, bool player);

public :

    SpaceInvader() : Scene("Game")
    {
        pPlayer = new Player(Transform2D(Vector2(400, 700)));
        pPlayer->AddComponent(new BoxCollider2D(pPlayer, 10, Rectangle{ Vector2::zero, Vector2(50,50) }));

        for (size_t i = 0; i < 6; i++)
        {
            Alien* alien = new Alien(Transform2D(Vector2(100, (i+1)*100)));
            alien->AddComponent(new BoxCollider2D(alien, 10, Rectangle{ Vector2::zero, Vector2(50,50) }));
            pAliens.push_back(alien);
            AddActor(alien);
        }

        AddActor(pPlayer);
    }

    void OnStart() override {
    };

    void OnUpdate() override {
    };

    void OnRender() override {
    };

    void Scene::OnClose() override {
    };

};

void SpaceInvader::SpawnBullet(Vector2 pos, bool player)
{
    Bullet* bullet = new Bullet(Transform2D(pos), player ? Vector2::down : Vector2::up);
    bullet->AddComponent(new BoxCollider2D(bullet, 50, { Vector2::zero, Vector2(5,20), 0 }));
    
    if (player)
    {
        pPlayerBullets.push_back(bullet);
    }
    else
    {
        pAlienBullets.push_back(bullet);
    }

    AddActor(bullet);
}
