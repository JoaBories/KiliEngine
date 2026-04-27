#pragma once
#include "Engine/Scene/Scene.h"
#include "Engine/Assets/AssetManager.h"

#include "DoomPlayerController.h"
#include "DoorComponent.h"
#include "EnemyComponent.h"
#include "FloorComponent.h"
#include "Engine/EmptyActor.h"
#include "Engine/EnviroActor.h"
#include "Engine/Components/BillboardComponent.h"
#include "Engine/Components/FreeCamComponent.h"
#include "Engine/Components/MeshComponent.h"
#include "Engine/Components/PlaneCollider.h"
#include "Engine/Components/RigidBody.h"
#include "Engine/Components/SphereCollider.h"
#include "Engine/Components/SpriteComponent.h"
#include "Engine/Components/TerrainComponent.h"

class Doom : public Scene
{
private:
    void SpawnTerrain(const int pSquareNumber, const float pSquareSize, const bool pTerrain)
    {
        const float size = static_cast<float>(pSquareNumber) * pSquareSize / 2.0f;
        
        EnviroActor* terrain = new EnviroActor(Transform(Vector3(0,0,0), Quaternion(), Vector3::unit));
        if (pTerrain) terrain->AddComponent(new TerrainComponent(terrain, Transform::Origin, AssetManager::GetTexture("Ground"), 1.0f, pSquareSize, pSquareNumber));
        else terrain->AddComponent(new MeshComponent(terrain, Transform(Vector3::zero, Quaternion(), Vector3(size, size, 1.0f)), AssetManager::GetMesh("plane"), AssetManager::GetTexture("Ground"), "BasicTile"));
        terrain->AddComponent(new PlaneCollider(terrain, Transform::Origin, false, Vector2(size, size)));
        AddActor(terrain);
    }

    void SpawnPlayer(const Vector3& pPosition)
    {
        EmptyActor* player = new EmptyActor(Transform(pPosition, Quaternion(), Vector3::unit), "Player", ActorTags::Player);
        player->AddComponent(new Camera(player, Transform(Vector3(0,0,1), Quaternion(), Vector3::unit), 90.0f, 0.1f, 10000.0f));
        player->AddComponent(new BoxCollider(player, Transform::Origin, true, Vector3(0.9f,0.9f,2)));
        player->AddComponent(new RigidBody(player, 10.0f, 2.0f, 100.0f, 0.0f));
        player->AddComponent(new DoomPlayerController(player, 200.0f, 10.0f, Vector2(1.0f,1.0f)));
        AddActor(player);
    }
    
    void SpawnHud()
    {
        EmptyActor* hud = new EmptyActor(Transform::Origin, "Hud", ActorTags::Hud);
        hud->AddComponent(new AnimatedComponent(hud, AssetManager::GetAnimation("Pistol", 0, 4, 24)));
        hud->AddComponent(new SpriteComponent(hud, Transform(Vector3(0.0f,-95.0f,0.0f), Quaternion(), Vector3(5.0f,5.0f,5.0f)), AssetManager::GetTexture("Pistol_0")));
        AddActor(hud);
    }
    
    void SpawnSky()
    {
        EmptyActor* skybox = new EmptyActor(Transform(Vector3(0,0,0), Quaternion(), Vector3::unit * 30.0f), "Skybox");
        skybox->AddComponent(new MeshComponent(skybox, Transform::Origin, AssetManager::GetMesh("Skybox"), AssetManager::GetTexture("DarkSky"), "Basic"));
        AddActor(skybox);
    }

    void SpawnFlyingCamera(const Vector3& pPosition, const float pSpeed)
    {
        CameraActor* cam = new CameraActor(Transform(pPosition, Quaternion(), Vector3::unit), 90.0f, 0.1f, 10000.0f);
        cam->AddComponent(new FreeCamComponent(cam, pSpeed, 5.0f));
        AddActor(cam);
    }

