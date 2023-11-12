#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"

class HANA_API Renderable
{
public:
	static void DrawQuad2D(float x, float y, float width, float height);
	static void DrawBackground(); // glm::vec3 color and or texture - enum or string
private:
	float x, y, width, height;
};


