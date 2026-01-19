#pragma once
#include "Scene.h"
#include "Utils.h"
using Struct::Rectangle;
#include <vector>
#include "Player.h"
#include "Alien.h"

class SpaceInvader :
    public Scene
{

private :

public :

    inline SpaceInvader() : Scene("Game")
    {
        mActors.push_back(new Player(*this, Transform2D(Vector2( 400, 700))));
        mActors.push_back(new Alien(*this, Transform2D()));
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
            actor->Render();
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

