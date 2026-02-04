#pragma once
#include "Scene.h"

class SceneManager
{
private :
	static std::vector<Scene*> Scenes;
	static int CurrentScene;


public :
	static int PendingNewScene;
	static bool PendingReload;

	static void UnloadScene();
	static void LoadScene(GameRenderer* renderer);
	static void ReloadScene();

	static void UpdateScene();

	static void ChangeScene(int newScene);

	static void SetScenes(std::vector<Scene*> pScenes);

	static void FreeScenes();
};

