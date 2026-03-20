#pragma once

#include <vector>

#include "Shader.h"
#include "glew.h"

#include "Utils/Struct.h"
using Struct::Vector2;
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include "Utils/Matrix4Row.h"

class Material
{
private:
    // the program ID
    unsigned int mId;
    std::vector<Shader*> mShaders;

public:
    // constructor reads and builds the shader
    explicit Material(std::vector<Shader*> pShaders);

    [[nodiscard]] Shader* GetShaderByIndex(unsigned int pIndex) const;
    [[nodiscard]] Shader* GetShaderByType(ShaderType pType) const;

    [[nodiscard]] unsigned int GetId() const { return mId; }

    // use/activate the shader
    void Use();

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