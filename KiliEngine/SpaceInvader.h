#pragma once
#include "Scene.h"
#include "Utils.h"
using Struct::Rectangle;
#include <vector>
#include "Player.h"
#include "Alien.h"
#include "BoxCollider2D.h"

class SpaceInvader :
    public Scene
{

private :
    Player* pPlayer;
    std::vector<Alien*> pAliens;

public :

    SpaceInvader() : Scene("Game")
    {
        pPlayer = new Player(this, Transform2D(Vector2(400, 700)));
        pPlayer->AddComponent(new BoxCollider2D(pPlayer, 10, Rectangle{ Vector2::zero, Vector2(50,50) }));

        for (size_t i = 0; i < 6; i++)
        {
            Alien* alien = new Alien(this, Transform2D(Vector2(100, (i+1)*100)));
            alien->AddComponent(new BoxCollider2D(alien, 10, Rectangle{ Vector2::zero, Vector2(50,50) }));
            pAliens.push_back(alien);
            mActors.push_back(alien);
        }

        mActors.push_back(pPlayer);
    }

    // Inherited via Scene
    inline void SetRenderer(GameRenderer* pRenderer) override {   
        mRenderer = pRenderer;
    };

    inline void Start() override {
        for (const auto& actor : mActors)
        {
            actor->Start();
        }
    };

    inline void Update() override {
        for (const auto& actor : mActors)
        {
            actor->Update();
        }
    };

    inline void Render() override {
        for (const auto& actor : mActors)
        {
            actor->Render(mRenderer);
        }
    };

    inline void OnInput(SDL_Event input) override {

        if (input.key.type == SDL_KEYUP)
        {
            return;
        }
        
    };

    inline void Close() override {
    };
};

