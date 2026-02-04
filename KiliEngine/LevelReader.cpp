#include "LevelReader.h"
#include "Log.h"

LevelReader::LevelReader(std::string filename)
{
    //Open file of this name
    std::ifstream myFile;
    myFile.open(filename);

    //Check for errors
    if (myFile.fail()) {
        Log::Error(LogType::Test, "Error - Failed to open " + filename);
    }
    else
    {
        Log::Info("INFO - Success opening " + filename);
    }

    short tile;

    for (size_t y = 0; y < LevelSize; y++)
    {
        for (size_t x = 0; x < LevelSize; x++)
        {
            myFile >> tile;
            mContent[x][y] = tile;
        }
    }

    myFile.close();
}
