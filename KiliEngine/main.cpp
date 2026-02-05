#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <SDL.h>
#include <glew.h>
#include "GameEngine.h"
#include "SceneLevel.h"

#include <iostream>

using namespace std;

#define GLEW_STATIC

int main(int argc, char* argv[])
{
	SceneManager::SetScenes({ 
		new SceneLevel("Resources/Level1.level", "Platformer"), 
		new SceneLevel("Resources/GameOver.level", "GameOver") });

	GameEngine* Kili = new GameEngine("KiliEngine");
	Kili->Init();

	SceneManager::FreeScenes();
	delete Kili;

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}