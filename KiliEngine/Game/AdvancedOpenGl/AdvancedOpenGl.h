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
		EmptyActor* skybox = new EmptyActor(Transform(Vector3(0,0,0), Quaternion(), Vector3::unit * 1000.0f), "Skybox");
		skybox->AddComponent(new MeshComponent(skybox, Transform::Origin, AssetManager::GetMesh("Skybox"), AssetManager::GetTexture("StarrySky"), "Basic"));
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
			AssetManager::GetTexture("SeaTexture"), AssetManager::GetTexture("GroundTexture"), 
			0.01f, 0.0f, 0.15f, 0.1f));
		AddActor(planet);
		
		EmptyActor* sun = new EmptyActor(Transform(Vector3(-20.0f,0,10.0f), Quaternion(), Vector3::unit), "Sun");
		sun->AddComponent(new PlanetMeshComponent(sun, 7.5f,
			nullptr, AssetManager::GetTexture("SunTexture"),
			-0.005f, -1.0f, 0.25f, 1.0f));
		AddActor(sun);
	}

	void OnUpdate() override {
	}

	void OnClose() override {
	}

	void DebugDraw() override {
	}
};

