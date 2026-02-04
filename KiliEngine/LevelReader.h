#pragma once

#include <string>
#include <fstream>

constexpr int LevelSize = 25;
constexpr float TileSize = 32.0f;

class LevelReader
{
public :
	LevelReader() = default;
	~LevelReader() = default;

	LevelReader(std::string filename);

	short mContent[LevelSize][LevelSize];
};

