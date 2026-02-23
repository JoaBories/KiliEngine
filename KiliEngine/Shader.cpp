#include "Shader.h"
#include "Log.h"

#include <fstream>

using std::ifstream;

Shader::Shader(const std::string& pCode, const ShaderType pType) :
    Code(pCode), Id(0), Type(pType)
{
}

std::string ShaderProgram::ReadFile(const std::string& pFilePath)
{
    std::string shader;
    std::string line;

    //Open file of this name
    ifstream myFile;
    myFile.open(pFilePath);

    //Check for errors
    if (myFile.fail()) {
        Log::Error(LogType::Render, "Failed to open shader : " + pFilePath);
    }

    while (std::getline(myFile, line)) {
        shader += line + "\n";
    }

    myFile.close();

    return shader;
}

bool ShaderProgram::Compile(const unsigned int pShaderId)
{
    int retValue;
    glCompileShader(pShaderId);
    glGetShaderiv(pShaderId, GL_COMPILE_STATUS, &retValue);
    if (!retValue)
    {
        GLint len = 0;
        glGetShaderiv(pShaderId, GL_INFO_LOG_LENGTH, &len);
        std::vector <GLchar>log(len);

        glGetShaderInfoLog(mId, len, nullptr, log.data());
        Log::Error(LogType::Render, log.data());

        return false;
    }

    return true;
}

ShaderProgram::ShaderProgram(const std::string& pVertexName, const std::string& pFragmentName)
{
    mVertex = Shader(ReadFile(pVertexName), VertexShader);
    mVertex.Id = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexCode = mVertex.Code.c_str();
    glShaderSource(mVertex.Id, 1, &vertexCode, nullptr);
    if(!Compile(mVertex.Id))
    {
        Log::Error(LogType::Render, "Failed to compile : " + pVertexName);
    }
    else
    {
        Log::Info("Shader compiled : " + pVertexName);
    }

    mFragment = Shader(ReadFile(pFragmentName), FragmentShader);
    mFragment.Id = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentCode = mFragment.Code.c_str();
    glShaderSource(mFragment.Id, 1, &fragmentCode, nullptr);
    if (!Compile(mFragment.Id))
    {
        Log::Error(LogType::Render, "Failed to compile : " + pFragmentName);
    }
    else
    {
        Log::Info("Shader compiled : " + pFragmentName);
    }

    mId = glCreateProgram();
    glAttachShader(mId, mVertex.Id);
    glAttachShader(mId, mFragment.Id);
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

void ShaderProgram::Use()
{
    glUseProgram(mId);
}

void ShaderProgram::Unload()
{
    glDeleteShader(mVertex.Id);
    glDeleteShader(mFragment.Id);
}

#pragma region Uniforms

void ShaderProgram::SetBool(const std::string& pName, const bool pValue)
{
    glUniform1i(glGetUniformLocation(mId, pName.c_str()), static_cast<int>(pValue));
}

void ShaderProgram::SetInt(const std::string& pName, const int pValue)
{
    glUniform1i(glGetUniformLocation(mId, pName.c_str()), pValue);
}

void ShaderProgram::SetFloat(const std::string& pName, const float pValue)
{
    glUniform1f(glGetUniformLocation(mId, pName.c_str()), pValue);
}

void ShaderProgram::SetVec2(const std::string& pName, const GLfloat pX, const GLfloat pY)
{
    glUniform2f(glGetUniformLocation(mId, pName.c_str()), pX, pY);
}

void ShaderProgram::SetVec2(const std::string& pName, const Vector2& pValue)
{
    glUniform2f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y);
}

void ShaderProgram::SetVec3(const std::string& pName, const GLfloat pX, const GLfloat pY, const GLfloat pZ)
{
    glUniform3f(glGetUniformLocation(mId, pName.c_str()), pX, pY, pZ);
}

void ShaderProgram::SetVec3(const std::string& pName, const Vector3& pValue)
{
    glUniform3f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y, pValue.z);
}

void ShaderProgram::SetVec4(const std::string& pName, const GLfloat pX, const GLfloat pY, const GLfloat pZ, const GLfloat pW)
{
    glUniform4f(glGetUniformLocation(mId, pName.c_str()), pX, pY, pZ, pW);
}

void ShaderProgram::SetVec4(const std::string& pName, const Vector4& pValue)
{
    glUniform4f(glGetUniformLocation(mId, pName.c_str()), pValue.x, pValue.y, pValue.z, pValue.w);
}

void ShaderProgram::SetMatrix4Row(const std::string& pName, const Matrix4Row& pMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, pName.c_str()), 1, GL_TRUE, pMatrix.GetAsFloatPtr());
}

#pragma endregion