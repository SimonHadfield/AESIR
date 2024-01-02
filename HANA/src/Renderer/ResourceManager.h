#pragma once

#include <map>
//#include <sstream>
//#include <fstream>
#include "Texture2D.h"
#include "shaderClass.h"

// Singleton class to host functions that load Shaders
class HANA_API ResourceManager
{
public:
	static std::map<std::string, Shader_New> Shaders;
	static std::map<std::string, Texture2D> Textures;

	static Shader_New LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name);
	static Shader_New GetShader(std::string name);

	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	static Texture2D GetTexture(std::string name);

	static void      Clear();

private:
	ResourceManager() { }
	static Shader_New loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile);
	static Texture2D loadTextureFromFile(const char* file, bool alpha);
};