#include "Shader.h"

#include "Engine/Tools/Log.h"
#include "glew.h"

#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;

Shader::Shader(const std::string& pPath, const ShaderType pType) :
    Id(0), Type(pType)
{
    Code = GetShaderCode(pPath);
    switch (Type)
    {
    case VertexShader :
        Id = glCreateShader(GL_VERTEX_SHADER);
        break;

    case FragmentShader :
        Id = glCreateShader(GL_FRAGMENT_SHADER);
        break;

    case GeometryShader :
        Id = glCreateShader(GL_GEOMETRY_SHADER);
        break;

    case TessControlShader :
        Id = glCreateShader(GL_TESS_CONTROL_SHADER);
        break;

    case TessEvalShader :
        Id = glCreateShader(GL_TESS_EVALUATION_SHADER);
        break;
    }
    
    const char* vertexCode = Code.c_str();
    glShaderSource(Id, 1, &vertexCode, nullptr);
    if(!Compile(Id))
    {
        Log::Info("Failed to compile : " + pPath);
    }
    else
    {
        Log::Info("Shader compiled : " + pPath);
    }
}

void Shader::Unload()
{
    glDeleteShader(Id);
}

bool Shader::IsSupported(const std::string& pExtension)
{
    if (pExtension == ".vert") return true;
    if (pExtension == ".frag") return true;
    if (pExtension == ".geom") return true;
    if (pExtension == ".tesc") return true;
    if (pExtension == ".tese") return true;
    return false;
}

ShaderType Shader::GetShaderType(const std::string& pExtension)
{
    if (pExtension == ".vert") return VertexShader;
    if (pExtension == ".frag") return FragmentShader;
    if (pExtension == ".geom") return GeometryShader;
    if (pExtension == ".tesc") return TessControlShader;
    if (pExtension == ".tese") return TessEvalShader;
    return VertexShader;
}

std::string Shader::GetShaderCode(const std::string& pFilePath)
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

bool Shader::Compile(const unsigned int pShaderId)
{
    int compileStatus;
    glCompileShader(pShaderId);
    glGetShaderiv(pShaderId, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        GLint len = 0;
        glGetShaderiv(pShaderId, GL_INFO_LOG_LENGTH, &len);
        std::vector <GLchar>log(len);

        glGetShaderInfoLog(pShaderId, len, nullptr, log.data());
        Log::Info(log.data());

        return false;
    }

    return true;
}