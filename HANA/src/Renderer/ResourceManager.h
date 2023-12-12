#pragma once

#include <unordered_map>
//#include <sstream>
//#include <fstream>
#include "shaderClass.h"

// Singleton class to host functions that load Shaders
class ResourceManager
{
public:
	static std::unordered_map<std::string, Shader> Shaders;
	
	static Shader LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name);
	static Shader GetShader(std::string name);

private:
	ResourceManager() {}
	static Shader loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile);
};