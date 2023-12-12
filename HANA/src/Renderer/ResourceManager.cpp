#include "ResourceManager.h"

/*
Shader ResourceManager::LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name) {
	Shader[name] = loadShaderFromFile(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
	return Shader[name];
}

Shader ResourceManager::loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile = nullptr) {
	
	std::string vertexCode;
	std::string fragmentCode;
    std::string geometryCode;

    try
    {
        // open files
        std::ifstream vertexShaderFile(vertexShaderFile);
        std::ifstream fragmentShaderFile(fragmentShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (geometryShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(geometryShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    //shader.Compile(vShaderCode, fShaderCode, geometryShaderFile != nullptr ? gShaderCode : nullptr);

    return shader;
}
*/