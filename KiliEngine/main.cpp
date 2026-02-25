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


#include "GameEngine.h"
#include "DefaultScene.h"
#include "Bowling.h"

using namespace std;

int main(int argc, char* argv[])
{
	SceneManager::SetScenes({ new Bowling() });

	GameEngine* kili = new GameEngine("KiliEngine");
	kili->Init();

	SceneManager::FreeScenes();
	delete kili;

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}