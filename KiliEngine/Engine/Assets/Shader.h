#pragma once

#include <string>

enum ShaderType : unsigned char
{
    VertexShader,
    FragmentShader,
    TessControlShader,
    TessEvalShader,
    GeometryShader
};

struct Shader
{
    
private:
    static std::string GetShaderCode(const std::string& pFilePath);
    static bool Compile(unsigned int pShaderId);

public:
    std::string Code;
    unsigned int Id;
    ShaderType Type;

    Shader() = delete;
    Shader(const std::string& pPath, ShaderType pType);

    void Unload();

    static bool IsSupported(const std::string& pExtension);
    static ShaderType GetShaderType(const std::string& pExtension);
};



