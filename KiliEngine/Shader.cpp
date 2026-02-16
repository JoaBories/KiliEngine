#include "Shader.h"
#include "Log.h"

#include <iostream>
#include <fstream>

using std::ifstream;

Shader::Shader(std::string pCode, ShaderType pType) :
    code(pCode), type(pType), id(0)
{
}

std::string ShaderProgram::ReadFile(std::string fileName)
{
    std::string Shader;
    std::string line;

    //Open file of this name
    ifstream myFile;
    myFile.open(SHADER_PATH + fileName);

    //Check for errors
    if (myFile.fail()) {
        Log::Error(LogType::Render, "Failed to open shader : " + fileName);
    }

    while (std::getline(myFile, line)) {
        Shader += line + "\n";
    }

    myFile.close();

    return Shader;
}

bool ShaderProgram::Compile(unsigned int shaderId)
{
    int retValue;
    glCompileShader(mId);
    glGetShaderiv(mId, GL_COMPILE_STATUS, &retValue);
    if (!retValue)
    {
        GLint len = 0;
        glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &len);
        std::vector <GLchar>log(len);

        glGetShaderInfoLog(mId, len, nullptr, log.data());
        Log::Error(LogType::Render, log.data());

        return false;
    }

    return true;
}

ShaderProgram::ShaderProgram(const char* vertexName, const char* fragmentName)
{
    mVertex = Shader(ReadFile(vertexName), VERTEX);
    mVertex.id = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexCode = mVertex.code.c_str();
    glShaderSource(mVertex.id, 1, &vertexCode, NULL);
    if(Compile(mVertex.id))
    {
        Log::Error(LogType::Render, "Failed to compile : " + (std::string)vertexName);
    }

    mFragment = Shader(ReadFile(fragmentName), FRAGMENT);
    mFragment.id = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentCode = mFragment.code.c_str();
    glShaderSource(mFragment.id, 1, &fragmentCode, NULL);
    if (Compile(mFragment.id))
    {
        Log::Error(LogType::Render, "Failed to compile : " + (std::string)fragmentName);
    }

    mId = glCreateProgram();
    glAttachShader(mId, mVertex.id);
    glAttachShader(mId, mFragment.id);
    glLinkProgram(mId);

    int success;
    char infoLog[512];
    glGetProgramiv(mId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mId, 512, NULL, infoLog);
        Log::Error(LogType::Render, "ERROR::SHADER::PROGRAM::LINKING_FAILED : " + (std::string)infoLog);
    }
}

void ShaderProgram::Use()
{
    glUseProgram(mId);
}

#pragma region Uniforms

void ShaderProgram::setBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(mId, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(mId, name.c_str()), x, y);
}

void ShaderProgram::setVec2(const std::string name, const Vector2& value)
{
    glUniform2f(glGetUniformLocation(mId, name.c_str()), value.x, value.y);
}

void ShaderProgram::setVec3(const std::string name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(mId, name.c_str()), x, y, z);
}

void ShaderProgram::setVec3(const std::string name, const Vector3& value)
{
    glUniform3f(glGetUniformLocation(mId, name.c_str()), value.x, value.y, value.z);
}

void ShaderProgram::setVec4(const std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(mId, name.c_str()), x, y, z, w);
}

void ShaderProgram::setVec4(const std::string name, const Vector4& value)
{
    glUniform4f(glGetUniformLocation(mId, name.c_str()), value.x, value.y, value.z, value.w);
}

void ShaderProgram::setMatrix4(const std::string name, const Matrix4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void ShaderProgram::setMatrix4Row(const std::string name, const Matrix4Row& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_TRUE, matrix.GetAsFloatPtr());
}

#pragma endregion