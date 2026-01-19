#include <SDL.h>
#include <glew.h>
#include "GameEngine.h"
#include "SpaceInvader.h"

using namespace std;

#define GLEW_STATIC

int main(int argc, char* argv[])
{
	GameEngine* spaceInvader = new GameEngine("KiliEngine", { new SpaceInvader() });
	spaceInvader->Init();

	return 0;
}