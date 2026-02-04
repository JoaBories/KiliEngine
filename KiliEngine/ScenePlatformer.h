#pragma once
#include "Scene.h"
#include "Struct.h"
#include "Player.h"
#include "Block.h"
#include "GameRenderer.h"
#include "AssetManager.h"
#include "LevelReader.h"

using Struct::Rectangle;

class ScenePlatformer :
    public Scene
{

private :
    GameActor* CreateBlock(int x, int y) {
        Vector2 offset = Vector2(TileSize / 2, TileSize / 2);
        Vector2 pos = Vector2(x * TileSize, y * TileSize) + offset;

        GameActor* block = new Block(Transform2D(pos));

        SpriteComponent* sprite = new SpriteComponent(block, Transform2D{ Vector2::zero, Vector2(TileSize/16.0f,TileSize/16.0f), 0 }, AssetManager::GetTexture("box"));
        block->AddComponent(sprite);

        BoxCollider2D* box = new BoxCollider2D(block, 10, Rectangle{ Vector2::zero, Vector2(TileSize,TileSize)});
        block->AddComponent(box);

        return block;
    };

    GameActor* CreatePlayer(int x, int y) {
        Vector2 offset = Vector2(TileSize / 2, TileSize / 2);
        Vector2 pos = Vector2(x * TileSize, y * TileSize) + offset;

        GameActor* player = new Player(Transform2D(pos));

        std::vector<Texture*> anims;
        for (size_t i = 0; i < 22; i++)
        {
            anims.push_back(&AssetManager::GetTexture("run_" + std::to_string(i)));
        }

        AnimatedSpriteComponent* animated = new AnimatedSpriteComponent(player, { Vector2::one, Vector2(0.5f,0.5f), 0 }, anims, 30.0f);
        player->AddComponent(animated);

        BoxCollider2D* box = new BoxCollider2D(player, 10, Rectangle{ Vector2::zero, Vector2(30,60) });
        player->AddComponent(box);

        PlayerComponent* playerComp = new PlayerComponent(player, 10);
        player->AddComponent(playerComp);

        return player;
    }

public :

    ScenePlatformer() : Scene("Platformer")
    {
    }

    void OnStart() override {

        LevelReader level = LevelReader("Resources/Level1.level");

        for (size_t x = 0; x < LevelSize; x++)
        {
            for (size_t y = 0; y < LevelSize; y++)
            {
                short tile = level.mContent[x][y];

                switch (tile)
                {
                case 1:
                    AddActor(CreateBlock(x, y));
                    break;

                case 3:
                    AddActor(CreatePlayer(x, y));

                default:
                    break;
                }
            }
        }
    };

    void OnUpdate() override {
    };

    void OnClose() override {
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