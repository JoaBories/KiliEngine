#include "Material.h"

#include "Engine/Tools/Log.h"

Material::Material(std::vector<Shader*> pShaders) :
    mShaders(std::move(pShaders))
{
    mId = glCreateProgram();

    for (const Shader* shader : mShaders)
    {
        glAttachShader(mId, shader->Id);
    }
    
    glLinkProgram(mId);

    int success;
    char infoLog[512];
    glGetProgramiv(mId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mId, 512, nullptr, infoLog);
        Log::Error(LogType::Render, "ERROR::SHADER::PROGRAM::LINKING_FAILED : " + static_cast<std::string>(infoLog));
    }
}

Shader* Material::GetShaderByIndex(const unsigned int pIndex) const
{
    return mShaders[pIndex];
}

Shader* Material::GetShaderByType(ShaderType pType) const
{
    for (Shader* shader : mShaders) if (shader->Type == pType) return shader;
    return nullptr;
}

void Material::Use()
{
    glUseProgram(mId);
}

#pragma region Uniforms

void Material::SetBool(const std::string& pName, const bool pValue)
{
    glUniform1i(glGetUniformLocation(mId, pName.c_str()), static_cast<int>(pValue));
}

void Material::SetInt(const std::string& pName, const int pValue)
{
    glUniform1i(glGetUniformLocation(mId, pName.c_str()), pValue);
}

void Material::SetFloat(const std::string& pName, const float pValue)
{
    glUniform1f(glGetUniformLocation(mId, pName.c_str()), pValue);
}

void Material::SetVec2(const std::string& pName, const GLfloat pX, const GLfloat pY)
{
    glUniform2f(glGetUniformLocation(mId, pName.c_str()), pX, pY);
}

void Material::SetVec2(const std::string& pName, const Vector2& pValue)
{
    glUniform2f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y);
}

void Material::SetVec3(const std::string& pName, const GLfloat pX, const GLfloat pY, const GLfloat pZ)
{
    glUniform3f(glGetUniformLocation(mId, pName.c_str()), pX, pY, pZ);
}

void Material::SetVec3(const std::string& pName, const Vector3& pValue)
{
    glUniform3f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y, pValue.z);
}

void Material::SetVec4(const std::string& pName, const GLfloat pX, const GLfloat pY, const GLfloat pZ, const GLfloat pW)
{
    glUniform4f(glGetUniformLocation(mId, pName.c_str()), pX, pY, pZ, pW);
}

void Material::SetVec4(const std::string& pName, const Vector4& pValue)
{
    glUniform4f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y, pValue.z, pValue.w);
}

void Material::SetMatrix4Row(const std::string& pName, const Matrix4Row& pMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, pName.c_str()), 1, GL_TRUE, pMatrix.GetAsFloatPtr());
}

#pragma endregion