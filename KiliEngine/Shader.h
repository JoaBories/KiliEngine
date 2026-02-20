#pragma once

#include <string>
#include "glew.h"
#include <vector>

#include "Utils/Struct.h"
using Struct::Vector2;
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include "Utils/Matrix4Row.h"

enum ShaderType : Uint8
{
    Vertex,
    Fragment
};

struct Shader
{
    std::string Code;
    unsigned int Id;
    ShaderType Type;

    Shader() = default;
    Shader(std::string pCode, ShaderType pType);
};

class ShaderProgram
{
private:
	std::string ReadFile(std::string fileName);
    bool Compile(unsigned int pShaderId);

    // the program ID
    unsigned int mId;
    
    Shader mVertex;
    Shader mFragment;

public:
    // constructor reads and builds the shader
    ShaderProgram(const char* pVertexName, const char* pFragmentName);

    unsigned int GetId() const { return mId; }
    Shader GetVertex() const { return mVertex; }
    Shader GetFragment() const { return mFragment; }

    // use/activate the shader
    void Use();

    void Unload();

    // utility uniform functions
    void SetBool(const std::string& pName, bool pValue);
    void SetInt(const std::string& pName, int pValue);
    void SetFloat(const std::string& pName, float pValue);
    void SetVec2(const std::string& pName, GLfloat pX, GLfloat pY);
    void SetVec2(const std::string& pName, const Vector2& pValue);
    void SetVec3(const std::string& pName, GLfloat pX, GLfloat pY, GLfloat pZ);
    void SetVec3(const std::string& pName, const Vector3& pValue);
    void SetVec4(const std::string& pName, GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat pW);
    void SetVec4(const std::string& pName, const Vector4& pValue);
    void SetMatrix4Row(const std::string& pName, const Matrix4Row& pMatrix);
};

