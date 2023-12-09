#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"
#include <string>

class HANA_API Renderable
{
public:
	static void DrawQuad2D(float x, float y, float width, float height);
	static void DrawBackground(); // glm::vec3 color and or texture - enum or string
	static void DrawTextureQuad2D(float x, float y, float width, float height, const char* ImgPath);

	static void DrawImGui(int player1Score, int player2Score); // to abstract ###############################################
	static void DrawImGuiText(const std::string& Text, unsigned int x = 0, unsigned int y = 0, float fontSize = 2.0f, unsigned int Alignment = 0); //std::string Text, int x, int y, float size
private:
	float x, y, width, height;
};


