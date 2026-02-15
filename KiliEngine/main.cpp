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
#include "DefaultScene.h"

using namespace std;

int main(int argc, char* argv[])
{
	SceneManager::SetScenes({ new DefaultScene() });

	GameEngine* Kili = new GameEngine("KiliEngine");
	Kili->Init();

	SceneManager::FreeScenes();
	delete Kili;

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}