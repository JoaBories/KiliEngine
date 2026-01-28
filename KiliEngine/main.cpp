#include <SDL.h>
#include <glew.h>
#include "GameEngine.h"
#include "DefaultScene.h"

using namespace std;

int main(int argc, char* argv[])
{
	GameEngine* spaceInvader = new GameEngine("KiliEngine", {new DefaultScene()});
	spaceInvader->Init();

	return 0;
}