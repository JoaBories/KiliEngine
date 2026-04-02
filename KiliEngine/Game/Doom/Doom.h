#pragma once
#include "DoomPlayerController.h"
#include "Engine/EmptyActor.h"
#include "Engine/EnviroActor.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/FreeCamComponent.h"
#include "Engine/Components/InstanceComponent.h"
#include "Engine/Components/MeshComponent.h"
#include "Engine/Components/PlaneCollider.h"
#include "Engine/Components/RigidBody.h"
#include "Engine/Components/TerrainComponent.h"
#include "Engine/Scene/Scene.h"

class Doom : public Scene
{
private:
    void SpawnTerrain(const int pSquareNumber, const float pSquareSize, bool pTerrain)
    {
        const float size = static_cast<float>(pSquareNumber) * pSquareSize / 2.0f;
        
        EnviroActor* terrain = new EnviroActor(Transform(Vector3(0,0,0), Quaternion(), Vector3::unit));
        if (terrain) terrain->AddComponent(new TerrainComponent(terrain, Transform::Origin, AssetManager::GetTexture("Ground"), 1.0f, pSquareSize, pSquareNumber));
        else terrain->AddComponent(new MeshComponent(terrain, Transform(Vector3::zero, Quaternion(), Vector3(size, size, 1.0f)), AssetManager::GetMesh("plane"), AssetManager::GetTexture("Ground"), "BasicTile"));
        terrain->AddComponent(new PlaneCollider(terrain, Transform::Origin, Vector2(size, size)));
        AddActor(terrain);
    }

    void SpawnPlayer(const Vector3& pPosition)
    {
        EmptyActor* player = new EmptyActor(Transform(pPosition, Quaternion(), Vector3::unit), "Player", ActorPlayer);
        player->AddComponent(new Camera(player, Transform(Vector3(0,0,1), Quaternion(), Vector3::unit), 70.0f));
        player->AddComponent(new BoxCollider(player, Transform::Origin, Vector3(1,1,2)));
        player->AddComponent(new RigidBody(player, 10.0f, 1.5f, 100.0f, 0.0f));
        player->AddComponent(new DoomPlayerController(player, 150.0f, 2.0f, Vector2(1.0f,1.0f)));
        AddActor(player);
    }

    void SpawnFlyingCamera(const Vector3& pPosition)
    {
        CameraActor* cam = new CameraActor(Transform(pPosition, Quaternion(), Vector3::unit), 70.0f, 0.1f, 2000.0f);
        cam->AddComponent(new FreeCamComponent(cam, 20.0f, 5.0f));
        AddActor(cam);
    }

    void SpawnWall(const Transform& pTransform, Texture* pTexture)
    {
        EnviroActor* wall = new EnviroActor(pTransform);
        wall->AddComponent(new MeshComponent(wall, Transform::Origin, AssetManager::GetMesh("Wall"), pTexture, "BasicTile"));
        AddActor(wall);
    }
    
public :
    Doom() : Scene("Doom") {}

    void AssetLoad() override {
    }

    void OnStart() override {
        //SpawnPlayer(Vector3(0, 0, 10));
        SpawnFlyingCamera(Vector3::zero);
        SpawnTerrain(20, 15.0f, true);

        EnviroActor* blades = new EnviroActor(Transform::Origin);
        blades->AddComponent(new InstanceComponent(blades, Transform::Origin, AssetManager::GetMesh("grass"), Vector2(100.0f,100.0f), AssetManager::GetTexture("grass")));
        AddActor(blades);

        Map* mMap = AssetManager::GetMap("Test_Map");
        for (MapWall wall : mMap->GetWalls())
        {
            SpawnWall(wall.Transform, mMap->GetTexture(wall.TextureIndex));
        }
    }

    void OnUpdate() override {
    }

    void OnClose() override {
    }

    void DebugDraw() override {
    }
    
};
