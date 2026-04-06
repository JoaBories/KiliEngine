#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "Game/Doom/Doom.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include "Engine/GameEngine.h"
#include "Engine/Scene/DefaultScene.h"
#include "Game/Bowling/Bowling.h"
#include "Engine/Scene/SceneManager.h"

int main(int argc, char* argv[])
{
	SceneManager::SetScenes({ new Doom() });

	GameEngine* kili = new GameEngine("KiliEngine");
	kili->Init();

	SceneManager::FreeScenes();
	delete kili;

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}