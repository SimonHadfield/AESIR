#pragma once

#include "Renderer.h"
#include <string>
//#include "HanaCube.h"

class HANA_API Renderable
{
public:
	Renderable() {}
	Renderable(Shader& shaderProgram_);

	// 2D
	static void DrawQuad2D(float x, float y, float width, float height);

	void DrawTextureQuad2D(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
	void DrawTextureQuad2D(float x, float y, float width, float height, const char* ImgPath, float scale_x, float scale_y); // texture clipping

	void DrawBackground(); // glm::vec3 color and or texture - enum or string

	static void DrawImGui(int player1Score, int player2Score); // to abstract ###############################################
	static void DrawImGuiText(const std::string& Text, unsigned int x = 0, unsigned int y = 0, float fontSize = 2.0f, unsigned int Alignment = 0); //std::string Text, int x, int y, float size


	// 3D 
	static void DrawCuboid(glm::vec3 pos, glm::vec3 dimensions);
	static void Draw3DScene();

private:
	float x, y, width, height;

	// Quad indices
	inline static GLuint quad_indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	Shader shaderProgram;
	unsigned int quadVAO;
	void initRenderData();

	//static Renderable renderable;
	//Shader shaderProgram; //  create shader with vertexShader and fragmentShader

	// // VAO, VBO, EBO
	// VAO VAO1;										// create vertex array
	// 
	// VBO VBO1;			// create vertex buffer
	// EBO EBO1; // (quad_indices, sizeof(quad_indices));			    // create index buffer
	// 
	// 
	// // screen height and width
	// inline static float screenWidth = 1080;
	// inline static float screenHeight = 720;
	// inline static glm::mat4 orthographic = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
	// 
	// inline static GLint orthoLoc;
};


