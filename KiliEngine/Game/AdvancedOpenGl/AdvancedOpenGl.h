#pragma once
#include "Engine/Scene/Scene.h"
#include "Engine/CameraActor.h"
#include "Engine/EnviroActor.h"
#include "Engine/Assets/AssetManager.h"
#include "Engine/Components/FreeCamComponent.h"
#include "Engine/Components/InstanceComponent.h"
#include "Engine/Components/MeshComponent.h"

class AdvancedOpenGl : public Scene
{
	void SpawnSky()
	{
		EmptyActor* skybox = new EmptyActor(Transform(Vector3(0,0,0), Quaternion(), Vector3::unit * 30.0f), "Skybox");
		skybox->AddComponent(new MeshComponent(skybox, Transform::Origin, AssetManager::GetMesh("Skybox"), AssetManager::GetTexture("DarkSky"), "Basic"));
		AddActor(skybox);
	}

	void SpawnFlyingCamera(const Vector3& pPosition, const float pSpeed)
	{
		CameraActor* cam = new CameraActor(Transform(pPosition, Quaternion(), Vector3::unit), 70.0f, 0.1f, 10000.0f);
		cam->AddComponent(new FreeCamComponent(cam, pSpeed, 5.0f));
		AddActor(cam);
	}

public :

	AdvancedOpenGl() : Scene("AdvancedOpenGl") {}
	~AdvancedOpenGl() override = default;

	void AssetLoad() override {
	}

	void OnStart() override {
		SpawnFlyingCamera(Vector3(-10,0,0), 2.0f);
		SpawnSky();
		
		EmptyActor* planet = new EmptyActor(Transform::Origin, "Planet");
		planet->AddComponent(new PlanetMeshComponent(planet, 3.0f, 
			AssetManager::GetTexture("GroundTexture"), AssetManager::GetTexture("SeaTexture"), 
			0.002f, 0.0f, 0.05f));
		AddActor(planet);
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};

