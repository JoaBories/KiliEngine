#pragma once
#include "Player.h"
#include "Components/FpsCameraComponent.h"
#include "Engine/Scene/Scene.h"

class Doom : public Scene
{
public :
    Doom() : Scene("Doom") {}

    void AssetLoad() override {
    }

    void OnStart() override {
        Camera* camera = new Camera(Transform(Vector3(0, 0, 1), Quaternion(), Vector3::unit), 70.0f, 0.1f, 1000.0f);
        camera->AddComponent(new FpsCameraComponent(camera, 1.0f, Vector3(0,0,1)));
        //camera->AddComponent(new FreeCamComponent(camera, 20.0f, 5.0f));
        AddActor(camera);
    
        Player* player = new Player(Transform(Vector3(0,0,1), Quaternion(), Vector3::unit), 10.0f);
        player->AddComponent(new RigidBody(player, 0.9f, 1.0f, 75.0f, 0.0f));
        player->AddComponent(new BoxCollider(player, Transform::Origin, Vector3(1,1,2)));
        AddActor(player);
        camera->GetComponent<FpsCameraComponent>()->SetPlayer(player);
    
        Floor* floor = new Floor(Transform(Vector3::zero, Quaternion(), Vector3(10,10,1)));
        floor->AddComponent(new MeshComponent(floor, Transform::Origin, AssetManager::GetMesh("plane")));
        floor->AddComponent(new BoxCollider(floor, Transform(Vector3(0,0,-10), Quaternion(), Vector3::unit), Vector3(1,1,10)));
        AddActor(floor);
    }

    void OnUpdate() override {
    }

    void OnClose() override {
    }

    void DebugDraw() override {
    }
    
};
