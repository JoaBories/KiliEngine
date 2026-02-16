#pragma once

#include <string>
#include "glew.h"
#include <vector>

#include "Utils/Struct.h"
using Struct::Vector2;
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include "Utils/Matrix4.h"
#include "Utils/Matrix4Row.h"

const std::string SHADER_PATH = "Resources/Shaders/";

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

    Shader() = default;
    Shader(std::string pCode, ShaderType pType);
};

class ShaderProgram
{
private:
	std::string ReadFile(std::string fileName);
    bool Compile(unsigned int shaderId);

    // the program ID
    unsigned int mId;
    
    Shader mVertex;
    Shader mFragment;

public:
    // constructor reads and builds the shader
    ShaderProgram(const char* vertexName, const char* fragmentName);

    unsigned int GetId() const { return mId; };
    Shader GetVertex() const { return mVertex; };
    Shader GetFragment() const { return mFragment; };

    // use/activate the shader
    void Use();

    // utility uniform functions
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string name, GLfloat x, GLfloat y);
    void setVec2(const std::string name, const Vector2& value);
    void setVec3(const std::string name, GLfloat x, GLfloat y, GLfloat z);
    void setVec3(const std::string name, const Vector3& value);
    void setVec4(const std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setVec4(const std::string name, const Vector4& value);
    void setMatrix4(const std::string name, const Matrix4& matrix);
    void setMatrix4Row(const std::string name, const Matrix4Row& matrix);
};

