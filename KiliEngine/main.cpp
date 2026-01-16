#include <SDL.h>
#include <glew.h>
#include "GameEngine.h"
#include "MainMenu.h"

using namespace std;

#define GLEW_STATIC

int main(int argc, char* argv[])
{
	GameEngine* spaceInvader = new GameEngine("KiliEngine", { new MainMenu() });
	spaceInvader->Init();

	return 0;
}