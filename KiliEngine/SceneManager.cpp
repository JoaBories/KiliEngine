#include "SceneManager.h"

std::vector<Scene*> SceneManager::Scenes = {};
int SceneManager::CurrentScene = 0;

int SceneManager::PendingNewScene = -1;
bool SceneManager::PendingReload = false;

void SceneManager::UnloadScene()
{
	Scenes[CurrentScene]->Close();
}

void SceneManager::LoadScene(GameRenderer* renderer)
{
	Scenes[CurrentScene]->SetRenderer(renderer);
	Scenes[CurrentScene]->AssetLoad();
	Scenes[CurrentScene]->Start();
}

void SceneManager::ReloadScene()
{
	if (Scenes[CurrentScene]->IsUpdatingActors())
	{
		PendingReload = true;
	}
	else
	{
		GameRenderer* renderer = Scenes[CurrentScene]->GetRenderer();
		UnloadScene();

		LoadScene(renderer);
	}
}

void SceneManager::UpdateScene()
{
	Scenes[CurrentScene]->Update();

	if (PendingNewScene != -1)
	{
		ChangeScene(PendingNewScene);
		PendingNewScene = -1;
	}

	if (PendingReload)
	{
		ReloadScene();
		PendingReload = false;
	}
}

void SceneManager::ChangeScene(int newScene)
{
	if (Scenes[CurrentScene]->IsUpdatingActors())
	{
		PendingNewScene = newScene;
	}
	else
	{
		if (Scenes[newScene])
		{
			GameRenderer* renderer = Scenes[CurrentScene]->GetRenderer();
			UnloadScene();

			CurrentScene = newScene;
			LoadScene(renderer);
		}
	}
}

void SceneManager::SetScenes(std::vector<Scene*> pScenes)
{
	if (!Scenes.empty())
	{
		FreeScenes();
	}

	Scenes = pScenes;
}

void SceneManager::FreeScenes()
{
	Scenes[CurrentScene]->Unload();

	for (Scene* scene : Scenes)
	{
		delete scene;
	}

	Scenes.clear();
}
