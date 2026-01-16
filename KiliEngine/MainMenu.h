#pragma once
#include "Scene.h"
#include "Utils.h"
using Struct::Rectangle;
#include <vector>

class MainMenu :
    public Scene
{

private :
    std::vector<Rectangle> mMap;
    Vector2 mPlayerPos;

public :

    inline MainMenu() : Scene("MainMenu"),
        mMap{}, mPlayerPos( 400, 400)
    {
    }

    // Inherited via Scene
    inline void SetRenderer(GameRenderer* pRenderer) override {   
        mRenderer = pRenderer;
    };

    inline void Start() override {
        mMap.push_back({ Vector2(400, 0), Vector2(200, 100) , 0 });
        mMap.push_back({ Vector2(400, 800), Vector2(200, 100) , 0 });
        mMap.push_back({ Vector2(800, 400), Vector2(100, 200) , 0 });
        mMap.push_back({ Vector2(0, 400), Vector2(100, 200) , 0 });
    };

    inline void Update() override {
    };

    inline void Render() override {
        for (const Rectangle& rect : mMap)
        {
            mRenderer->DrawRect(rect);
        }

        Rectangle player = { mPlayerPos, Vector2(50, 50), 0 };
        mRenderer->DrawRect(player);
    };

    inline void OnInput(SDL_Event input) override {

        if (input.key.type == SDL_KEYUP)
        {
            return;
        }

        switch (input.key.keysym.sym)
        {
        case SDLK_z :
            mPlayerPos += Vector2::down * 10;
            break;
        case SDLK_q :
            mPlayerPos += Vector2::left * 10;
            break;
        case SDLK_s :
            mPlayerPos += Vector2::up * 10;
            break;
        case SDLK_d :
            mPlayerPos += Vector2::right * 10;
            break;

        default:
            break;
        } 
        
    };

    inline void Close() override {
    };
};