    void SpawnWall(const Transform& pTransform, Texture* pTexture)
    {
        EnviroActor* wall = new EnviroActor(pTransform);
        wall->AddComponent(new MeshComponent(wall, Transform::Origin, AssetManager::GetMesh("Wall"), pTexture, "Wall"));
        wall->AddComponent(new BoxCollider(wall, Transform::Origin, false, Vector3(0.1f,1.0f,1.0f)));
        AddActor(wall);
    }

    void SpawnFloor(const Vector3& pPosition, Mesh* pMesh, const Vector3& pOffset, const Vector2 pSize, const float pFloorHeight)
    {
        const Vector3 floorOffset = Vector3(0.0f,0.0f,pFloorHeight);
        EnviroActor* floor = new EnviroActor(Transform(pPosition, Quaternion(), Vector3::unit));
        floor->AddComponent(new FloorComponent(floor, Transform(floorOffset, Quaternion(), Vector3::unit), pMesh));
        floor->AddComponent(new PlaneCollider(floor, Transform(pOffset + floorOffset, Quaternion(), Vector3::unit), false, pSize));
        AddActor(floor);
    }
    
    void SpawnDoor(const Vector3& pPosition, const Quaternion& pRotation)
    {
        const Vector3 size = Vector3(0.5f,10.0f,5.0f);
        EmptyActor* door = new EmptyActor(Transform(pPosition, pRotation, Vector3::unit), "Door", ActorTags::Door);
        door->AddComponent(new DoorComponent(door));
        door->AddComponent(new MeshComponent(door, Transform(Vector3::zero, Quaternion(), size), AssetManager::GetMesh("cube"), AssetManager::GetTexture("Door"), "Basic"));
        door->AddComponent(new BoxCollider(door, Transform::Origin, false, size));
        AddActor(door);
    }
    
    void SpawnEnemy(const Vector3& pPosition)
    {
        EmptyActor* enemy = new EmptyActor(Transform(pPosition, Quaternion(), Vector3::unit), "Enemy", ActorTags::Enemy);
        enemy->AddComponent(new BillboardComponent(enemy, Transform(Vector3(0,0,0), Quaternion(), Vector3(3.0f, 1.0f, 3.0f)), AssetManager::GetTexture("Imp_0")));
        enemy->AddComponent(new AnimatedComponent(enemy, AssetManager::GetAnimation("Imp", 0, 3, 6)));
        enemy->AddComponent(new BoxCollider(enemy, Transform::Origin, true, Vector3(1.0f, 1.0f, 3.0f)));
        enemy->AddComponent(new RigidBody(enemy, 10.0f, 1.5f, 100.0f, 0.0f));
        enemy->AddComponent(new EnemyComponent(enemy));
        AddActor(enemy);
    }
    
public :
    Doom() : Scene("Doom") {}

    void AssetLoad() override {
        AssetManager::LoadAll();
    }

    void OnStart() override {
        SpawnHud();
        SpawnPlayer(Vector3(0, 0, 10));
        //SpawnFlyingCamera(Vector3::zero, 20.0f);
        
        SpawnSky();

        Map* map = AssetManager::GetMap("Map2");
        for (auto [TextureIndex, Transform] : map->GetWalls())
        {
            SpawnWall(Transform, map->GetTexture(TextureIndex));
        }

        for (const auto& [TextureIndex, Position, Vertices, Offset, Size, Floor] : map->GetFloors())
        {
            Mesh* mesh = new Mesh(Vertices, map->GetTexture(TextureIndex), "BasicTile");
            SpawnFloor(Position, mesh, Offset, Size, Floor);
        }
        
        for (const Transform& door : map->GetDoors())
        {
            SpawnDoor(door.GetPosition(), door.GetRotation());
        }
        
        for (const Vector3& enemy : map->GetEnemies())
        {
            SpawnEnemy(enemy);
        }
    }

    void OnUpdate() override {
    }

    void OnClose() override {
    }

    void DebugDraw() override {
    }
    
};
