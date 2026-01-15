#include <SDL.h>
#include <glew.h>
#include "GameEngine.h"

using namespace std;

#define GLEW_STATIC

int main(int argc, char* argv[])
{
	new GameEngine("KiliEngine");

	return 0;
}