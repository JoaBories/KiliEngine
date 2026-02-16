#include "Shader.h"
#include "Log.h"

#include <iostream>
#include <fstream>

using std::ifstream;

std::string ShaderProgram::ReadFile(std::string filepath)
{
    std::string Shader;
    std::string line;

    //Open file of this name
    ifstream myFile;
    myFile.open(filepath);

    //Check for errors
    if (myFile.fail()) {
        Log::Error(LogType::Render, "Failed to open shader : " + filepath);
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

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
    mVertex = Shader();
    mFragment = Shader();

    mVertex.code = ReadFile(vertexPath);
    const char* vertexCode = mVertex.code.c_str();
    mFragment.code = ReadFile(fragmentPath);
    const char* fragmentCode = mFragment.code.c_str();

    mVertex.id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertex.id, 1, &vertexCode, NULL);
    if(Compile(mVertex.id))
    {
        Log::Error(LogType::Render, "Failed to compile : " + (std::string)vertexPath);
    }

    mFragment.id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragment.id, 1, &fragmentCode, NULL);
    if (Compile(mFragment.id))
    {
        Log::Error(LogType::Render, "Failed to compile : " + (std::string)fragmentPath);
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

void ShaderProgram::use()
{
    glUseProgram(mId);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(mId, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
}

void ShaderProgram::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(mId, name.c_str()), x, y, z);
}
