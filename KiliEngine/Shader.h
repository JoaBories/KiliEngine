#pragma once

#include <string>
#include "glew.h"
#include <vector>

enum ShaderType
{
    VERTEX,
    FRAGMENT
};

struct Shader
{
    std::string code;
    unsigned int id;
    ShaderType type;
};

class ShaderProgram
{
private:
	std::string ReadFile(std::string filepath);
    bool Compile(unsigned int shaderId);

    // the program ID
    unsigned int mId;
    
    Shader mVertex;
    Shader mFragment;

public:
    // constructor reads and builds the shader
    ShaderProgram(const char* vertexPath, const char* fragmentPath);

    unsigned int GetId() const { return mId; };
    Shader GetVertex() const { return mVertex; };
    Shader GetFragment() const { return mFragment; };

    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};

