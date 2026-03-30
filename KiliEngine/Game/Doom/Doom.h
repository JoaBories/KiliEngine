#pragma once
#include "DoomPlayerController.h"
#include "Engine/EmptyActor.h"
#include "Engine/EnviroActor.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/PlaneCollider.h"
#include "Engine/Components/RigidBody.h"
#include "Engine/Components/TerrainComponent.h"
#include "Engine/Scene/Scene.h"

class Doom : public Scene
{
public :
    Doom() : Scene("Doom") {}

    void AssetLoad() override {
    }

    void OnStart() override {
    
        EmptyActor* player = new EmptyActor(Transform(Vector3(0, 0, 10), Quaternion(), Vector3::unit), "Player", ActorPlayer);
        player->AddComponent(new Camera(player, Transform(Vector3(0,0,1), Quaternion(), Vector3::unit), 70.0f));
        player->AddComponent(new BoxCollider(player, Transform::Origin, Vector3(1,1,2)));
        player->AddComponent(new RigidBody(player));
        player->AddComponent(new DoomPlayerController(player, 10.0f, Vector2(1.0f,1.0f)));
        AddActor(player);
    
        EnviroActor* terrain = new EnviroActor(Transform(Vector3(0,0,0), Quaternion(), Vector3::unit));
        terrain->AddComponent(new TerrainComponent(terrain, Transform::Origin, 
            AssetManager::GetTexture("Ground"), 1.0f, 10, 5));
        terrain->AddComponent(new PlaneCollider(terrain, Transform::Origin, Vector2(25, 25)));
        AddActor(terrain);
    
    }

    void OnUpdate() override {
    }

    void OnClose() override {
    }

    void DebugDraw() override {
    }
    
};
