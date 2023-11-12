#include "Renderable.h"

void Renderable::DrawBackground() // glm::vec3 color
{
	float x, y, width, height;
	x = -1.0f;
	y = -1.0f;
	width = 2.0f;
	height = 2.0f;

	GLfloat vertices[] =
	{
		//  X          Y            Z
			x,         y,           0.0f,    // 1
			x,         y + height,  0.0f,    // 2
			x + width, y + height,  0.0f,    // 3
			x + width, y,           0.0f     // 4
	};


	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	Shader shaderProgram("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/background.frag"); //  create shader with vertexShader and fragmentShader
	VAO VAO1;										// create vertex array
	VAO1.Bind();									// bind vertex array 

	VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer
	EBO EBO1(indices, sizeof(indices));			    // create index buffer

	//VBO1.Bind();
	//EBO1.Bind();
	//	link VBO to VAO
	//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);							// link position vertices

	shaderProgram.Activate();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Unbind to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	shaderProgram.Delete();
}

void Renderable::DrawQuad2D(float x, float y, float width, float height) {

	GLfloat vertices[] =
	{
		//  X          Y            Z
			x,         y,           0.0f,    // 1
			x,         y + height,  0.0f,    // 2
			x + width, y + height,  0.0f,    // 3
			x + width, y,           0.0f     // 4
	};


	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	Shader shaderProgram("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.frag"); //  create shader with vertexShader and fragmentShader
	VAO VAO1;										// create vertex array
	VAO1.Bind();									// bind vertex array 

	VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer
	EBO EBO1(indices, sizeof(indices));			    // create index buffer

	//VBO1.Bind();
	//EBO1.Bind();
	//	link VBO to VAO
	//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);							// link position vertices
	
	shaderProgram.Activate();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Unbind to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	shaderProgram.Delete();

    
};
