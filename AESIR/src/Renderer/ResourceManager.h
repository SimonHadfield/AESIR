#pragma once

#include <map>
//#include <sstream>
//#include <fstream>
#include "Texture2D.h"
#include "shaderClass.h"

// Singleton class to host functions that load Shaders
class Aesir_API ResourceManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	static Shader LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name);
	static Shader GetShader(std::string name);

	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	static Texture2D GetTexture(std::string name);

	static void      Clear();

private:
	ResourceManager() { }
	static Shader loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile);
	static Texture2D loadTextureFromFile(const char* file, bool alpha);
};